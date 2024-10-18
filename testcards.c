// Keven Duong
// Test for Poker Deck and Hand Calculations

/********************************************************
*
* Notes:
* 1. Straight checking does not include Ace, King, Queen,
*    Jack, 10
* 2. Ace is treated as a low card
* 3. Need to check for straight flushes
* 4. Overall efficiency and readability is bad
*
*********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SUITS 4
#define VALUES 13
#define STATES 9 // Types of Poker Hands

// 0 high card, 1 one pair, 2 two pair, 3 threeofakind, 4 straight, 5 flush, 6 full house, 7 fourofakind, 8 straightflush


/* MISCELLANEOUS FUNCTIONS */
void printCards(int c[SUITS][VALUES])
{
  int i,j;
  for (i=0;i<SUITS;i++)
  {
    for (j=0;j<VALUES;j++)
      printf("%d ",c[i][j]);
    printf("\n");
  }
}

int noCards(int set[SUITS][VALUES])
{
  int suit,value;
  
  for (suit=0;suit<SUITS;suit++)
    for (value=0;value<VALUES;value++)
      if (set[suit][value]>0)
        return 0;

  return 1;
}
/*********************************/


/* HAND AND DECK SETUP FUNCTIONS */
void fillCards(int d[SUITS][VALUES])
{
  int i,j;
  for (i=0;i<SUITS;i++)
    for (j=0;j<VALUES;j++)
      d[i][j] = 1;
}

void emptyCards(int h[SUITS][VALUES])
{
  int i,j;
  for (i=0;i<SUITS;i++)
    for (j=0;j<VALUES;j++)
      h[i][j] = 0;
}
/*********************************/


/* CARD IDENTIFICATION FUNCTIONS*/
char* cardSuit(int suitID)
{
  switch(suitID)
  {
    case 0:
      return "Hearts";
      break;
    case 1:
      return "Diamonds";
      break;
    case 2:
      return "Clubs";
      break;
    case 3:
      return "Spades";
      break;
    default:
      return "Unknown Suit";
  }
}

char* cardValue(int valueID)
{
  switch(valueID)
  {
    case 0:
      return "Ace";
      break;
    case 1:
      return "2";
      break;
    case 2:
      return "3";
      break;
    case 3:
      return "4";
      break;
    case 4:
      return "5";
      break;
    case 5:
      return "6";
      break;
    case 6:
      return "7";
      break;
    case 7:
      return "8";
      break;
    case 8:
      return "9";
      break;
    case 9:
      return "10";
      break;
    case 10:
      return "Jack";
      break;
    case 11:
      return "Queen";
      break;
    case 12:
      return "King";
      break;
  }
  return "Unknown Value";
}

void whatCards(int c[SUITS][VALUES])
{
  int i,j;
  for (i=0;i<SUITS;i++)
    for (j=0;j<VALUES;j++)
      if (c[i][j] == 1)
        printf("%s of %s\n",cardValue(j),cardSuit(i));
}

void printHandType(int handState[STATES])
{
  int handType=0,i;
  for (i=0;i<STATES;i++)
    if (handState[i]>0)
      handType = i;
  switch(handType)
  {
    case 0:
      printf("(High Card)\n");
      break;
    case 1:
      printf("(One Pair)\n");
      break;
    case 2:
      printf("(Two Pair)\n");
      break;
    case 3:
      printf("(Three-of-a-Kind)\n");
      break;
    case 4:
      printf("(Straight)\n");
      break;
    case 5:
      printf("(Flush)\n");
      break;
    case 6:
      printf("(Full House)\n");
      break;
    case 7:
      printf("(Four-of-a-Kind)\n");
      break;
    case 8:
      printf("(Straight Flush)\n");
      break;
  }
}
/*********************************/


/* CARD OPERATION FUNCTIONS */
void drawCards(int h[SUITS][VALUES],int d[SUITS][VALUES],int cards)
{
  int suit, value,drawnum;
  
  for(drawnum=1;drawnum<=cards;drawnum++)
  {
    if(noCards(d))
    {
      printf("Source is empty.\n");
      return;
    }
    
    do{
      suit = rand()%4;
      value = rand()%13;
    }while(d[suit][value]==0);
    d[suit][value]--;
    h[suit][value]++;
  }
}

void updatePool(int pool[SUITS][VALUES],int update[SUITS][VALUES])
{
  int i,j;
  for (i=0;i<SUITS;i++)
    for (j=0;j<VALUES;j++)
      pool[i][j] = pool[i][j] | update[i][j];

}

