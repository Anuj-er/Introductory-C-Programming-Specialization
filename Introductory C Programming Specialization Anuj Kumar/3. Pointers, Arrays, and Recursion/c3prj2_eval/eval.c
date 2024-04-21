#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2) {
  const card_t * const *c1 = (const card_t* const*) vp1;
  assert(c1);
  const card_t *card1 = *c1;
  const card_t * const *c2 = (const card_t* const*) vp2;
  assert(c2);
  const card_t *card2 = *c2;
  if (card1->value > card2->value)
    return -1;
  else if (card1->value == card2->value){
    return card2->suit - card1->suit; // enum value of spade is 0 and club is 3
  }
  else
    {
      assert(card1->value < card2->value);
      return 1;
    }
}

static int is_flush_suit_of_type(deck_t *hand, suit_t s)
{
  assert(hand);
  int count = 0;
  card_t *c=NULL;
  for (int i=0; i<hand->n_cards; i++)
    {
      c = hand->cards[i];
      if (c->suit == s)
        count++;
    }
  return count >= 5 ? 1 : 0;
}

suit_t flush_suit(deck_t * hand) {
  assert(hand);

  if(is_flush_suit_of_type(hand, SPADES))
    {
      return SPADES;
    }
  else if(is_flush_suit_of_type(hand, HEARTS))
    {
      return HEARTS;
    }
  else if(is_flush_suit_of_type(hand, DIAMONDS))
    {
      return DIAMONDS;
    }
   else if(is_flush_suit_of_type(hand, CLUBS))
    {
      return CLUBS;
    }
    else
      return NUM_SUITS;
}

unsigned get_largest_element(unsigned * arr, size_t n) {
  assert(arr);
  assert(n > 0);
  unsigned largest = arr[0];
  for (int i=1; i<n; i++)
    {
      if (arr[i] > largest)
        largest = arr[i];
    }
 return largest;
}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
  assert(match_counts);
  assert(n>0);
  for (int j=0; j<n; j++)
    {
      if (match_counts[j]==n_of_akind)
        {         
            return j;
        }
    }

  assert(0); // forceful
  return 0; // if none found?
}

// Assuming cards are already sorted
ssize_t  find_secondary_pair(deck_t * hand,
                             unsigned * match_counts,
                             size_t match_idx) {
  if (hand==NULL)
    return -1;
  
  assert(match_counts);
  for (int i=0; i<hand->n_cards; i++)
    {
      if ((i >= match_idx) && (i<(match_idx+match_counts[match_idx])))
        continue;
      else if (match_counts[i]>1)
        return i;
    }
  
  return -1;
}

// returns 1 if found n length straight else 0
// hand already sorted
int is_n_length_straight_at(deck_t * hand, size_t index, suit_t fs, int n) {
  card_t *c1 = hand->cards[index];
  suit_t suitAtIndex = c1->suit;
  card_t *c2 = NULL;
  int count = 1;
  for (int j=index+1; j<hand->n_cards; j++)
    {
      c2 = hand->cards[j];
      if (c1->value == c2->value) // equal card values - could be straight
        {
          if (fs == NUM_SUITS)
            continue;
          else if (c2->suit==suitAtIndex)
            {
              count++;
              if (count==n)
                return 1;
              c1=c2;
            }
        }
      else if (c1->value == (c2->value + 1)) // straight/straight flush
        {
          if ((fs == NUM_SUITS) || (suitAtIndex == c2->suit) )
            {
              count++;
              if (count==n)
                return 1;
            }
          c1 = c2; // next card may be of same value as current and suit as suitAtIndex
        }
      else
        return 0; // no straight - break the loop early
    }
  return 0;
}

// returns -1 if found ace-low straight else 0
int is_ace_low_straight_at(deck_t * hand, size_t index, suit_t fs) {
  if (is_n_length_straight_at(hand, index, fs, 4)) //card value ==5
    {
      //if (hand->cards[0]->value==VALUE_ACE)
        return -1;
    }
  return 0;
}

// Hand is sorted by value
int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  if (hand==NULL)
    return 0;

  if (is_n_length_straight_at(hand, index, fs, 5)==1)
    return 1;
  else if (index==0 && hand->cards[0]->value==VALUE_ACE)
    {
      if (hand->cards[hand->n_cards-4]->value==5)
        return is_ace_low_straight_at(hand, hand->n_cards - 4, fs);
    }
    return 0;
}

hand_eval_t build_hand_from_match(deck_t * hand,
                                  unsigned n,
                                  hand_ranking_t what,
                                  size_t idx) {
  assert(hand!=NULL);

  hand_eval_t ans;
  ans.ranking = what;
  int j = idx;
  int i = 0; // i can be 0 to 4
  // fill 0 to n-1
  for (; i<n; i++,j++) 
    {
      ans.cards[i] = hand->cards[j];
    }
  // fill remainder of the cards array into n-1 to 4
  for (int k=0; i<5 && k<hand->n_cards; k++)
    {
      if ((i==0) || (hand->cards[k]->value != hand->cards[idx]->value))
        ans.cards[i++] = hand->cards[k];
    }
  
  return ans;
}

static void sort_hands(deck_t * hand1, deck_t * hand2) {
  qsort(hand1->cards, hand1->n_cards, sizeof(card_t*), card_ptr_comp);
  qsort(hand2->cards, hand2->n_cards, sizeof(card_t*), card_ptr_comp);
}

// return a positive number
// if hand 1 is better, 0 if the hands tie, and a negative number
// if hand 2 is better.
int compare_hands(deck_t * hand1, deck_t * hand2) {

  assert(hand1 && hand2);

  // 1. sort the cards in decreasing order
  sort_hands(hand1, hand2);
  
  // 2. Select 5 cards making a hand
  // 3. Figure out the ranking of each hand
  hand_eval_t h1 = evaluate_hand(hand1);
  hand_eval_t h2 = evaluate_hand(hand2);
  hand_ranking_t h1Rank = h1.ranking;
  hand_ranking_t h2Rank = h2.ranking;
  if (h1Rank != h2Rank)
    {
      // find winner using ranking
      return h1Rank < h2Rank ? 1 : -1; 
    }
  else
    {
      card_t *card1;
      card_t *card2;
      for (int i=0; i<5; i++)
        {
          //card_ptr_comp(h2.cards[i], h1.cards[i]);
          card1 = h1.cards[i];
          card2 = h2.cards[i];
          if (card1->value != card2->value)
              return (card1->value - card2->value);
        }
    }
  return 0;
}



//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand) ;

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
        (fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
        assert(hand->cards[i]->value == VALUE_ACE &&
               (fs == NUM_SUITS || hand->cards[i]->suit == fs));
        ans->cards[4] = hand->cards[i];
        size_t cpind = i+1;
        while(hand->cards[cpind]->value != 5 ||
              !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
          cpind++;
          assert(cpind < hand->n_cards);
        }
        copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
        copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
        ans.cards[copy_idx] = hand->cards[i];
        copy_idx++;
        if (copy_idx >=5){
          break;
        }
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4]; 
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
