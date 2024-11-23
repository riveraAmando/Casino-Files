#ifndef cardart
#define cardart


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
void blankCard();

// Adds suit to template
void addSuit();

// Combines multiple cards for printing
void combineCards();

// Prints art row by row
void printArt();

// Setup for card art array
void clearCards();

// Adds the rank and suit to card art
void determineCard();

// Prints several cards at a time from ID array
void printCards();

#endif