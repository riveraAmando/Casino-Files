#ifndef readCards
#define readCards

/*******************************************
*  Determines the Suit and Value from 
*  cardID.
*******************************************/

char* cardSuit(int cardID)
{
  switch(cardID/100)
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

char* cardValue(int cardID)
{
  switch(cardID - (cardID/100)*100)
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

void printCards(Hand cards)
{
  int i;
  for (i=0;i<cards.numCards;i++)
    printf("%s of %s\n",cardValue(cards.cardID[i]),cardSuit(cards.cardID[i]));

}

#endif