/********************************************************************************************
File name:
Names:
Purpose:
Date:

*********************************************************************************************/
#include <stdio.h>
#include "game_blackjack.h"
#include "game_slots.h"
#include "game_texas_holdemv6.h"

int main()
{
  int money = 1000;
  int input;
  char name[30];
  printf("Welcome to the Casino, what would you like to play? (Enter 1: poker)\n (Enter 2: blackjack)\n (Enter 3: Slot machine)\n (Enter 0: To leave casino)\n");
  
  while(input > 0 && money > 0)
  {
    scanf("%d", &input);
    if(input == 1)
    {
       poker();
    }
    if(input == 2)
    {
      blackJack();
    }
    if(input == 3)
    {
      slots();
    }
   
    
  }
  if(money == 0)
  {
    printf("Congratulations %s you're bankrupt\n", name);
  }
  if(money > 1000)
  {
    printf("Hello %s! We no longer welcome your businees", name;);
  }
  
  
}