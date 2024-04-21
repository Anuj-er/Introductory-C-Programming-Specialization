#include "input.h"
#include "future.h"
#include <stdio.h>
#include <string.h>


deck_t * hand_from_string(const char * str, future_cards_t * fc) {
   
    deck_t * hand = malloc(sizeof(*hand));
    hand->cards = NULL;
    hand->n_cards = 0;

    while(str != NULL && *str != '\0') {
        if (*str == ' ') {
            str++;
            continue;
        } else {
            char value = *str;
            str++;
            if(value == '?') {
                int index = atoi(str);
                str = strchr(str, ' ');
                add_future_card(fc, index, add_empty_card(hand));
            } else {
                char suit = *str;
                str++;
                add_card_to(hand, card_from_letters(value, suit));
            }
        }
        //str++;
    }

    if (hand->n_cards < 5) {
        fprintf(stderr, "Each hand should have at least 5 cards.\n");
        exit(EXIT_FAILURE);
    }

    return hand;

}

/*
   This function reads the input from input file f (has one
   hand per line represented with a deck_t) It allocates a
   deck_t for each hand and place it into an array of
   pointers to deck_ts. This function needs to tell its
   caller how many hands it read. We could return a struct,
   but we are going to do this a different way: it will fill
   in *n_hands with the number of hands.
*/

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {

    deck_t ** arr = NULL;
    *n_hands = 0;

    ssize_t nread = 0;
    char *line = NULL;
    size_t len = 0;

    while((nread = getline(&line, &len, f)) != -1 ) {
        line[nread - 1] = '\0';
        (*n_hands)++;
        arr = realloc(arr, sizeof(*arr) * (*n_hands));
        arr[*n_hands - 1] = hand_from_string(line, fc);
    }
    free(line);
    return arr;
}
