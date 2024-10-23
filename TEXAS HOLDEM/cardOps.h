#ifndef cardOps
#define cardOps

#define SUITS 4
#define VALUES 13

void fillDeck(Deck * d)
{
  (*d).numCards = SUITS*VALUES;
  int suit,value;
  for (suit=0;suit<SUITS;suit++)
    for(value=0;value<VALUES;value++)
      (*d).cards[suit][value] = 1;
}

void emptyHand(Hand * cards)
{
  (*cards).numCards = 0;
//  int i;
//  for (i=0;i<MAX_CARD_COUNT;i++)
//    cards.cardID[i] = 0;
}

void draw(Hand * hand,Deck * d, int amount)
{
  if ((*d).numCards == 0)
    return;
  
  int i,suit,value;
  for(i=0;i<amount;i++)
  {
    do{
      suit  = rand()%SUITS;
      value = rand()%VALUES;
    }while((*d).cards[suit][value]==0);
    
    (*hand).cardID[(*hand).numCards] = suit*100 + value;
    (*d).cards[suit][value]--;
    
    (*hand).numCards++;
    (*d).numCards--;
  }
}

#endif