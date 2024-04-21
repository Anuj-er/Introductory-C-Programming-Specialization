#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2) {

  const card_t * const * c1 =  ( card_t const **) vp1;
  const card_t * const * c2 =  ( card_t const **) vp2;

  if ((*c1)->value == (*c2)->value) {
      return (*c2)->suit - (*c1)->suit;
  }  else {
      return ((*c2)->value - (*c1)->value);
  }

}

suit_t flush_suit(deck_t * hand) {

  int suits[4] = {0};

  for (int i = 0; i < hand->n_cards; i++) 
      suits[hand->cards[i]->suit] += 1;
  
  for (int i = 0; i < 4; i++)
      if (suits[i] >= 5) return i;
  return NUM_SUITS;

}

unsigned get_largest_element(unsigned * arr, size_t n) {

  if (n == 0) return 0;

  unsigned largest = arr[0];
  for (int i = 1; i < n; i++)
      if (arr[i] > largest) largest = arr[i];

  return largest;

}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
  
  for (int i = 0; i < n; i++) 
      if (match_counts[i] == n_of_akind) return i;

  assert(0);

}

size_t  find_secondary_pair(deck_t * hand,
                             unsigned * match_counts,
                             size_t match_idx) {
  
  size_t card_value;

  for (int i = 0; i < hand->n_cards; i++) {
      card_value = hand->cards[i]->value;
      if ( card_value  == hand->cards[match_idx]->value) {
          continue;
      }
      if (match_counts[i] > 1) {
          return i;
      }
  }

  return -1;
}

int is_suit_matched(card_t c, suit_t fs) {


  if (fs == NUM_SUITS) 
      return 1;
  else 
      return (c.suit == fs) ? 1 : 0;

}

size_t find_index_for_card_value(deck_t * hand, size_t index, int value) {

    for (; index < hand->n_cards; index++) {
        if (hand->cards[index]->value == value)
            return index;
    }
    return 0;
}

int is_1_length_straight_at(deck_t * hand, size_t index, suit_t fs) {

  for (; index < hand->n_cards; index++) {
    if (hand->cards[index]->value != VALUE_ACE) return 0;
    if (is_suit_matched(*(hand->cards[index]), fs) == 1) return -1;
  }
  return 0;
}

int is_n_length_straight_at(deck_t * hand, size_t index, suit_t fs, int n) {

  // check whether we have enough cards for n_straight
  size_t hand_size = hand->n_cards;;
  if (hand_size - index < n) return 0;

  int straight_found = 0;
  int suit_found = is_suit_matched(*(hand->cards[index]), fs);

  unsigned previous_value;
  unsigned current_value = hand->cards[index]->value;
  index++;

  if(suit_found || fs == NUM_SUITS) {
      straight_found++;
      suit_found = 0;
  } else return 0; 

  
  // main loop
  for (; index < hand_size && straight_found < n; index++) {
    previous_value = current_value;
    current_value = hand->cards[index]->value;
    // is suit not matched previously and now we have different card,
    // staight is no longer possible
    if (current_value != previous_value && !suit_found && fs != NUM_SUITS) return 0;
    if (!suit_found)
       suit_found = is_suit_matched(*(hand->cards[index]), fs);
    // if value difference is greater than 1, no straight for sure
    if (previous_value - current_value > 1)  return 0;
    // if value is the same and looking for any suit, we can continue as
    // such value was already counted for straight
    if (current_value == previous_value) {
        continue;
    }
 
    if(suit_found || fs == NUM_SUITS) {
        straight_found++;
        suit_found = 0;
    }
  }
 
  // check what we have found
  if (straight_found == 5 && n == 5)  return 1;
  else 
      if (straight_found == 4 && n == 4) {
          if (current_value == 2) return -1;
          else return 0;
      }
  else
    return 0;
}

int is_straight_at(deck_t * hand, size_t index, suit_t fs) {

  int try_n_5 = is_n_length_straight_at(hand, index, fs, 5);
  if (try_n_5 != 0 ) return try_n_5;
  else { 
  // chech for A-low straight
      if (is_1_length_straight_at(hand, index, fs) == -1) {
          int i = find_index_for_card_value(hand, index, 5);
          if (i < index)
              return 0;
          else
              return is_n_length_straight_at(hand, i, fs, 4);
      }
  }
  return 0;
}


hand_eval_t build_hand_from_match(deck_t * hand,
                                  unsigned n,
                                  hand_ranking_t what,
                                  size_t idx) {

  hand_eval_t ans;
  ans.ranking = what;
  
  // fill with n of kinds first
  for(int i = 0; i < n; i++) {
      ans.cards[i] = hand->cards[idx + i];
  }
 
  size_t pos = 0;
  // fill left with highest value cards
  for(int i = n; i < 5; i++) {
      if (idx == 0) pos += n;
      ans.cards[i] = hand->cards[pos];
      pos++;
      idx--;
  }
      
  return ans;
}

/* Compares hand1 and hands2 and returns:
                 0 - both hands tie
   negative number - hands2 wins
   positive number - hands1 wins
*/



int compare_hands(deck_t * hand1, deck_t * hand2) {

  qsort(hand1->cards, hand1->n_cards, sizeof(card_t *), card_ptr_comp); 
  qsort(hand2->cards, hand2->n_cards, sizeof(card_t *), card_ptr_comp);

  hand_eval_t eval_hand1 = evaluate_hand(hand1);
  hand_eval_t eval_hand2 = evaluate_hand(hand2);

  // rankings are equals
  if (eval_hand1.ranking == eval_hand2.ranking) {
      for(int i = 0; i < 5; i++) {
            if (eval_hand1.cards[i]->value == eval_hand2.cards[i]->value) {
                continue;
            }
            else {
                return eval_hand1.cards[i]->value - eval_hand2.cards[i]->value;
            }
        }
        return 0;
  }
  // rankings are not equals
  else {
      return eval_hand2.ranking - eval_hand1.ranking;
  }
}



//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand) {

    unsigned * arr = malloc(sizeof(*arr) * hand->n_cards);
    for (int i = 0; i < hand->n_cards; i++) {
        char value = value_letter(*hand->cards[i]);
        unsigned count = 0;
        for (int j = 0; j < hand->n_cards; j++) {
            if (value == value_letter(*hand->cards[j])) {
                count++;
            }
        }
        arr[i] = count;
    }

    return arr;

}

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
