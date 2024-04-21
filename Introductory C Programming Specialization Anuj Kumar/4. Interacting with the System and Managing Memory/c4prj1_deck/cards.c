#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {
    assert(c.value >= 2 && c.value <= VALUE_ACE);
    assert(c.suit == SPADES || \
            c.suit == CLUBS || \
            c.suit == HEARTS || \
            c.suit == DIAMONDS);
}

const char * ranking_to_string(hand_ranking_t r) {

    switch(r) {
        case(STRAIGHT_FLUSH): return "STRAIGHT_FLUSH"; break;
        case(FOUR_OF_A_KIND): return "FOUR_OF_A_KIND"; break;
        case(FULL_HOUSE): return "FULL_HOUSE"; break;
        case(FLUSH): return "FLUSH"; break;
        case(STRAIGHT): return "STRAIGHT"; break;
        case(THREE_OF_A_KIND): return "THREE_OF_A_KIND"; break;
        case(TWO_PAIR): return "TWO_PAIR"; break;
        case(PAIR): return "PAIR"; break;
        case(NOTHING): return "NOTHING"; break;
    }
    return ""; 
}

char value_letter(card_t c) {
    if (c.value < 10)
        return '0' + c.value;
    else if (c.value == 10)
        return '0';
    else if (c.value == VALUE_JACK)
        return 'J';
    else if (c.value == VALUE_QUEEN)
        return 'Q';
    else if (c.value == VALUE_KING)
        return 'K';
    else if (c.value == VALUE_ACE)
        return 'A';
    return 'E';
}


char suit_letter(card_t c) {
    switch(c.suit) {
        case(SPADES): return 's'; break;
        case(HEARTS): return 'h'; break;
        case(DIAMONDS): return 'd'; break;
        case(CLUBS): return 'c'; break;
        case(NUM_SUITS): return '?'; break;
    }
    return '?';
}

void print_card(card_t c) {
    printf("%c%c", value_letter(c), suit_letter(c));
}

card_t card_from_letters(char value_let, char suit_let) {
    assert((value_let > '1' && value_let <= '9') \
            || value_let == '0'\
            || value_let == 'J'\
            || value_let == 'Q' \
            || value_let == 'K' \
            || value_let == 'A' );
    assert(suit_let == 's' \
            || suit_let == 'h' \
            || suit_let == 'd' \
            || suit_let == 'c'); 
    card_t temp;
    switch(value_let) {
        case('0'): temp.value = 10; break;
        case('A'): temp.value = VALUE_ACE ; break;
        case('K'): temp.value = VALUE_KING; break;
        case('Q'): temp.value = VALUE_QUEEN; break;
        case('J'): temp.value = VALUE_JACK; break;
        default: temp.value = value_let - '0';
    }
    switch(suit_let) {
        case('s'): temp.suit = SPADES; break;
        case('h'): temp.suit = HEARTS; break;
        case('c'): temp.suit = CLUBS; break;
        case('d'): temp.suit = DIAMONDS; break;
    }
    return temp;
}

card_t card_from_num(unsigned c) {
    card_t temp;
    temp.suit = c / 13;
    temp.value = (c % 13) + 2; 
    return temp;
}
