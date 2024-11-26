/***********************************************************
*
* Author:    Keven Duong
*
* File:      texas_holdemv6.c
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
#include "pokerAI.h"

// Resets game state
void resetGame(Player player[], Deck *deck, Table *table, int num_players) {
	shuffle(deck);
	resetTable(table);
	int p;
	for (p = 0; p < num_players; p++) {
		resetHand(&player[p]);
	}
}

// Gives starting money to AI
void addAIMoney(Player player[], int num_players) {
	int ai;
	for (ai = 1; ai < num_players; ai++) {
		player[ai].money = 1000;
	}
}

// Deals cards to all players
void dealCards(Player player[], Deck *deck, int num_players) {
	int p;
	for (p = 0; p < num_players; p++) {
		playerDeal(&player[p], deck, 2); // Deal 2 cards to each player
	}
}

// Finds the next player in the turn order
int nextPlayer(int current_player, int num_players, int turns) {
	int next_player = current_player, turn;
	for ( turn = 0; turn < turns; turn++) {
		next_player = (next_player + 1) % num_players;
	}
	return next_player;
}

// Resolves blinds
void startBlind(Player player[], Table *table, int num_players, int dealer) {
	int blind = 100;
	table->high_bet = blind;
	player[nextPlayer(dealer, num_players, 1)].bet = blind;
	player[nextPlayer(dealer, num_players, 2)].bet = blind / 2;
	table->pot += blind + (blind / 2);
}

// Shows table state to user
void printTableState(Table table, int dealer) {
	printf("Current Pot: $%d\nHighest Bet: $%d\n", table.pot, table.high_bet);
	if (table.num_cards > 0) {
		printCards(table.card_pool, table.num_cards);  // Show community cards
	} else {
		printf("No community cards on the table yet.\n");
	}
}

// Shows a player's hand state to user
void printHandState(Player player, Table table) {
	printf("Your Hand:\n");
	printCards(player.hand, player.num_cards);
	determineScore(&player, table, 1, 1); // Display player's hand score
	printf("Money: $%d\n", player.money);
	printf("Current Bet: $%d\n", player.bet);
 
}

// Function to clear the input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Betting function. 
void getBetFromPlayer(Player *player, Table *table) {
    int amount;
    
    while (1) {
        printf("How much do you want to bet? (-1 to fold): ");

        // Check if scanf returns a valid integer
        int goodscan = scanf("%d", &amount);

        if (goodscan == 0) { 
            printf("Invalid input. Please enter a valid integer.\n");
            clearInputBuffer();
            continue;
        }

        if (amount == -1) {
            player->fold = 1;
            player->money -= player->bet;
            player->bet = 0;
            break;
        } 
        else if (amount > player->money) {
            printf("You don't have enough money to bet that amount. Please try again.\n");
        } 
        else if (amount < table->high_bet) {
            printf("Your bet must match or exceed the current high bet of $%d. Please try again.\n", table->high_bet);
        } 
        else {
            player->bet = amount;
            if (amount > table->high_bet) {
                table->high_bet = amount;
            }
            
            break;
        }
    }
}

// Prompts user for a bet.
void bettingRound(Player player[], Table *table, int num_players, int *turn_player) {
	printf("--------------------------\n");
	int active_players = num_players;
	int passes = 0;
  int folds=0,i;
  
  for(i=0;i<num_players;i++)
  {
    if(player[i].fold == 1)
      folds++;
  }
  
  if(folds == 2)
    return;

	while (passes < active_players) 
  {
    if(player[*turn_player].money <= 0)
      player[*turn_player].fold = 1;
    
    // Fold Players
		if (player[*turn_player].fold == 1) 
    {
      player[*turn_player].money -= player[*turn_player].bet;
      player[*turn_player].bet = 0;
			*turn_player = nextPlayer(*turn_player, num_players, 1);
      passes++;
			continue;
		}
    // All-In Players
    if (player[*turn_player].bet == player[*turn_player].money)
    {
      *turn_player = nextPlayer(*turn_player, num_players, 1);
      passes++;
			continue;
    }
		// User's turn
		if (*turn_player == 0) 
    {
			getBetFromPlayer(&player[0], table);
			if (player[0].bet == table->high_bet) {
				passes++;
			}
      else if(player[0].bet > table->high_bet)
        passes = 0;
			*turn_player = nextPlayer(*turn_player, num_players, 1);
		} 
    else if(*turn_player == 1)
    {
			// AI's turn
      while(player[1].bet < table->high_bet && player[1].fold != 1)
			  ai_randy_bet(&player[1],table);
      if(player[1].fold == 1)
      {
        passes++;
        //active_players--;
      }
      else if(player[1].bet == table->high_bet)
        passes++;
      else if(player[1].bet > table->high_bet)
      {
        table->high_bet = player[1].bet;
        passes = 0;
      }
			*turn_player = nextPlayer(*turn_player, num_players, 1);
      sleep(1);
		}
    else if(*turn_player == 2)
    {
      while(player[2].bet < table->high_bet && player[2].fold != 1)
			  ai_steve_bet(&player[2],table);
      if(player[2].fold == 1)
      {
        passes++;
        //active_players--;
      }
      else if(player[2].bet == table->high_bet)
        passes++;
      else if(player[2].bet > table->high_bet)
      {
        passes = 0;
        table->high_bet = player[2].bet;
      }
			*turn_player = nextPlayer(*turn_player, num_players, 1);
      sleep(1);
    }
	}

	for (i = 0; i < num_players; i++) {
    if(player[i].bet > 0 && player[i].fold != 1)
    {
		  table->pot += player[i].bet;
      player[i].money -= player[i].bet;
    }
    if(player[i].fold != 1)
		  player[i].bet = 0;  
  
	}
	table->high_bet = 0; 
}

 // Very Basic Win Checker
void determineWinner(Player player[],Table * table,int num_players)
{
  int p,best_hand=0,best_player;
  for(p=0;p<num_players;p++)
  {
    if(player[p].fold == 1)
      continue;
    printf("%s:\n",player[p].name);
    printCards(player[p].hand, player[p].num_cards);
    determineScore(&player[p],*table,1,1);
    if(player[p].score > best_hand && player[p].fold != 1)
    {
      best_hand = player[p].score;
      best_player = p;
    }
  }
  
  printf("%s WINS!\n",player[best_player].name);
  player[best_player].money += table->pot;
}


int poker(int user_money,char username[20]) {
	srand(time(0));
  char inp[5];
 	int num_players=3;
  int dealer, turn_player;
  
  Deck deck;
 	Player player[num_players];
 	Table table;
  resetGame(player, &deck, &table, num_players);
  addAIMoney(player, num_players);
  player[0].money = user_money;
  
  strcpy(player[0].name,username);
  strcpy(player[1].name,"RANDY");
  strcpy(player[2].name,"STEVE");

  while(1){
  
  	// Initialize deck, players, table, and starting dealer
  	resetGame(player, &deck, &table, num_players);
    addAIMoney(player, num_players);
  	dealer = rand() % num_players;
  
  	// Start Game
  	clearScreen();
  	dealer = nextPlayer(dealer, num_players, 1);
  	turn_player = nextPlayer(dealer, num_players, 2);
  	dealCards(player, &deck, num_players);
  	startBlind(player, &table, num_players, dealer);
  	printTableState(table, dealer);
  	printHandState(player[0], table);
  	bettingRound(player, &table, num_players, &turn_player);
  
  	// Flop first 3 cards
  	clearScreen();
  	tableDeal(&table, &deck, 3);
  	printTableState(table, dealer);
  	printHandState(player[0], table);
  	bettingRound(player, &table, num_players, &turn_player);
  
  	//4th card 
  	clearScreen();
  	tableDeal(&table, &deck, 1);
  	printTableState(table, dealer);
  	printHandState(player[0], table);
  	bettingRound(player, &table, num_players, &turn_player);
  
  	//  5th card
  	clearScreen();
  	tableDeal(&table, &deck, 1);
  	printTableState(table, dealer);
  	printHandState(player[0], table);
  	bettingRound(player, &table, num_players, &turn_player);
  
    determineWinner(player,&table,num_players);
    while(1){
    printf ("Would you like to play again?(Yes or No)\n");
    scanf("%s",&inp);
    int i;
    for(i=0;i<=sizeof(inp);i++)
    {
      inp[i] = tolower(inp[i]);
    }
    if(strcmp(inp,"yes") == 0){
      break;
      }
    else if(strcmp(inp,"no") == 0){
      return player[0].money;
      }
    else{
      printf ("INVALID Input. Try again\n");
      continue;
    }
  }
  }
  	return player[0].money;
}
