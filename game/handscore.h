#pragma once

// Swaps integers
void swapInt();

// Determine suit of card.
int findSuit();

// Determine rank of card.
int findRank();

// Determines if a card is an ACE
int isAce();

// Resets a counter array.
void resetCount();

// Counts # of cards of each rank or suit.
// type = RANKS or SUITS
void countCards();

// Determines the value of high card in hand
// and returns high card and low card ranks.
int checkHighCard();

// Determines if a single pair exists and
// returns the rank of the pair
int checkPair();

// Determines if two or more pairs exist and
// returns the two highest pair ranks
int checkTwoPair();

// Determines if a three-of-a-kind exists and
// returns rank of the set.
int checkTriple();

// Determines if a four-of-a-kind exists and
// returns the rank of the set.
int checkFour();

// Determines if a straight exists and returns
// the rank of the highest card involved.
int checkStraight();

// Determines if a flush exists and returns
// 1 if true and -1 if false
int checkFlush();

// Determines if a straight-flush exists and returns
// highest rank involved
int checkStraightFlush();

// Determines if a full-house exists
// and returns the ranks of the two sets.
int checkFullHouse();

// Determines and assigns a score to a player's hand.
void determineScore();
