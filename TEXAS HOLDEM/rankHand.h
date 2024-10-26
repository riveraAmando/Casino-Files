#ifndef rankHand
#define rankHand

#define VALUES 13
#define SUITS 4

#include "cardSetType.h"




int calcCardSuit(int cardID)
{
  return cardID/100;
}

int calcCardValue(int cardID)
{
  return cardID - calcCardSuit(cardID)*100;
}

void compressValues(Hand hand, Hand community,int num_cards[])
{
  int i;
  num_cards[9]=2;
  for(i=0;i<VALUES;i++)
    num_cards[i]=0;
  for(i=0;i<hand.numCards;i++)
    num_cards[calcCardValue(hand.cardID[i])]+=1;
  for(i=0;i<community.numCards;i++)
    num_cards[calcCardValue(community.cardID[i])]+=1;
}

void compressSuits(Hand hand, Hand community,int num_cards[])
{
  int i;
  num_cards[0]=1;
  for(i=0;i<SUITS;i++)
    num_cards[i]=0;
  for(i=0;i<hand.numCards;i++)
    num_cards[calcCardSuit(hand.cardID[i])]+=1;
  for(i=0;i<community.numCards;i++)
    num_cards[calcCardSuit(community.cardID[i])]+=1;
}

int checkPair(Hand hand, Hand community)
{
  // Read in cards
  int num_cards[VALUES],i;
  compressValues(hand,community,num_cards);
  
    
  // Determine # of 2 card pairs
  int num_pairs = 0,largest_value;
  for(i = 0;i < VALUES;i++)
    if(num_cards[i]==2)
    {
      if(i==0)
        largest_value = 13;
      num_pairs++;
      if(largest_value!=13)
        largest_value = i;
    }
    
  // Report Value of Pair (if only a single pair)
  if(num_pairs == 1)
    return largest_value;
  else
    return -1;
}

int checkTwoPair(Hand hand, Hand community)
{
  // Read in cards
  int num_cards[VALUES],i;
  compressValues(hand,community,num_cards);
  
    
  // Determine # of 2 card pairs
  int num_pairs = 0,largest_value=0,small_value=9999;
  for(i = 0;i < VALUES;i++)
    if(num_cards[i]==2)
    {
      num_pairs++;
      if (i==0)
        largest_value = 13;
      if(largest_value!=13)
      {
        small_value = largest_value;
        largest_value = i;
      }
      else
        small_value = i;
    }
    
  // Report Values of Pairs
  if(num_pairs >= 2)
    return largest_value*100 + small_value;
  else
    return -1;
}

int checkTriple(Hand hand, Hand community)
{
  // Read in cards
  int num_cards[VALUES],i;
  compressValues(hand,community,num_cards);
  
    
  // Determine # of 3 card sets
  int num_triple = 0,largest_value=0;
  for(i = 0;i < VALUES;i++)
    if(num_cards[i]==3)
    {
      if(i==0)
        largest_value = 13;
      num_triple++;
      if(largest_value!=13)
        largest_value = i;
    }
    
  // Report Value of Triple
  if(num_triple > 0)
    return largest_value;
  else
    return -1;
}

int checkFour(Hand hand, Hand community)
{
  // Read in cards
  int num_cards[VALUES],i;
  compressValues(hand,community,num_cards);
  
    
  // Determine # of 4 card sets
  int num_four = 0,largest_value=0;
  for(i = 0;i < VALUES;i++)
    if(num_cards[i]==4)
    {
      if(i==0)
        largest_value = 13;
      num_four++;
      if(largest_value!=13)
        largest_value = i;
    }
    
  // Report Value of Triple
  if(num_four > 0)
    return largest_value;
  else
    return -1;
}

int checkStraight(Hand hand, Hand community)
{
  // Read in cards
  int num_cards[VALUES],i;
  compressValues(hand,community,num_cards);
  
  // Determine Length of Sequence
  int length_max_sequence=0,length_current_sequence=0,value_max_sequence;
  for(i=0;i<VALUES;i++)
  {
    if(num_cards[i]==0)
    {
      length_current_sequence = 0;
      continue;
    }
    
    length_current_sequence++;
    
    if(length_current_sequence >= length_max_sequence)
    {
      length_max_sequence = length_current_sequence;
      value_max_sequence = i;
    }
  }
  
  // Check for 10 to Ace
  if(length_current_sequence > 3 && num_cards[0]>0)
  {
    value_max_sequence = 13;
    length_max_sequence = ++length_current_sequence;
  }
  
  // Report Straight Value
  if(length_max_sequence >= 5)
    return value_max_sequence;
  else
    return -1;
}

