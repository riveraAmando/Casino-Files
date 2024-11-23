#include <stdlib.h>
#include <time.h>
#include "cardops.h"

#define MAX_HAND_SIZE 5
#define DECK_SIZE 52
#define SUITS 4
#define RANKS 13

// Checks to see if the current cardID is seen
// previously.
int isRepeatedCard(int cardID[],int card_index)
{
  int current_card;
  for(current_card=0;current_card<card_index;current_card++)
  {
    if(current_card == card_index)
      break;
    
    if(cardID[card_index] == cardID[current_card])
      return 1;
  }
  return 0;
}

// Initializes and shuffles deck.
void shuffle(Deck * deck)
{
  (*deck).num_cards = DECK_SIZE;
  int i;
  for(i=0;i<DECK_SIZE;i++)
  {
    do{
      (*deck).card[i] = rand()%SUITS * 100 + rand()%RANKS;
    }while(isRepeatedCard((*deck).card,i));
  }
}

// Resets number of cards in the hand.
void resetHand(Player * player)
{
  (*player).num_cards = 0;
  (*player).score = 0;
  (*player).fold = 0;
  (*player).bet = 0;
}

// Resets cards on table and pot.
void resetTable(Table * table)
{
  (*table).num_cards = 0;
  (*table).pot = 0;
  (*table).high_bet = 0;
}

// Deals card(s) to a player.
void playerDeal(Player * player,Deck * deck,int amt_cards)
{
  int cards_dealt;
  for(cards_dealt=0;cards_dealt<amt_cards;cards_dealt++)
  {
    (*player).hand[(*player).num_cards++] = (*deck).card[--(*deck).num_cards];
  }
}

// Deals card(s) to a the community card pool.
void tableDeal(Table * table,Deck * deck,int amt_cards)
{
  int cards_dealt;
  for(cards_dealt=0;cards_dealt<amt_cards;cards_dealt++)
  {
    (*table).card_pool[(*table).num_cards++] = (*deck).card[--(*deck).num_cards];
  }
}