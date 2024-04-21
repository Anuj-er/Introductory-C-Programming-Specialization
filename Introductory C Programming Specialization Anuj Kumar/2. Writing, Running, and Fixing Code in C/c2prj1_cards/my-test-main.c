#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "cards.h"

void assert_card_correct(card_t c, unsigned value, suit_t suit) {
  printf("assert_card_correct with c.value (%d), c.suit (%d), value (%d), suit (%d)\n",
	 c.value, c.suit, value, suit);
  if (value == 0 && suit == 0) {
    printf("Should have printed ASSERT\n");
  } else {
    assert(c.value == value && c.suit == suit);
  }
}

void test_card_from_num() {
  printf("test_card_from_num\n");
  //  assert_card_correct(card_from_num(-1),0,0);
  assert_card_correct(card_from_num(0),2,SPADES);
  assert_card_correct(card_from_num(1),3,SPADES);
  assert_card_correct(card_from_num(12),VALUE_ACE,SPADES);
  assert_card_correct(card_from_num(13),2,HEARTS);
  assert_card_correct(card_from_num(50),VALUE_KING, CLUBS);  
  assert_card_correct(card_from_num(51),VALUE_ACE, CLUBS);
  //  assert_card_correct(card_from_num(52),0,0);
  printf("PASSED TESTS\n");
  printf("\n\n");
}

void test_assert_card_valid() {
  printf("test_assert_valid\n");
  card_t c;
  /*
  c.value = 1;
  c.suit = SPADES;
  assert_card_valid(c);
  printf("Should have printed ASSERT\n");
  */
  c.suit = SPADES;
  c.value = 2;
  assert_card_valid(c);
  printf("Should have been OK\n");
  /*
  c.value = VALUE_ACE+1;
  assert_card_valid(c);
  printf("Should have printed ASSERT\n");
  */
  c.value = VALUE_ACE;
  assert_card_valid(c);
  printf("Should have been OK\n");
}

void test_ranking_to_string()  {
  //ranking_to_string(STRAIGHT_FLUSH-1); // exit with EXIT_FAILURE
  assert(strcmp(ranking_to_string(STRAIGHT_FLUSH), "STRAIGHT_FLUSH") == 0);
  assert(strcmp(ranking_to_string(FOUR_OF_A_KIND), "FOUR_OF_A_KIND") == 0);
  assert(strcmp(ranking_to_string(NOTHING), "NOTHING") == 0);
  //ranking_to_string(NOTHING+1); // exit with EXIT_FAILURE
  printf("PASSED TESTS\n\n\n");
}

void test_value_letter() {
  printf("test_value_letter\n");
  card_t c;
  c.value = 2;
  c.suit = SPADES;
  assert(value_letter(c) == '2');
  c.value = 10;
  assert(value_letter(c) == '0');
  c.value = VALUE_JACK;
  assert(value_letter(c) == 'J');
  c.value = VALUE_QUEEN;
  assert(value_letter(c) == 'Q');
  c.value = VALUE_KING;
  assert(value_letter(c) == 'K');
  c.value = VALUE_ACE;
  assert(value_letter(c) == 'A');
  printf("PASSED TESTS\n\n\n");
}

void test_suit_letter()  {
  printf("test_suit_letter\n");
  card_t c;
  c.value = 3;
  c.suit = SPADES;
  assert(suit_letter(c) == 's');
  c.suit = HEARTS;
  assert(suit_letter(c) == 'h');
  c.suit = DIAMONDS;
  assert(suit_letter(c) == 'd');
  c.suit = CLUBS;
  assert(suit_letter(c) == 'c');
  //  c.suit = NUM_SUITS;
  //  suit_letter(c);
  //  printf("Should have printed ASSERT\n");
  printf("\n\n");
}

void test_print_card() {
  printf("test_print_card\n");
  card_t c;
  c.value = 2;
  c.suit = SPADES;
  print_card(c);
  printf("\n");
  c.value = 10;
  print_card(c);
  printf("\n");
  c.value = VALUE_JACK;
  print_card(c);
  printf("\n");
  c.value = VALUE_QUEEN;
  print_card(c);
  printf("\n");
  c.value = VALUE_KING;
  print_card(c);
  printf("\n");
  c.value = VALUE_ACE;
  print_card(c);
  printf("\n");
  c.suit = HEARTS;
  print_card(c);
  printf("\n");
  c.suit = DIAMONDS;
  print_card(c);
  printf("\n");
  c.suit = CLUBS;
  print_card(c);
  printf("\n\n");
}

void test_card_from_letters(char value_let, char suit_let) {
  printf("test_card_from_letters\n");
  card_t card;
  card = card_from_letters('2', 's');
  printf("card (value=%d, suit=%d)\n", card.value, card.suit);
  assert(card.value == 2 && card.suit == SPADES);
  card = card_from_letters('0', 's');
  printf("card (value=%d, suit=%d)\n", card.value, card.suit);
  assert(card.value == 10 && card.suit == SPADES);
  card = card_from_letters('J', 's');
  printf("card (value=%d, suit=%d)\n", card.value, card.suit);
  assert(card.value == VALUE_JACK && card.suit == SPADES);
  card = card_from_letters('Q', 's');
  printf("card (value=%d, suit=%d)\n", card.value, card.suit);
  assert(card.value == VALUE_QUEEN && card.suit == SPADES);
  card = card_from_letters('K', 's');
  printf("card (value=%d, suit=%d)\n", card.value, card.suit);
  assert(card.value == VALUE_KING && card.suit == SPADES);
  card = card_from_letters('A', 's');
  printf("card (value=%d, suit=%d)\n", card.value, card.suit);
  assert(card.value == VALUE_ACE && card.suit == SPADES);
  card = card_from_letters('2', 'h');
  printf("card (value=%d, suit=%d)\n", card.value, card.suit);
  assert(card.value == 2 && card.suit == HEARTS);
  card = card_from_letters('2', 'd');
  printf("card (value=%d, suit=%d)\n", card.value, card.suit);
  assert(card.value == 2 && card.suit == DIAMONDS);
  card = card_from_letters('2', 'c');
  printf("card (value=%d, suit=%d)\n", card.value, card.suit);
  assert(card.value == 2 && card.suit == CLUBS);
}

int main(void) {
  test_card_from_num();
  test_assert_card_valid();
  test_ranking_to_string();
  test_value_letter();
  test_suit_letter();
  test_print_card();
  test_card_from_letters('2', 's');
}
