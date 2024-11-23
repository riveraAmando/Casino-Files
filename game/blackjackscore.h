#ifndef blackjackscore
#define blackjackscore

#include <stdio.h>

#define RANKS 13
#define SUITS 4


// Resets a counter array.
void resetCnt(int count[],int size)
{
  int cnt_index;
  for(cnt_index=0;cnt_index<size;cnt_index++)
  {
    count[cnt_index] = 0;
  }
}

// Counts # of cards of each rank or suit.
// type = RANKS or SUITS
void countCard(Player player,int card_count[],int type)
{
  resetCount(card_count,type);
  int card_index;
  for(card_index=0;card_index<player.num_cards;card_index++)
  {
    if(type == RANKS)
      card_count[findRank(player.hand[card_index])] += 1;
    else if(type == SUITS)
      card_count[findSuit(player.hand[card_index])] += 1;
    else
    {
      printf("ERROR in countCards: type arg must be RANKS(13) or SUITS(4)\n");
      return;
    }
  }
}


// Determines and assigns a score to a player's hand.
void determineBlackjackScore(Player * player)
{
  int rank;
  int score = 0;
  int count_ranks[RANKS];
  countCard((*player), count_ranks, RANKS);
  for(rank = 0; rank < RANKS; rank++){
    if (rank < 9){
      score += (rank+1)*count_ranks[rank];
    } else {
      score += 10*count_ranks[rank];
    }
  }
  if(score + (10*count_ranks[0]) <= 21){
    score += (10*count_ranks[0]);
  }
  (*player).score = score;
}

#endif