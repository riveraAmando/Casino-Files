/*************************************************************
Name: Amando Rivera
Purpose: To create a casino with a variety of games. This game is designed to simulate slots.
File name: slots.c
**************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
void yellow()     ///paint casino text yellow
   {
    printf("\033[0;33m"); 
   }
void red()       ///paint top and bottom of casino sign red
   {
    printf("\033[0;31m");
   }

void reset()       ///paint top and bottom of casino sign red
   {
    printf("\033[0m");
   }
int betting()
{                      ///Prompts the user on the bets they want to wager for each slot turn
  int bet = 10;
  char input;
  printf("\nWelcome to the slots! How much would you like to bet?\n");
  while(bet >= 0){
    printf("--------------------------------------------\n");
    printf("\nInstructions: \nEnter + for +$10 bet or enter - for -$10 bet\nEnter 1 to play or enter q to leave slots\n");
    printf("\n--------------------------------------------\n");
    printf("Bonuses double bets, and jackpots are 10x bets");
    printf("\n--------------------------------------------");
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
    system("clear");     
  }
  return bet;
} 

void move()
{
   int x,i;
   system("clear");
   printf("--------------------------------------\n");
   printf("|1111111  111    111111 1111 1111111 |\n");
   printf("|111      111    11  11  11  111     |\n");
   printf("|1111111  111    11  11  11  1111111 |\n");
   printf("|    111  11111  11  11  11      111 |\n");
   printf("|1111111  11111  111111  11  1111111 |\n");
   printf("--------------------------------------\n");
   for(x=0; x<3; x++)
      {
       
       sleep(1);
       printf("||  1  1   ||     1   ||  1      ||\n");
       printf("||  1  1   ||  1  1   ||  1  1   ||\n");
       printf("||  1      ||  1  1   ||  1      ||\n");
       printf("||     1   ||     1   ||     1   ||\n");
       printf("--------------------------------------\n");
       
       }
       
     
}

int slotsEasy(int amountOfBet, int money)
{              ///Each slot has independent chances of occurring where 3 of the same garners a bonus
  char input;
  int x, turn=0; 
  while (money > 0)
  {        /// A player wins the jackpot if they get three 7's in a row                                           
    printf("\nBalance $%d. Bets of $%d", money, amountOfBet);
    printf("\nEnter 1 to spin or q to exit: ");
    scanf(" %1c", &input);
    if (input == '1') 
    {  
      turn++;
      money -= amountOfBet;
      move();
      system("clear");
      printf("--------------------------------------\n");
      printf("|1111111  111    111111 1111 1111111 |\n");
      printf("|111      111    11  11  11  111     |\n");
      printf("|1111111  111    11  11  11  1111111 |\n");
      printf("|    111  11111  11  11  11      111 |\n");
      printf("|1111111  11111  111111  11  1111111 |\n");
      for(x=0; x<3; x++)
      {
        
        printf("--------------------------------------\n");
        int icon1 = (rand()% 100) + 1; 
        switch(icon1) {
            case 1 ... 2:
                yellow();
                printf("|| 1111111 || 1111111 || 1111111 ||\n");
                printf("|| 1   111 || 1   111 || 1   111 ||\n");
                printf("||     111 ||     111 ||     111 ||\n");
                printf("||    1111 ||    1111 ||    1111 ||\n");
                reset();
                money = money + (amountOfBet*10);
                break;
            
            case 3 ... 8:
                yellow();
                printf("|| 1111111 || 1111111 || 1111111 ||\n");
                printf("||  11111  ||  11111  ||  11111  ||\n");
                printf("||   111   ||   111   ||   111   ||\n");
                printf("||    1    ||    1    ||    1    ||\n");
                reset();
                money = money + (amountOfBet*5);
                break;
            
            case 9 ... 17:
                yellow();
                printf("|| 1  1  1 || 1  1  1 || 1  1  1 ||\n");
                printf("|| 11 1 11 || 11 1 11 || 11 1 11 ||\n");
                printf("|| 1111111 || 1111111 || 1111111 ||\n");
                printf("|| 1111111 || 1111111 || 1111111 ||\n");
                reset();
                money = money + (amountOfBet*2);
                break;
            
            case 18 ... 28:
                yellow();
                printf("||   111   ||   111   ||   111   ||\n");
                printf("|| 1111111 || 1111111 || 1111111 ||\n");
                printf("|| 1111111 || 1111111 || 1111111 ||\n");
                printf("||    1    ||    1    ||    1    ||\n");
                reset();
                money = money + (amountOfBet*2);
                break;
    
            case 29 ... 44:
                yellow();
                printf("|| 1111111 || 1111111 || 1111111 ||\n");
                printf("|| 111 111 || 111 111 || 111 111 ||\n");
                printf("|| 11   11 || 11   11 || 11   11 ||\n");
                printf("|| 11   11 || 11   11 || 11   11 ||\n");
                reset();
                money = money + (amountOfBet*2);
                break;
    
            case 45 ... 55:
                printf("|| 1111111 || 1111111 || 1111111 ||\n");
                printf("|| 111 111 || 1   111 || 111 111 ||\n");
                printf("|| 11   11 ||     111 || 11   11 ||\n");
                printf("|| 11   11 ||    1111 || 11   11 ||\n");
                break;
    
            case 56 ... 65:
                printf("|| 1  1  1 || 1111111 || 1111111 ||\n");
                printf("|| 11 1 11 || 1   111 ||  11111  ||\n");
                printf("|| 1111111 ||     111 ||   111   ||\n");
                printf("|| 1111111 ||    1111 ||    1    ||\n");
                break;
    
            case 66 ... 75:
                printf("|| 1111111 || 1111111 ||   111   ||\n");
                printf("|| 1   111 ||  11111  || 1111111 ||\n");
                printf("||     111 ||   111   || 1111111 ||\n");
                printf("||    1111 ||    1    ||    1    ||\n");
                break;
    
            case 76 ... 85:
                printf("||   111   || 1111111 || 1111111 ||\n");
                printf("|| 1111111 || 1   111 || 111 111 ||\n");
                printf("|| 1111111 ||     111 || 11   11 ||\n");
                printf("||    1    ||    1111 || 11   11 ||\n");
                break;
    
            case 86 ... 90:
                printf("|| 1  1  1 || 1  1  1 || 1111111 ||\n");
                printf("|| 11 1 11 || 11 1 11 || 111 111 ||\n");
                printf("|| 1111111 || 1111111 || 11   11 ||\n");
                printf("|| 1111111 || 1111111 || 11   11 ||\n");
                break;
    
            default:
                printf("|| 1111111 ||   111   || 1111111 ||\n");
                printf("|| 1   111 || 1111111 || 1   111 ||\n");
                printf("||     111 || 1111111 ||     111 ||\n");
                printf("||    1111 ||    1    ||    1111 ||\n");
                break;
       
      }
    }
}
    else if (input == 'q')
      {
        printf("Goodbye\n");
        break;
      }
  }
    return money;
}
  


int slots()
{                                                                      

  srand(time(NULL));
  slotsEasy(betting(), 200);
	return 0;
}




