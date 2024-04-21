#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

  /*
   Add the particular card to the given deck (which will
   involve reallocing the array of cards in that deck).
   */

void add_card_to(deck_t * deck, card_t c) {

  deck->n_cards++;
  deck->cards = realloc(deck->cards, sizeof(*deck->cards) * deck->n_cards);
  deck->cards[deck->n_cards - 1] = malloc(sizeof(c));
  *deck->cards[deck->n_cards - 1] = c;

}

   /*
   Add a card whose value and suit are both 0, and return a
   pointer to it in the deck.  This will add an invalid card
   to use as a placeholder for an unknown card.
   */

card_t * add_empty_card(deck_t * deck) {

  card_t *empty = malloc(sizeof(* empty));
  empty->value = 0;
  empty->suit = 0;

  deck->n_cards++;
  deck->cards = realloc(deck->cards, sizeof(*deck->cards) * deck->n_cards);
  deck->cards[deck->n_cards - 1] = empty;

  return empty;

}

deck_t * make_deck_exclude(deck_t * excluded_cards) {

    deck_t * deck = malloc(sizeof(*deck));
    deck->cards = NULL;
    deck->n_cards = 0;
    
    for (int i = 0; i < 52; i++) {
        if (!deck_contains(excluded_cards, card_from_num(i))) {
            add_card_to(deck, card_from_num(i));
        }
    }

    return deck;
}

deck_t * build_remaining_deck(deck_t **hands, size_t n_hands) {

    deck_t * excluded_cards = malloc(sizeof(*excluded_cards));
    excluded_cards->cards = NULL;
    excluded_cards->n_cards = 0;

    for (int i = 0; i < n_hands; i++) {
        for (int j = 0; j < hands[i]->n_cards; j++) {
            add_card_to(excluded_cards, *(hands[i]->cards[j]));
        }
    }

    return make_deck_exclude(excluded_cards);
}

void free_deck(deck_t * deck) {

    for (int i = 0; i < deck->n_cards; i++) {
        free(deck->cards[i]);
    }
    free(deck->cards);
    free(deck);
    
}

void print_hand(deck_t * hand){

    for(int i = 0; i < hand->n_cards; i++) {
        print_card(*(hand->cards[i]));
        printf(" ");
    }
}

int deck_contains(deck_t * d, card_t c) {
    card_t tmp;
    for(int i = 0; i < d->n_cards; i++) {
        tmp = *(d->cards[i]);
        if (tmp.value == c.value && tmp.suit == c.suit)
            return 1;
    }
  return 0;
}

void shuffle(deck_t * d){
    
    int random_number;
    card_t *tmp;
    size_t count = d->n_cards;
    for(int i = 0; i < count ; i++) {
        random_number = random() % count;
        tmp = d->cards[i];
        d->cards[i] = d->cards[random_number];
        d->cards[random_number] = tmp;
    }
}

void assert_full_deck(deck_t * d) {
    
    for (int i = 0; i < 52; i++) {
        assert(deck_contains(d, card_from_num(i)));
    }
}
