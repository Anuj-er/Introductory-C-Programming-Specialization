#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"

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
