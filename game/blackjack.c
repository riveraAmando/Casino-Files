/*************************************
* File: blackjack.c
* Author Sergio Quiroga Velarde
* Purpose: Have a playable, accurate blackjack game
* Note: modified from week4peerProgram.c by Author and Sanaya Nichani (v0.0)
* Version History: v0.0 - 09/19/2024
*                  v1.0 - 10/23/2024 (removed second player, added dealer inheriting most player 2 code)
*                  v1.1 - 10/29/2024 (implemented card system created by Keven Duong and separated player and dealer cycles)
*                  v1.2 - 11/5/2024  (Fixed endless dealing bug, dealer printing player deack twice and garbage values being received as well as it not accepting input)
*                  v2.0 - 11/12/2024 Implemented Dealer AI improvements (Auto stand if player bust, as well as a difficulty ranking which modifies how much risk they are willing to taken exchange for changing prize) and a wait.
*                  v2.1 - Fixes folding at the wrong values, and not folding on player bust, succesfully implements Cheater Dealer.
*************************************/
#include <stdio.h>

//card system and files by Keven Duong
#include "cardart.h"
#include "cardops.h"
//also part of system but modified by me due to majorly different scoring system
#include "blackjackscore.h"

void clearScreens()
{
  printf("\e[1;1H\e[2J");
}

//resets the game, part of card system to be able to reuse variables and functions minimizing number of files, fold will be used for standing.
void resetBlackjackGame(Player * player,Deck * deck,Player * dealer)
{
  shuffle(deck);
  resetHand(player);
  resetHand(dealer);
}

//prints the players hand, part of card system, modified to new functions (dealer = is the dealer? 0 = no, 1 = yes);
void printHandStateBJ(Player * player, int dealer)
{
  if(dealer){
    printf("Dealers Hand:\n");
  } else {
    printf("Your Hand:\n");
  }
  printCards((*player).hand,(*player).num_cards);
  determineBlackjackScore(player);
  printf("Score: %d\n\n",(*player).score);
  if(!dealer){
    printf("Money: $%d\n",(*player).money);
    printf("Current Bet: $%d\n",(*player).bet);
  }
}

void blackJack() {
  srand(time(0));
  int user_money = 1000;
  int scanSafe;
  // defines player and dealer hand as well as the deck and ensures empty
  Player player;
  Player dealer;
  Deck deck;
  resetBlackjackGame(&player, &deck, &dealer);
  //sets up dealer AI and risk values
  int guts = -1;
  int riskFactor;
  int waryness;
  printf("Select dealer guts value:\nNormal:    x2 Money                 Enter 1\nDaredevil: x1.5(rounded down) Money Enter 2\nCoward:    x1.5(rounded down) Money Enter 3\nCheater:   x3 Money                 Enter 0\n");
  scanf("%d", &guts);
  while(guts < 0 || guts > 3){
    printf("Invalid value, please try again. ");
    scanf("%d", &guts);
  }
  printf("How much will you bet? ");
  scanf("%d", &player.bet);
  player.money = user_money;
  while(player.bet <= 0 || player.bet > user_money){
    printf("Invalid value, please try again. ");
    scanf("%d", &player.bet);
  }
  switch (guts) {
    case 0:
      riskFactor = 3;
      waryness = 21;
      break;
    case 1:
      riskFactor = 2;
      waryness = 16;
      break;
    case 2:
      riskFactor = -1;
      waryness = 20;
      break;
    case 3:
      riskFactor = -1;
      waryness = 10;
      break;
  }
  //deals starting hands, dealer first for a bit of a loaded dice for the player, maybe good maybe bad.
  clearScreens();
  playerDeal(&dealer, &deck, 2);
  playerDeal(&player, &deck, 2);
  printHandStateBJ(&player, 0);
  //Play cycle
  while(player.fold == 0){
    printf("Player turn, press 1 to stand or 0 to hit: ");
    player.fold = -1;
    while(player.fold != 0 && player.fold != 1){
		  scanf("%d", &player.fold);
		  if(player.fold != 1 && player.fold != 0){
		  	printf("Invalid input, please try again.");
		  }
  	}
	  if(player.fold == 0){
		  clearScreens();
      playerDeal(&player, &deck, 1);
      printHandStateBJ(&player, 0);
		  if(player.score > 21){
			  player.fold = 1;
        dealer.fold = 1;
     }
    }
  }
  //Dealer cycle
  printHandStateBJ(&dealer, 1);
  while(dealer.fold == 0){
    sleep(1);
    if(dealer.score > waryness || dealer.score > player.score){
      dealer.fold = 1;
      break;
    }
    clearScreens();
    playerDeal(&dealer, &deck, 1);
    determineBlackjackScore(&dealer);
    if(dealer.score > 21 && guts == 0){
      dealer.num_cards -= 1;
      printf("cheat");
      dealer.fold = 1;
    }
    printHandStateBJ(&player, 0);
    printHandStateBJ(&dealer, 1);
  }
  if((player.score <= 21 && player.score > dealer.score) || (dealer.score > 21 && player.score <= 21)){
    printf("You win!\n");
    if(riskFactor = -1){
      user_money += player.bet + player.bet/2;
    } else {
      user_money += player.bet * riskFactor;
    }
  } else if((dealer.score <= 21 && dealer.score > player.score) || (player.score > 21 && dealer.score <= 21)){
    printf("You lose!\n");
    user_money -= player.bet;
  } else{	
    printf("Its a draw!\n");
  }    
}