int checkFlush(Hand hand, Hand community)
{
  // Read in cards
  int num_cards[SUITS];
  compressSuits(hand,community,num_cards);
  
  // Determine max number of same suits
  int max_suit_count=0,current_suit;
  for(current_suit=0;current_suit<SUITS;current_suit++)
    if(num_cards[current_suit] > max_suit_count)
      max_suit_count = num_cards[current_suit];
      
  // Report existance of flush
  if(max_suit_count >= 5)
    return 1;
  else
    return -1;
}

int checkStraightFlush(Hand hand, Hand community)
{
  // Read in cards
  int cards[SUITS][VALUES],i,j,current_suit,current_value;
  cards[0][0]=1;
  for(i=0;i<SUITS;i++)
    for(j=0;j<VALUES;j++)
      cards[i][j]=0;
  for(i=0;i<hand.numCards;i++)
  {
    current_suit = calcCardSuit(hand.cardID[i]);
    current_value = calcCardValue(hand.cardID[i]);
    cards[current_suit][current_value]=1;
  }
  for(i=0;i<community.numCards;i++)
  {
    current_suit = calcCardSuit(community.cardID[i]);
    current_value = calcCardValue(community.cardID[i]);
    cards[current_suit][current_value]=1;
  }
  
  // Determine sequences
  int length_max_sequence=0,length_current_sequence=0,value_max_sequence=-1;
  for(current_suit=0;current_suit<SUITS;current_suit++)
  {
    for(current_value=0;current_value<VALUES;current_value++)
    {
      if(cards[current_suit][current_value]==0)
      {
        length_current_sequence = 0;
        continue;
      }
      
      length_current_sequence++;
      
      if(length_current_sequence >= length_max_sequence && current_value > value_max_sequence)
      {
        length_max_sequence = length_current_sequence;
        value_max_sequence = j;
      }
    }
    // Check for 10 to Ace
    if(length_current_sequence > 3 && cards[current_suit][0]>0)
    {
      value_max_sequence = 13;
      length_max_sequence = ++length_current_sequence;
    }
  }
  
  // Report value of Straight-Flush
  if(length_max_sequence>=5)
    return value_max_sequence;
  else
    return -1;
}

int checkHighCard(Hand hand)
{
  int high_card_value = calcCardValue(hand.cardID[0]);
  int low_card_value = calcCardValue(hand.cardID[1]);
  
  if(high_card_value < low_card_value)
  {
    low_card_value = high_card_value^low_card_value;
    high_card_value = high_card_value^low_card_value;
    low_card_value = high_card_value^low_card_value;
  }
  
  // Report combined high card
  return high_card_value*100+low_card_value;
}

int handRank(Hand hand, Hand community, int print)
{
  if(checkStraightFlush(hand,community)>=0)
  {
    if(print)
      printf("(Straight-Flush)");
    return 10*10000 + checkStraightFlush(hand,community);
  }
  if(checkFour(hand,community)>=0)
  {
    if(print)
      printf("(Four-of-a-Kind)");
    return 9*10000 + checkFour(hand,community);
  }
  if(checkTriple(hand,community)>=0 && checkTwoPair(hand,community)>=0) // Full House case 1
  {
    if(print)
      printf("(Full-House)");
    return 8*10000 + checkTriple(hand,community)*100 + checkTwoPair(hand,community)/100;
  }
  if(checkTriple(hand,community)>=0 && checkPair(hand,community)>=0) // Full House case 2
  {
    if(print)
      printf("(Full-House)");
    return 8*10000 + checkTriple(hand,community)*100 + checkPair(hand,community);
  }
  if(checkFlush(hand,community)>=0)
  {
    if(print)
      printf("(Flush)");
    return 7*10000 + checkFlush(hand,community);
  }
  if(checkStraight(hand,community)>=0)
  {
    if(print)
      printf("(Straight)");
    return 6*10000 + checkStraight(hand,community);
  }
  if(checkTriple(hand,community)>=0)
  {
    if(print)
      printf("(Three-of-a-Kind)");
    return 5*10000 + checkTriple(hand,community);
  }
  if(checkTwoPair(hand,community)>=0)
  {
    if(print)
      printf("(Two Pair)");
    return 4*10000 + checkTwoPair(hand,community);
  }
  if(checkPair(hand,community)>=0)
  {
    if(print)
      printf("(Pair)");
    return 3*10000 + checkPair(hand,community)*100 + checkHighCard(hand);
  }
  
  if(print)
    printf("(High Card)");
  return checkHighCard(hand);
}

#endif