/***********************************************************
*
* Author:    Keven Duong
*
* File:      texas_holdem2.c
*
* Purpose:   Main file for texas holdem game.
*
* Version:   1.0 Oct 27, 2024
*
***********************************************************/

#include "cardart.h"
#include "cardops.h"
#include "handscore.h"
#include "outops.h"

// Resets game state
void resetGame(Player player[],Deck * deck,Table * table,int num_players)
{
  shuffle(deck);
  resetTable(table);
  int p;
  for(p=0;p<num_players;p++)
    resetHand(&player[p]);
}

// Gives starting money to ai
void addAIMoney(Player player[],int num_players)
{
  int ai;
  for(ai=1;ai<num_players;ai++)
  {
    player[ai].money = 1000;
  }
}

// Deals cards to all players
void dealCards(Player player[],Deck * deck,int num_players)
{
  int p;
  for(p=0;p<num_players;p++)
  {
    playerDeal(&player[p],deck,2);
  }
}

// Finds the next player in the turn order
int nextPlayer(int current_player,int num_players,int turns)
{
  int next_player,turn;
  for(turn=0;turn<turns;turn++)
  {
    if(++current_player >= num_players)
      next_player = 0;
    else
      next_player = current_player;
  }
  return next_player;
}

// Resolves blinds
void startBlind(Player player[],Table * table,int num_players, int dealer)
{
  int blind = 100;
  (*table).high_bet = blind;
  player[nextPlayer(dealer,num_players,1)].bet = blind;
  player[nextPlayer(dealer,num_players,2)].bet = blind/2;
  (*table).pot += blind + blind/2;
}

// Shows table state to user
void printTableState(Table table,int dealer)
{
  printf("Current Pot: $%d\nHighest Bet: $%d\n",table.pot,table.high_bet);
  if(table.num_cards > 0)
    printCards(table.card_pool,table.num_cards);
  else
    printf("\n\n\n\n\n\n");
}

// Shows a player's hand state to user
void printHandState(Player player,Table table)
{
  printf("Your Hand:\n");
  printCards(player.hand,player.num_cards);
  determineScore(&player,table,1,1);
  printf("Money: $%d\n",player.money);
  printf("Current Bet: $%d\n",player.bet);
}

// Prompts User for an integer with type error checking
int scanInt(int * variable)
{
  int good_scan;
  while(1)
  {
    good_scan = scanf("%d",variable);
    if(good_scan == 0)
    {
      printf("Invalid input, please try again.\n");
      *variable = 0;
      continue;
    }
    else
      break;
  }
  return good_scan;
}

// Prompts user to reply with 'y' or 'n'
// and returns a 1 or 0;
int promptYN(char * yn)
{
  int ans;
  while(1)
  {
    scanf(" %c",yn);
    if(*yn == 'y' || *yn == 'Y')
      return 1;
    else if(*yn = 'n' || *yn == 'N')
      return 0;
    else
    {
      printf("Invalid entry, please try again.\n");
    }
  }
}

// Prompts user for a bet.
void getBetFromPlayer(Player * player, Table * table)
{
  int good_scan;
  char all_in,call;
  while((*player).bet < (*table).high_bet)
  {
    printf("How much do you want to bet? (-1 to fold) ");
    scanInt(&(*player).bet);
    // Fold
    if((*player).bet < 0)
    {
      (*player).fold = 1;
      (*player).money -= (*player).bet;
      (*player).bet = 0;
      break;
    }  
    // All in
    if((*player).bet > (*player).money || (*table).high_bet > (*player).money)
    {
      printf("Do you want to go all-in? (y/n) ");
      if(promptYN(&all_in))
      {
        (*player).bet = (*player).money;
        if((*player).bet > (*table).high_bet)
          (*table).high_bet = (*player).bet;
        break;
      }
      else
      {
        (*player).bet = 0;
        continue;
      }
    }
    // Call
    if((*player).bet < (*table).high_bet)
    {
      printf("Do you want to call? (y/n) "); 
      if(promptYN(&call))
      {
        (*player).bet = (*table).high_bet;
        break;
      }
      else
      {
        (*player).bet = 0;
        continue;
      }
    }
    // Raise
    if((*player).bet > (*table).high_bet)
    {
      (*table).high_bet = (*player).bet;
      break;
    }
  }
}

// Collects bets from around the table
void bettingRound(Player player[],Table * table,int num_players,int * turn_player)
{
  printf("--------------------------\n");
  int passes=0;
  while(1)
  {
    if(player[*turn_player].fold == 1)
    {
      *turn_player = nextPlayer(*turn_player,num_players,1);
      continue;
    }
    // Needs workshopping to account for big blind //
    if(player[*turn_player].bet == (*table).high_bet && (*table).high_bet > 0)
      break;
    else if(passes <= num_players && (*table).high_bet == 0)
      passes++;
    else if(passes > num_players && (*table).high_bet == 0)
      break;
      
    if(*turn_player == 0)
    {
      getBetFromPlayer(&player[0],table);
      *turn_player = nextPlayer(*turn_player,num_players,1);
      continue;
    }
    else
    {
      // Replace with AI code //
      if(player[*turn_player].money < (*table).high_bet)
      {
        player[*turn_player].fold = 1;
        player[*turn_player].money -= player[*turn_player].bet;
        printf("AI %d Folds.\n",*turn_player);
        *turn_player = nextPlayer(*turn_player,num_players,1);
        sleep(1);
        continue;
      }
      else
      {
        player[*turn_player].bet = (*table).high_bet;
        printf("AI %d Calls.\n",*turn_player);
        *turn_player = nextPlayer(*turn_player,num_players,1);
        sleep(1);
        continue;
      }
    }
  }
  int i;
  for(i=0;i<num_players;i++)
  {
    (*table).pot += player[i].bet;
    player[i].money -= player[i].bet;
    player[i].bet = 0;
  }
  (*table).high_bet = 0;
}

int main()
{
  srand(time(0));
  int user_money = 1000;
  
  // Determine # of players (player 0 is the user)
  int num_players,good_scan;
  
  /* FIX WHEN USER ENTERS A CHAR */
  do{
    printf("How many players (min 2, max 5): ");
    good_scan = scanf("%d",&num_players);
    if(num_players >= 2 && num_players <= 5 && good_scan > 0)
      break;
    printf("Invalid player count, please try again.\n");
  }while(1);
  
  // Initialize deck, players, table, and starting dealer
  Deck deck;
  Player player[num_players];
  Table table;
  resetGame(player,&deck,&table,num_players);
  addAIMoney(player,num_players);
  player[0].money = user_money;
  int dealer = rand()%num_players, turn_player;
  
  // Start Game
  clearScreen();
  dealer = nextPlayer(dealer,num_players,1);
  turn_player = nextPlayer(dealer,num_players,2);
  dealCards(player,&deck,num_players);
  startBlind(player,&table,num_players,dealer);
  printTableState(table,dealer);
  printHandState(player[0],table);
  bettingRound(player,&table,num_players,&turn_player);
  
  // Flop
  clearScreen();
  tableDeal(&table,&deck,3);
  printTableState(table,dealer);
  printHandState(player[0],table);
  bettingRound(player,&table,num_players,&turn_player);
  
  
  
  return 0;
}