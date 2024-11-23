#ifndef cardops
#define cardops

/****************************************************
*                                                   *
*  A set of basic playing card functions,           *
*  including deck shuffling, drawing cards, and     *
*  reseting the game state.                         *
*                                                   *
****************************************************/



#include <stdlib.h>
#include <time.h>

#define MAX_HAND_SIZE 5
#pragma once
#define DECK_SIZE 52
#define SUITS 4
#define RANKS 13

// Keeps track of player data.
typedef struct player
{
  char name[20];
  int num_cards;
  int hand[MAX_HAND_SIZE];
  int score;
  int money;
  int bet;
  int fold;
}Player;

// Keeps track of table data.
typedef struct table
{
  int num_cards;
  int card_pool[MAX_HAND_SIZE];
  int high_bet;
  int pot;
}Table;

// Keeps track of deck data.
typedef struct card_storage
{
  int num_cards;
  int card[DECK_SIZE];
}Deck;

// Checks to see if the current cardID is seen
// previously.
int isRepeatedCard();

// Initializes and shuffles deck.
void shuffle();

// Resets number of cards in the hand.
void resetHand();

// Resets cards on table and pot.
void resetTable();

// Deals card(s) to a player.
void playerDeal();

// Deals card(s) to a the community card pool.
void tableDeal();

#endif