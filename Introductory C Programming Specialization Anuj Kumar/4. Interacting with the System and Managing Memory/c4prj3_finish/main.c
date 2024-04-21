#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"


size_t find_winning_hand(deck_t ** hands, size_t n) {

    size_t num_winner = 0;
    deck_t * deck_winner = hands[0];

    for (size_t i = 1; i < n; i++) {
        
        /*
        printf("hand0 (current winner) = ");
        print_hand(deck_winner);
        printf(" hand[%ld] = ",i);
        print_hand(hands[i]);
        printf("\n");
        */

        int result = compare_hands(deck_winner, hands[i]);
        if (result == 0) {
            num_winner = n;
        }
        if (result < 0 ) {
            num_winner = i;
            deck_winner = hands[i];
        }
    }

    return num_winner;
}

void print_results(unsigned int * results, unsigned int n, unsigned int total) {

    for(size_t i = 0; i < n; i++) {
        printf("Hand %zu won %u / %u times (%.2f%%)\n", i, results[i], total, (float) results[i] / total * 100);
    }

    printf("And there were %u ties\n", results[n]);

}

int main(int argc, char ** argv) {
 
    if (argc != 2 && argc != 3) {
        printf("Prawidlowa skladnia to: %s file_input no_or_trials\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsigned int num_trials = 10000;
    if (argc == 3) {
        num_trials = atoi(argv[2]);
    }

    FILE * f = fopen(argv[1], "r");
    size_t n_hands = 0;
    future_cards_t * fc = malloc(sizeof(*fc));
    fc->decks = NULL;
    fc->n_decks = 0;
    deck_t ** uploaded_hands = read_input(f, &n_hands, fc);
    fclose(f);
 
    deck_t * remaining_cards = build_remaining_deck(uploaded_hands, n_hands);
    unsigned int * wins = calloc(n_hands + 1, sizeof(*wins));

    for(int i = 0; i < num_trials; i++) {
        shuffle(remaining_cards);
        future_cards_from_deck(remaining_cards, fc);
        unsigned int winner = find_winning_hand(uploaded_hands, n_hands);
        wins[winner]++;

        /*
        printf("uploaded_hands[0]: ");
        print_hand(uploaded_hands[0]);
        printf(" uploaded_hands[1]: ");
        print_hand(uploaded_hands[1]);
        printf(" winner: %d\n",winner);
        */

    }

    print_results(wins, n_hands, num_trials);

    free(wins);
    free_deck(remaining_cards);
    for (int i = 0; i < n_hands; i++) {
        free_deck(uploaded_hands[i]);
    }
    free(uploaded_hands);
    for (int i = 0; i < fc->n_decks; i++) {
        free(fc->decks[i].cards);
    }
    free(fc->decks);
    free(fc);
    
    return EXIT_SUCCESS;

}
