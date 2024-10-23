/***********************************************************
*
* Author:    Keven Duong
*
* File:      texasholdem.c
*
* Purpose:   Main file for texas holdem game.
*
* Version:   1.0 Oct 18, 2024
*            1.1 Oct 22, 2024 (seperated functions into header files
*                              and created basic player vs ai game)
*
***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cardSetType.h"
#include "readCards.h"
#include "cardOps.h"
#include "rankHand.h"




int main()
{
  char dummy;
  // Game Setup
  srand(time(NULL));
  Deck main_deck;
  Hand player_hand;
  Hand ai_hand;
  Hand card_pool;
  
  // Round Setup
  fillDeck(&main_deck);
  emptyHand(&player_hand);
  emptyHand(&ai_hand);
  emptyHand(&card_pool);
  draw(&player_hand,&main_deck,2);
  draw(&ai_hand,&main_deck,2);
  
  printf("-------BLIND-------\n");
  printf("Your cards:\n");
  printCards(player_hand);
  player_hand.handRank = handRank(player_hand,card_pool,1);
  printf("\n");
  printf("Enter to continue.");
  scanf("%c",&dummy);
  
  printf("\n--------FLOP-------\n");
  draw(&card_pool,&main_deck,3);
  printf("Community cards:\n");
  printCards(card_pool);
  printf("Your cards:\n");
  printCards(player_hand);
  player_hand.handRank = handRank(player_hand,card_pool,1);
  printf("\n");
  printf("Enter to continue.");
  scanf("%c",&dummy);
  
  printf("\n--------TURN-------\n");
  draw(&card_pool,&main_deck,1);
  printf("Community cards:\n");
  printCards(card_pool);
  printf("Your cards:\n");
  printCards(player_hand);
  player_hand.handRank = handRank(player_hand,card_pool,1);
  printf("\n");
  printf("Enter to continue.");
  scanf("%c",&dummy);
  
  printf("\n-------RIVER-------\n");
  draw(&card_pool,&main_deck,1);
  printf("Community cards:\n");
  printCards(card_pool);
  printf("Your cards:\n");
  printCards(player_hand);
  player_hand.handRank = handRank(player_hand,card_pool,1);
  printf("\n");
  printf("Enter to continue.");
  scanf("%c",&dummy);
  
  printf("\n-------REVEAL------\n");
  printf("Community cards:\n");
  printCards(card_pool);
  printf("Your cards:\n");
  printCards(player_hand);
  player_hand.handRank = handRank(player_hand,card_pool,1);
  printf("\n");
  printf("AI cards:\n");
  printCards(ai_hand);
  ai_hand.handRank = handRank(ai_hand,card_pool,1);
  printf("\n");
  
  // Determine Winner
  if(ai_hand.handRank > player_hand.handRank)
    printf("AI WINS!\n");
  else if(ai_hand.handRank > player_hand.handRank)
    printf("PLAYER WINS!\n");
  else
    printf("TIE\n");
  
  return 0;
}