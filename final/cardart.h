#ifndef cardart
#define cardart

#include <stdio.h>

#define LINES 6
#define CHARS 50

/****************************************************
*                                                   *
*  How to use:                                      *
*  Most functions require a cardID to identify      *
*  the card you wish to display. The ID is defined  *
*  as suitID*100 + rankID.                          *
*  suitID: 0=Hearts,1=Diamonds,2=Clubs,3=Spades     *
*  rankID: 0=Ace,1=Two,...,12 = King                *
*                                                   *
****************************************************/

// Reads in card template
void blankCard(char card[LINES][CHARS])
{
  FILE* temp = fopen("blank_card.txt","r");
  int i;
  for(i=0;i<LINES;i++)
  {
    fgets(card[i],CHARS,temp);
  }
  fclose(temp);
}

// Adds suit to template
void addSuit(char card[LINES][CHARS],int cardID)
{
  switch(cardID/100)
  {
  case 0: // Hearts
    card[1][2] = '_';
    card[1][4] = '_';
    card[2][1] = '(';
    card[2][3] = 'v';
    card[2][5] = ')';
    card[3][2] = '\\';
    card[3][4] = '/';
    card[4][3] = 'V';
    break;
  case 1: // Diamonds
    card[1][3] = '^';
    card[2][2] = '/';
    card[2][4] = '\\';
    card[3][2] = '\\';
    card[3][4] = '/';
    card[4][3] = 'v';
    break;
  case 2: // Clubs
    card[1][3] = '_';
    card[2][2] = '(';
    card[2][4] = ')';
    card[3][1] = '(';
    card[3][2] = '_';
    card[3][3] = 39;
    card[3][4] = '_';
    card[3][5] = ')';
    card[4][3] = '|';
    break;
  case 3: // Spades
    card[1][3] = '.';
    card[2][2] = '/';
    card[2][3] = '.';
    card[2][4] = '\\';
    card[3][1] = '(';
    card[3][2] = '_';
    card[3][3] = '.';
    card[3][4] = '_';
    card[3][5] = ')';
    card[4][3] = '|';
    break;
  }
}

// Adds rank to template
void addValue(char card[LINES][CHARS],int cardID)
{
  int value = cardID - (cardID/100)*100;
  switch(value)
  {
  case 0:
    card[1][1] = 'A';
    card[5][5] = 'A';
    break;
  case 1 ... 8:
    card[1][1] = 49+value;
    card[5][5] = 49+value;
    break;
  case 9:
    card[1][1] = '1';
    card[1][2] = '0';
    card[5][4] = '1';
    card[5][5] = '0';
    break;
  case 10:
    card[1][1] = 'J';
    card[5][5] = 'J';
    break;
  case 11:
    card[1][1] = 'Q';
    card[5][5] = 'Q';
    break;
  case 12:
    card[1][1] = 'K';
    card[5][5] = 'K';
    break;
  }
}

// Combines multiple cards for printing
void combineCards(char set[LINES][CHARS],char card[LINES][CHARS])
{
  int i,j,gap;
  for(i=0;i<LINES;i++)
  {
    gap = 0;
    for(j=0;j<CHARS;j++)
    {
      if(set[i][j] != '\0' && set[i][j] != '\r' && set[i][j] != '\n')
      {
        gap+=1;
        continue;
      }
      set[i][j] = card[i][j-gap];
    } 
  }
}

// Prints art row by row
void printArt(char cards[LINES][CHARS])
{
  int i;
  for(i=0;i<LINES;i++)
    printf("%s",cards[i]);
}

// Setup for card art array
void clearCards(char set[LINES][CHARS])
{
  int i,j;
  for(i=0;i<LINES;i++)
    for(j=0;j<CHARS;j++)
      set[i][j] = '\0';
}

// Adds the rank and suit to card art
void determineCard(char card[LINES][CHARS],int cardID)
{
  clearCards(card);
  blankCard(card);
  addSuit(card,cardID);
  addValue(card,cardID);
}

// Prints several cards at a time from ID array
void printCards(int cardID[],int num_cards)
{
  char card[num_cards][LINES][CHARS],hand[LINES][CHARS];
  int i;
  clearCards(hand);
  for(i=0;i<num_cards;i++)
  {
    determineCard(card[i],cardID[i]);
    combineCards(hand,card[i]);
  }
  printArt(hand);
  printf("\n");
}

#endif