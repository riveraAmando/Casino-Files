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
*            1.2 Oct 25, 2024 (added card visuals to game and updated
*                              pair tie breaker)
*
***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cardart.c"
#include "cardSetType.h"
#include "readCards.h"
#include "cardOps.h"
#include "rankHand.h"

void clearScreen()
{
  printf("\e[1;1H\e[2J");
}

void waitForInput()
{
  char dummy;
  printf("\nEnter to continue.");
  scanf("%c",&dummy);
  clearScreen();
}




int main()
{
  
  // Game Setup
  srand(time(NULL));
  Deck main_deck;
  Hand player_hand;
  Hand ai_hand;
  Hand card_pool;
  clearScreen();
  
  // Round Setup
  fillDeck(&main_deck);
  emptyHand(&player_hand);
  emptyHand(&ai_hand);
  emptyHand(&card_pool);
  draw(&player_hand,&main_deck,2);
  draw(&ai_hand,&main_deck,2);
  
  printf("-------BLIND-------\n");
  printf("Your Hand:\n");
  printHand(player_hand.cardID,player_hand.numCards);
  handRank(player_hand,card_pool,1);
  
  waitForInput();
  
  printf("--------FLOP-------\n");
  printf("Community Cards:\n");
  draw(&card_pool,&main_deck,3);
  printHand(card_pool.cardID,card_pool.numCards);
  printf("\nYour Hand:\n");
  printHand(player_hand.cardID,player_hand.numCards);
  handRank(player_hand,card_pool,1);
  printf("\n");
  
  waitForInput();
  
  printf("--------TURN-------\n");
  printf("Community Cards:\n");
  draw(&card_pool,&main_deck,1);
  printHand(card_pool.cardID,card_pool.numCards);
  printf("\nYour Hand:\n");
  printHand(player_hand.cardID,player_hand.numCards);
  handRank(player_hand,card_pool,1);
  printf("\n");
  
  waitForInput();
  
  printf("-------RIVER-------\n");
  printf("Community Cards:\n");
  draw(&card_pool,&main_deck,1);
  printHand(card_pool.cardID,card_pool.numCards);
  printf("\nYour Hand:\n");
  printHand(player_hand.cardID,player_hand.numCards);
  handRank(player_hand,card_pool,1);
  printf("\n");
  
  waitForInput();
  
  printf("-------REVEAL------\n");
  printf("Community Cards:\n");
  printHand(card_pool.cardID,card_pool.numCards);
  printf("\nYour Hand:\n");
  printHand(player_hand.cardID,player_hand.numCards);
  player_hand.handRank = handRank(player_hand,card_pool,1);
  printf("\n");
  printf("\nAI Hand:\n");
  printHand(ai_hand.cardID,ai_hand.numCards);
  ai_hand.handRank = handRank(ai_hand,card_pool,1);
  printf("\n");
  
  // Determine Winner
  if(ai_hand.handRank > player_hand.handRank)
    printf("\nAI WINS!\n");
  else if(ai_hand.handRank < player_hand.handRank)
    printf("\nPLAYER WINS!\n");
  else
    printf("\nTIE\n");
  
  return 0;
}