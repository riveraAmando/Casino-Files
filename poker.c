#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_SUITS 4
#define NUM_RANKS 13
#define NUM_CARDS 52
#define HAND_SIZE 2
#define COMMUNITY_CARDS 5
#define INITIAL_BET 10  // Minimum initial bet amount

// Structure to represent a card
typedef struct {
    int rank;
    int suit;
} Card;

// Function prototypes
void shuffle_deck(Card deck[]);
void deal_cards(Card deck[], Card player_hand[], int num_cards);
void display_card(Card card);
void display_community_cards(Card community_cards[], int num_cards);
void reveal_cards(Card community_cards[], int reveal_count);
int place_bet(int current_money);

// Initialize and shuffle the deck
void shuffle_deck(Card deck[]) {
    int i,j;
    for ( i = 0; i < NUM_SUITS; i++) {
        for ( j = 0; j < NUM_RANKS; j++) {
            deck[i * NUM_RANKS + j].rank = j;
            deck[i * NUM_RANKS + j].suit = i;
        }
    }

}

// Deal cards to player
void deal_cards(Card deck[], Card player_hand[], int num_cards) {
    static int current_card = 0;  // Track current card in the deck
    int i;
    for ( i = 0; i < num_cards; i++) {
        player_hand[i] = deck[current_card++];
    }
}

// Display card
void display_card(Card card) {
    const char *ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    const char *suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    printf("%s of %s\n", ranks[card.rank], suits[card.suit]);
}

// Display community cards based on how many should be revealed
void reveal_cards(Card community_cards[], int reveal_count) {
    printf("Community Cards:\n");
    int i;
    for (i = 0; i < reveal_count; i++) {
        display_card(community_cards[i]);
    }
}

// Place a bet
int place_bet(int current_money) {
    int bet;
    do {
        printf("You have $%d. Enter your bet (minimum $%d): ", current_money, INITIAL_BET);
        scanf("%d", &bet);
        if (be < INITIAL_BET || bet > current_money) {
            printf("Invalid bet! Please bet between $%d and $%d.\n", INITIAL_BET, current_money);
        }
    } while (bet < INITIAL_BET || bet > current_money);
    return bet;
}

int main() {
    Card deck[NUM_CARDS];
    Card player1_hand[HAND_SIZE];
    Card community_cards[COMMUNITY_CARDS];
    int player_money;
    printf (" How much money would you like to start with? : ");
    scanf ("%d",&player_money);
   
    char play_again;

    do {
        shuffle_deck(deck);

        // Deal cards to player
        deal_cards(deck, player1_hand, HAND_SIZE);

        // RIVER (5 cards for the table)
        deal_cards(deck, community_cards, COMMUNITY_CARDS);

        // Display hand
        printf("Your Hand:\n");
        int i;
        for (i = 0; i < HAND_SIZE; i++) {
            display_card(player1_hand[i]);
        }

        // Initial bet
        int bet = place_bet(player_money);
        player_money -= bet;

        //Flop (first 3 cards)
        printf("\nRevealing the Flop:\n");
        reveal_cards(community_cards, 3);

        // Ask player if they want to place a bet after the flop
        bet = place_bet(player_money);
        player_money -= bet;

        // 4th card
        printf("\nRevealing the Turn:\n");
        reveal_cards(community_cards, 4);

        // Ask player if they want to place a bet after the turn
        bet = place_bet(player_money);
        player_money -= bet;

        // 5th card
        printf("\nRevealing the River:\n");
        reveal_cards(community_cards, 5);

        // Final bet after all cards are revealed
        bet = place_bet(player_money);
        player_money -= bet;

        printf("\nYou have $%d left after this round.\n", player_money);

        // Ask the player if they want to play again
        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &play_again);

        //If they play again, reset money if they've run out
        if (play_again == 'y' && player_money <= 0) {
            printf("You are out of money. Resetting your balance to $100.\n");
            player_money = 100;
        }

    } while (play_again == 'y' && player_money > 0);

    printf("Thank you for playing!\n");

    return 0;
}
