/***********************************************************
*
* Author:    Keven Duong
*
* File:     pokerAI.c
*
* Purpose:   File for poker ai.
*
* Version:   1.0 Nov 5, 2024
*
***********************************************************/

#include <stdio.h>
#include "cardops.h"
#include "handscore.h"
#include "cardart.h"

float hand_confidence(Player * player,Table * table,int cards[7],int win)
{
  int card,memory;
  float confidence=0;
  for(card=0;card<player->num_cards;card++)
  {
    for(memory=0;memory<7;memory++)
    {
      if(player->hand[card] == cards[memory])
        confidence += (float)win;
      else if(findRank(player->hand[card]) == findRank(cards[memory]))
        confidence += (float)win/2;
      else if(findSuit(player->hand[card]) == findSuit(cards[memory]))
        confidence += (float)win/2;
    }
  }
  
  for(card=0;card<table->num_cards;card++)
  {
    for(memory=0;memory<7;memory++)
    {
      if(table->card_pool[card] == cards[memory])
        confidence += (float)win/7;
      else if(findRank(table->card_pool[card]) == findRank(cards[memory]))
        confidence += (float)win/14;
      else if(findSuit(table->card_pool[card]) == findSuit(cards[memory]))
        confidence += (float)win/14;
    }
  }
  return confidence;
}

void ai_steve_bet(Player * steve,Table * table)
{
  FILE* memory = fopen("steve.txt","r");
  int cards[7];
  int win,card;
  float confidence=0;
  while(fscanf(memory,"%d%d%d%d%d%d%d%d",&cards[0],&cards[1],&cards[2],&cards[3],&cards[4],&cards[5],&cards[6],&win) != EOF)
  {
    confidence += hand_confidence(steve,table,cards,win);
  }
  printf("Steve's confidence: %f\n",confidence); 
  fclose(memory);
}

void ai_steve_remember(Player * players[2],Table * table,int winner)
{
  
}

void ai_randy();

int main()
{
  Player steve;
  Player opponent;
  Table table;
  Deck deck;
  resetHand(&steve);
  resetHand(&opponent);
  resetTable(&table);
  shuffle(&deck);
  
  playerDeal(&opponent,&deck,2);
  playerDeal(&steve,&deck,2);
  tableDeal(&table,&deck,3);
  printCards(steve.hand,steve.num_cards);
  printCards(table.card_pool,table.num_cards);
  ai_steve_bet(&steve,&table);
  
  tableDeal(&table,&deck,1);
  printCards(steve.hand,steve.num_cards);
  printCards(table.card_pool,table.num_cards);
  ai_steve_bet(&steve,&table);
  
  tableDeal(&table,&deck,1);
  printCards(steve.hand,steve.num_cards);
  printCards(table.card_pool,table.num_cards);
  ai_steve_bet(&steve,&table);
  
  
}