void checkMatch(int set[SUITS][VALUES],int handState[STATES])
{
  int i,j;
  int numPairs=0,pairSize=0,pairValue=0,lowValue = 0;
  int valueCnt[VALUES]={0,0,0,0,0,0,0,0,0,0,0,0,0};
  // Read Values in Set
  for (i=0;i<SUITS;i++)
    for (j=0;j<VALUES;j++)
      if (set[i][j] == 1)
        valueCnt[j]++;
  
  // Determine Pairs
  for (i=0;i<VALUES;i++)
    if (valueCnt[i] > 1)
    {
      numPairs++;
      if (valueCnt[i] >= pairSize) // Highest Matching Cards
      {
        if (pairValue < i+1)
          pairValue = i+1;
        pairSize = valueCnt[i];
      }
    }
  if (numPairs > 1)
  {
    for (i=0;i<VALUES;i++)
      if (valueCnt[i] == 2)
        if (i+1 < pairValue)
          lowValue = i+1;
  }

  // Update Data
  if (numPairs == 1) // Single Sets
  {
    switch(pairSize)
    {
      case 2: // One Pair Case
        handState[1]=pairValue;
        break;
      case 3: // Three of a Kind Case
        handState[3]=pairValue;
        break;
      case 4: // Four of a Kind Case
        handState[7]=pairValue;
        break;
    }
  }
  else if (numPairs>1) // Two Pair or Full House
  {
    switch(pairSize)
    {
      case 2: // Two Pair Case
        handState[2] = pairValue*100 + lowValue;
        break;
      case 3: // Full House Case
        handState[6] = pairValue*100 + lowValue;
        break;
      case 4: // Four of a Kind with an extra pair
        handState[7]=pairValue;
        break;
    }
  }
  
}

void checkFlush(int set[SUITS][VALUES],int handState[STATES])
{
  int i,j;
  int suitCnt[SUITS]={0,0,0,0};
  
  // Read In Suits
  for (i=0;i<SUITS;i++)
    for (j=0;j<VALUES;j++)
      if (set[i][j] == 1)
        suitCnt[i]++;

  // Determine if Flush
  for (i=0;i<SUITS;i++)
  {
    if(suitCnt[i] >= 5)
    {
      handState[5] = 1;
    }
  }
}

void checkStraight(int set[SUITS][VALUES],int handState[STATES])
{
  int i,j;
  int sequence=0,s=0,max=0;
  int values[VALUES]={0,0,0,0,0,0,0,0,0,0,0,0,0};
  // Read Values in Set
  for (i=0;i<SUITS;i++)
    for (j=0;j<VALUES;j++)
      if (set[i][j] == 1)
        values[j]=1;
        
  // Look for Sequences
  for (i=0;i<VALUES;i++)
  {
    if (values[i] == 1)
    {
      s++;
      if (s>sequence)
      {
        sequence = s;
        if(i+1 > max)
          max = i+1;
      }
    }
    else
      s=0;
  }
  
  // Determine if Straight
  if (sequence >=5)
    handState[4] = max;
    
}
/*********************************/

int main()
{

  srand(time(0));
  int deck[SUITS][VALUES],hand[SUITS][VALUES],tableCards[SUITS][VALUES],cardPool[SUITS][VALUES];
  int handState[STATES]={0,0,0,0,0,0,0,0,0}; 
  char dummy;
  // Setup
  fillCards(deck);
  emptyCards(hand);
  emptyCards(cardPool);
  emptyCards(tableCards);
  
  // Starting Hand
  
  printf("\e[1;1H\e[2J");

  printf("------Before Flop------\n");
  drawCards(hand,deck,2);
  printf("Your Hand:\n");
  whatCards(hand);
  updatePool(cardPool,hand);
  checkMatch(cardPool,handState);
  checkFlush(cardPool,handState);
  checkStraight(cardPool,handState);
  printHandType(handState);
  printf("Enter anything to continue.");
  scanf("%c",&dummy);
  
  // The Flop
  printf("\e[1;1H\e[2J");
  printf("---------Flop---------\n");
  drawCards(tableCards,deck,3);
  printf("Table:\n");
  whatCards(tableCards);
  printf("\nYour Hand:\n");
  whatCards(hand);
  updatePool(cardPool,tableCards);
  checkMatch(cardPool,handState);
  checkFlush(cardPool,handState);
  checkStraight(cardPool,handState);
  printHandType(handState);
  printf("Enter anything to continue.");
  scanf("%c",&dummy);
  
  
  // The Turn
  printf("\e[1;1H\e[2J");
  printf("---------Turn---------\n");
  drawCards(tableCards,deck,1);
  printf("Table:\n");
  whatCards(tableCards);
  printf("\nYour Hand:\n");
  whatCards(hand);
  updatePool(cardPool,tableCards);
  checkMatch(cardPool,handState);
  checkFlush(cardPool,handState);
  checkStraight(cardPool,handState);
  printHandType(handState);
  printf("Enter anything to continue.");
  scanf("%c",&dummy);
  
  
  // The River
  printf("\e[1;1H\e[2J");
  printf("---------River---------\n");
  drawCards(tableCards,deck,1);
  printf("Table:\n");
  whatCards(tableCards);
  printf("\nYour Hand:\n");
  whatCards(hand);
  updatePool(cardPool,tableCards);
  checkMatch(cardPool,handState);
  checkFlush(cardPool,handState);
  checkStraight(cardPool,handState);
  printHandType(handState);
  
}