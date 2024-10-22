/*************************************************************
Name: Amando Rivera
Purpose: To create a casino with a variety of games. This game is designed to simulate slots.
File name: slots.c
**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void yellow()     ///paint casino text yellow
   {
    printf("\033[0;33m"); 
   }
void red()       ///paint top and bottom of casino sign red
   {
    printf("\033[0;31m");
   }
void sign()     ///print casino sign
    {
  red();
  printf(" ABCEGF  KGE  IHG  IFL  FGK  GE   GE   EE  JGF  KFI  EHF  EGL  FGECDG\n");      
  printf("AP   LHQPIGFS GGEROHFKN EGJOPFFOK FEQMOFFP HHEROKGHN EHFSRFHJL HL   IG\n");     
  printf("B JGGF                                                          AHKKMJ\n");   
  yellow();
  printf("                                    XXX                         \n");   
  printf("       NQPNNM     QDAA     AAQOOON  MLA  FAEN  LAD    QPNQQZ    \n");    
  printf("      QA        AA    MQ   HG            IIIQQ  FH  NHA   DDA   \n");   
  printf("      QA        EA    AQ   ADCBA    ADA  IIO AAHIH  QMC   HKC   \n");       
  printf("      QB        EFXXXXXA     ADDA   FLC  IIF QIJJH  PJA   HLC   \n");
  printf("      QC        AA    AQ        HB  BFA  IIF  QQHH  MQQ   IHA   \n");
  printf("       AAAAAAW  QQ    AQ  OMAAAAAA  OQQ  CAA    AB    IAAAAS   \n");     
  red();
  printf("A JK                                                             NFJIG\n");
  printf("B IIBA                                                          AHMN L\n");    
  printf("AQ   NF  IEA  EFD  FDJ  CEI  DD Z CC   CD  NFC  JDE  CFE  CGH  FM   OA\n"); 
  printf(" ADDFHE  KIF  HHG  JGM  FIL  GF R FF VZGF  KGG ZMGH  GGG  GFLW FGDDB \033[0m\n"); 
    }

int betting(int bet)
{                      ///Prompts the user on the bets they want to wager for each slot turn
  char input;
  printf("Welcome to the slots! How much would you like to bet?\n");
  while(bet >= 0){
    printf("--------------------------------------------");
    printf("\nInstructions: \nEnter + for +$10 bet or enter - for -$10 bet\nEnter 1 to play or enter q to leave slots\n");
    printf("--------------------------------------------");
    printf("\nBet amount: $%d\n", bet);
    scanf(" %c", &input);
    if (input == '+')
    {
      bet = bet + 10;
    }
    else if(input == '-')
    {
      bet = bet - 10;       
    }
    else if (input == 'q')
    {
      printf("We're sad to see you go.\n");
      break; 
    }
    else if (input == '1')
    {
      break;
    }
    else {
        printf("Invalid input. Please try again.\n");
         }  
  }
  return bet;
} 

int slots(int amountOfBet)
{              ///Each slot has independent chances of occurring where 3 of the same garners a bonus
  char input;
  int x, y, z; 
  int money = 200;
  while (money > 0)
  {
    srand(time(NULL));        /// A player wins the jackpot if they get three 7's in a row
    int icon1 = (rand()% 100) + 1;
    int icon2 = (rand()% 50) + 3;
    int icon3 = (rand()% 80) + 2;
    printf("\nBalance $%d", money);
    printf("\nEnter 1 to spin: ");
    scanf(" %c", &input);
    if (input == '1')
    {
       money = money - amountOfBet;
       switch(icon1){
    case 1 ... 50:
      printf("1: Cherry\n");
      x = 1;
      break;
    
    case 51 ... 90:
      printf("1: Apple\n");
      x = 2;
      break;
    
    default:
      printf("1:7\n");
      x = 3;
      break;         
      }
  
  switch(icon2){
    case 3 ... 20:
      printf("2: Cherry\n");
      y = 1;
      break;
  
    case 21 ... 40:
      printf("2: Apple\n");
      y = 2;
      break;
  
    default:
      printf("2: 7\n");
      y = 3;
      break;
                }
  switch(icon3){
    case 2 ... 40:
      printf("3: Cherry\n");
      z = 1;
      break;
    
    case 41 ... 70:
      printf("3: Apple\n");
      z = 2;
      break;
    
    default:
      printf("3:7\n");
       z = 3;
       break;         
                }
  if ((z==y) & (x==y) && x != 3){
    yellow();
    printf("You have won a bonus!\033[0m\n");
    money = money + 30;
 }else if((z==y) & (x==y) && x == 3){
    yellow();
    printf("You have won the jackpot!\033[0m\n");
    money = money + 100;
 } 
    }
    else if (input == 'q')
    {
        printf("Goodbye");
    }
  }
    return money;
 
}


int main()
{                                                                                                                     
  sign();
  slots(betting(10));
	return 0;
}




