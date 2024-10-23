#ifndef cardSetType
#define cardSetType

#define MAX_CARD_COUNT 5
#define SUITS 4
#define VALUES 13

typedef struct cardGroup
{
  int numCards;
  int cardID[MAX_CARD_COUNT];
  int handRank;
  // cardID = suitID*100 + valueID
  // suitID: 0 = Hearts, 1 = Diamonds, 2 = Clubs, 3 = Spades
  // valueID: 0 = Ace ... 12 = King
}Hand;

typedef struct deck
{
  int numCards;
  int cards[SUITS][VALUES];
}Deck;


#endif