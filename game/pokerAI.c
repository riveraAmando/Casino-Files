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
#include "pokerAI.h"

float hand_confidence(Player * player,Table * table,int cards[7],int win)
{
  int card,memory;
  float confidence=0;
  int active_cards = player->num_cards + table->num_cards;
  for(card=0;card<player->num_cards;card++)
  {
    for(memory=0;memory<active_cards;memory++)
    {
      if(player->hand[card] == cards[memory])
        confidence += (float)win/active_cards;
    }
  }
  
  for(card=0;card<table->num_cards;card++)
  {
    for(memory=0;memory<active_cards;memory++)
    {
      if(table->card_pool[card] == cards[memory])
        confidence += (float)win/active_cards;
    }
  }
  return confidence;
}

void ai_steve_bet(Player * steve,Table * table)
{
  FILE* memory = fopen("steve.txt","r");
  int cards[7];
  int win,card,mem_size=0;
  float confidence=0,max_confidence=0;
  while(fscanf(memory,"%d%d%d%d%d%d%d%d",&cards[0],&cards[1],&cards[2],&cards[3],&cards[4],&cards[5],&cards[6],&win) != EOF)
  {
    mem_size++;
    confidence += hand_confidence(steve,table,cards,win);
  }
  confidence = confidence/mem_size;
  fclose(memory);
  
  float max_bet;
  if(confidence>0 && confidence<1)
  {
    max_bet = confidence*steve->money;
  }
  else if(confidence>=1)
  {
    max_bet = steve->money;
  }
  else if(confidence<0)
  {
    max_bet = -1;
  }
  
  if(max_bet >= table->high_bet)
  {
    steve->bet = (int)max_bet;
    printf("Steve bets $%d.\n",steve->bet);
  }
  else if((int)max_bet == steve->money)
  {
    steve->bet = (int)max_bet;
    printf("Steve goes all in! ($%d)\n",steve->bet);
  }
  else
  {
  //  steve->bet = -1;
    steve->fold = 1;
    printf("Steve folds.\n");
  }
}

void ai_steve_remember(Player * steve,Table * table,int win)
{
  FILE* memory = fopen("steve.txt","a");
  int i;
  for(i=0;i<steve->num_cards;i++)
    fprintf(memory,"%d ",steve->hand[i]);
  for(i=0;i<table->num_cards;i++)
    fprintf(memory,"%d ",table->card_pool[i]);
  for(i=steve->num_cards+table->num_cards;i<7;i++)
    fprintf(memory,"%d ",-1);
  if(win>0)
    fprintf(memory,"%d\n",win*steve->score/1000000);
  else
    fprintf(memory,"%d\n",win);
  fclose(memory);
}

void ai_randy_bet(Player * randy,Table * table)
{
  int decision = rand()%10+1;

  if(decision > 5 && randy->money > table->high_bet + 100)
  {
    randy->bet = table->high_bet + 100;
    printf("Randy bets $%d.\n",randy->bet);
    return;
  }
  if(decision > 1 && randy->money > table->high_bet)
  {
    randy->bet = table->high_bet;
    printf("Randy bets $%d.\n",randy->bet);
    return;
  }
  if(decision > 1 && randy->money <= table->high_bet)
  {
    randy->bet = randy->money;
    printf("Randy goes all in! ($%d)\n",randy->bet);
    return;
  }
  printf("Randy folds.\n");
  // randy->bet = -1;
  randy->fold = 1;
}

void ai_frank_bet(Player * frank,Table * table)
{
  int max_bet;

}