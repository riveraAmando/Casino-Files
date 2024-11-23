#include <stdio.h>
#include "cardops.h"

#define RANKS 13
#define SUITS 4

// Swaps integers
void swapInt(int * a,int * b)
{
  *a = *a^*b;
  *b = *a^*b;
  *a = *a^*b;
}

// Determine suit of card.
int findSuit(int cardID)
{
  return cardID/100;
}

// Determine rank of card.
int findRank(int cardID)
{
  return cardID - findSuit(cardID)*100;
}

// Determines if a card is an ACE
int isAce(int cardID)
{
  if(findRank(cardID)==0)
    return 1;
    
  return 0;
}

// Resets a counter array.
void resetCount(int count[],int size)
{
  int cnt_index;
  for(cnt_index=0;cnt_index<size;cnt_index++)
  {
    count[cnt_index] = 0;
  }
}

// Counts # of cards of each rank or suit.
// type = RANKS or SUITS
void countCards(Player player,Table table,int card_count[],int type)
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
  for(card_index=0;card_index<table.num_cards;card_index++)
  {
    if(type == RANKS)
      card_count[findRank(table.card_pool[card_index])] += 1;
    else if(type == SUITS)
      card_count[findSuit(table.card_pool[card_index])] += 1;
    else
    {
      printf("ERROR in countCards: type arg must be RANKS(13) or SUITS(4)\n");
      return;
    }
  }
}

// Determines the value of high card in hand
// and returns high card and low card ranks.
int checkHighCard(Player player)
{
  int high_card = findRank(player.hand[0]);
  int low_card = findRank(player.hand[1]);
  
  if(isAce(high_card))
    high_card = 13;
  if(isAce(low_card))
    low_card = 13;
  
  if(high_card < low_card)
    swapInt(&high_card,&low_card);
    
  return high_card*100 + low_card;
}

// Determines if a single pair exists and
// returns the rank of the pair
int checkPair(Player player,Table table)
{
  int count_rank[RANKS];
  countCards(player,table,count_rank,RANKS);
  
  int num_pairs=0,rank,pair_rank;
  for(rank=0;rank<RANKS;rank++)
  {
    if(count_rank[rank] == 2)
    {
      if(isAce(rank))
        pair_rank = 13;
      num_pairs++;
      if(pair_rank != 13)
        pair_rank = rank;
    }
  }
  
  if(num_pairs >= 1)
    return pair_rank;
  else
    return -1;
}

// Determines if two or more pairs exist and
// returns the two highest pair ranks
int checkTwoPair(Player player, Table table)
{
  int count_rank[RANKS];
  countCards(player,table,count_rank,RANKS);
  
  int num_pairs=0,rank,pair_rank[2]={0,0}; // pair_rank[0] is largest
  for(rank=0;rank<RANKS;rank++)
  {
    if(count_rank[rank] == 2)
    {
      num_pairs++;
      if(isAce(rank))
        pair_rank[0] = 13;
      if(pair_rank[0] != 13)
      {
        pair_rank[1] = pair_rank[0];
        pair_rank[0] = rank;
      }
      else
        pair_rank[1] = rank;
    }
  }
  
  if(num_pairs >= 2)
    return pair_rank[0]*100 + pair_rank[1];
  else
    return -1;
}

// Determines if a three-of-a-kind exists and
// returns rank of the set.
int checkTriple(Player player,Table table)
{
  int count_rank[RANKS];
  countCards(player,table,count_rank,RANKS);
  
  int num_triple=0,rank,triple_rank;
  for(rank=0;rank<RANKS;rank++)
  {
    if(count_rank[rank] == 3)
    {
      if(isAce(rank))
        triple_rank = 13;
      num_triple++;
      if(triple_rank != 13)
        triple_rank = rank;
    }
  }
  
  if(num_triple > 0)
    return triple_rank;
  else
    return -1;
}

// Determines if a four-of-a-kind exists and
// returns the rank of the set.
int checkFour(Player player,Table table)
{
  int count_rank[RANKS];
  countCards(player,table,count_rank,RANKS);
  
  int num_four=0,rank,four_rank;
  for(rank=0;rank<RANKS;rank++)
  {
    if(count_rank[rank] == 4)
    {
      if(isAce(rank))
        four_rank = 13;
      num_four++;
      if(four_rank != 13)
        four_rank = rank;
    }
  }
  
  if(num_four > 0)
    return four_rank;
  else
    return -1;
}

// Determines if a straight exists and returns
// the rank of the highest card involved.
int checkStraight(Player player,Table table)
{
  int count_rank[RANKS];
  countCards(player,table,count_rank,RANKS);
  
  int max_seq_length=0,current_seq_length=0,max_rank,rank;
  for(rank=0;rank<RANKS;rank++)
  {
    if(count_rank[rank]==0)
    {
      current_seq_length = 0;
      continue;
    }
    current_seq_length++;
    if(current_seq_length >= max_seq_length)
    {
      max_seq_length = current_seq_length;
      max_rank = rank;
    }
  }
  
  // Check 10 - Ace
  if(current_seq_length>=4 && count_rank[0]>0)
  {
    max_rank = 13;
    max_seq_length = ++current_seq_length;
  }
  
  if(max_seq_length >= 5)
    return max_rank;
  else
    return -1;
}

