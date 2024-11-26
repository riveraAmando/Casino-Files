/********************************************************************************************
File name:
Names:
Purpose:
Date:

*********************************************************************************************/
#include <stdio.h>
#include "blackjack.h"
#include "slots.h"
#include "texas_holdemv6.h"

int main()
{
  int money = 1000;
  int input;
  int play_money;
  char name[20];
  printf("Please enter your name: ");
  scanf("%s",name);
  while(input > 0 && money > 0)
  {
    if(money >= 1000)
      play_money = 1000;
    else
      play_money = money;
    printf("Welcome to the Casino, what would you like to play?\n (Enter 1: poker)\n (Enter 2: blackjack)\n (Enter 3: Slot machine)\n (Enter 0: To leave casino)\n");
    printf("Current Money: $%d\n",money);
    printf("Game: ");
    scanf("%d", &input);
    if(input == 1)
    {
      money -= play_money;
      money += poker(play_money,name);
    }
    if(input == 2)
    {
      money -= play_money;
      money = money + blackJack(play_money);
    }
    if(input == 3)
    {
      money -= play_money;
      money = money + slots(play_money);
    }
   
    
  }
  if(money <= 0)
  {
    printf("Congratulations %s you're bankrupt\n", name);
    return;
  }
  if(money > 1000)
  {
    printf("Hello %s! We no longer welcome your business.\n", name);
    return;
  }
  printf("%s, come again soon!\n",name);
  
  
}