// Determines if a flush exists and returns
// 1 if true and -1 if false
int checkFlush(Player player,Table table)
{
  int count_suit[SUITS];
  countCards(player,table,count_suit,SUITS);
  
  int max_suit_count=0,suit;
  for(suit=0;suit<SUITS;suit++)
    if(count_suit[suit] > max_suit_count)
      max_suit_count = count_suit[suit];
      
  if(max_suit_count >=5)
    return 1;
  else
    return -1;
}

// Determines if a straight-flush exists and returns
// highest rank involved
int checkStraightFlush(Player player,Table table)
{
  int cards[SUITS][RANKS],suit,rank,card_index;
  for(suit=0;suit<SUITS;suit++)
    for(rank=0;rank<RANKS;rank++)
      cards[suit][rank] = 0;
  for(card_index=0;card_index<player.num_cards;card_index++)
  {
    suit = findSuit(player.hand[card_index]);
    rank = findRank(player.hand[card_index]);
    cards[suit][rank] = 1;
  }
  for(card_index=0;card_index<table.num_cards;card_index++)
  {
    suit = findSuit(table.card_pool[card_index]);
    rank = findRank(table.card_pool[card_index]);
    cards[suit][rank] = 1;
  }
  
  int max_seq_len=0;
  int current_seq_len=0;
  int max_rank=-1;
  for(suit=0;suit<SUITS;suit++)
  {
    current_seq_len = 0;
    for(rank=0;rank<RANKS;rank++)
    {
      if(cards[suit][rank]==0)
      {
        current_seq_len = 0;
        continue;
      }
      current_seq_len++;
      if(current_seq_len >= max_seq_len && rank > max_rank)
      {
        max_seq_len = current_seq_len;
        max_rank = rank;
      }
    }
    if(current_seq_len>=4 && cards[suit][0]>0)
    {
      max_rank = 13;
      max_seq_len = ++current_seq_len;
    }
  }
  
  if(max_seq_len >=5)
    return max_rank;
  else
    return -1;
}

// Determines if a full-house exists
// and returns the ranks of the two sets.
int checkFullHouse(Player player,Table table)
{
  int count_rank[RANKS];
  countCards(player,table,count_rank,RANKS);
  
  int num_pairs=0,num_triple=0,rank,pair_rank[2]={-1,-1},triple_rank[2]={-1,-1};
  for(rank=0;rank<RANKS;rank++)
  {
    if(count_rank[rank] == 2)
    {
      num_pairs++;
      if(isAce(rank))
        pair_rank[0] = 13;
      if(pair_rank[0] != 13)
      {
        pair_rank[1] = pair_rank[0];
        pair_rank[0] = rank;
      }
      else
        pair_rank[1] = rank;
    }
    if(count_rank[rank] == 3)
    {
      num_triple++;
      if(isAce(rank))
        triple_rank[0] = 13;
      if(triple_rank[0] != 13)
      {
        triple_rank[1] = triple_rank[0];
        triple_rank[0] = rank;
      }
      else
        triple_rank[1] = rank;
    }
  }
  
  if(num_triple > 1)
    return triple_rank[0]*100 + triple_rank[1];
  else if(num_triple == 1 && num_pairs > 0)
    return triple_rank[0]*100 + pair_rank[0];
  else
    return -1;
}

// Determines and assigns a score to a player's hand.
void determineScore(Player * player,Table table,int print,int newline)
{
  int rating;
  int type_value = 1000000;
  if(checkStraightFlush(*player,table)>=0)
  {
    if(print)
      printf("(Straight-Flush)");
    rating = 9*type_value + checkStraightFlush(*player,table);
  }
  else if(checkFour(*player,table)>=0)
  {
    if(print)
      printf("(Four-of-a-Kind)");
    rating = 8*type_value + checkFour(*player,table);
  }
  else if(checkFullHouse(*player,table)>=0)
  {
    if(print)
      printf("(Full-House)");
    rating = 7*type_value + checkFullHouse(*player,table);
  }
  else if(checkFlush(*player,table)>=0)
  {
    if(print)
      printf("(Flush)");
    rating = 6*type_value + checkFlush(*player,table);
  }
  else if(checkStraight(*player,table)>=0)
  {
    if(print)
      printf("(Straight)");
    rating = 5*type_value + checkStraight(*player,table);
  }
  else if(checkTriple(*player,table)>=0)
  {
    if(print)
      printf("(Three-of-a-Kind)");
    rating = 4*type_value + checkTriple(*player,table)*10000 + checkHighCard(*player);
  }
  else if(checkTwoPair(*player,table)>=0)
  {
    if(print)
      printf("(Two Pair)");
    rating = 3*type_value + checkTwoPair(*player,table)*100 + checkHighCard(*player)/100;
  }
  else if(checkPair(*player,table)>=0)
  {
    if(print)
      printf("(One Pair)");
    rating = 2*type_value + checkPair(*player,table)*10000 + checkHighCard(*player);
  }
  else
  {
    if(print)
      printf("(High Card)");
    rating = checkHighCard(*player);
  }
  if(print && newline)
    printf("\n");
    
  (*player).score = rating;
}