/* This file tests the card adventurer
 *
 *
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 *
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int checkResult(int result, int expected) {
    printf("result = %d, expected = %d\n", result, expected);

    if (result == expected) {
        printf("Test passed\n");
        return 0;
    } else {
        printf("TEST FAILED\n");
        return 1;
    }
}


int main() {
    printf("TESTING CARD Adventurer...........\n\n");

    int card = adventurer;
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    int handPos = 0;
    int coin_bonus = 0;

    int testFailed = 0;

    int i, j;
    int seed = 500;
    int numPlayer = 2;
    int kingdom[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    
    struct gameState G, testG;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, kingdom, seed, &G); // initialize a new game

    G.whoseTurn = 0;

    for (i = 0; i < numPlayer; i++) {
        G.handCount[i] = 0;
        for (j = 0; j < 3; j++) {
            G.hand[i][j] = smithy;
            G.handCount[i]++;
        }
    }

    //Test when first 3 cards of deck are estate, next 7 cards are copper
    printf("Test Adventurer when deck has 3 estates, then 7 coppers\n");
    for (i = 0; i < numPlayer; i++) {
        G.deckCount[i] = 0;
        for (j = 0; j < 7; j++) {
            G.deck[i][j] = copper;
            G.deckCount[i]++;
        }
        for (j = 7; j < 10; j++) {
            G.deck[i][j] = estate;
            G.deckCount[i]++;
        }
    }
    i = 0;

    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(card, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

    printf("Checking number of cards in hand: ");
    testFailed += checkResult(testG.handCount[i], G.handCount[i] + 2 - 1); //Should draw 2 cards, discard adventurer
    printf("Checking number of cards in deck: ");
    testFailed += checkResult(testG.deckCount[i], G.deckCount[i] - 5); //Should take 5 cards out of deck
    printf("Checking number of cards in discard: ");
    testFailed += checkResult(testG.discardCount[i], G.discardCount[i] + 3); //Should discard 3 cards


    //Test when first 7 cards of deck are copper, next 3 cards are estate
    printf("Test Adventurer when deck has 7 coppers, then 3 estates\n");
    for (i = 0; i < numPlayer; i++) {
        G.deckCount[i] = 0;
        for (j = 0; j < 3; j++) {
            G.deck[i][j] = estate;
            G.deckCount[i]++;
        }
        for (j = 3; j < 10; j++) {
            G.deck[i][j] = copper;
            G.deckCount[i]++;
        }
    }
    i = 0;

    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(card, choice1, choice2, choice3, &testG, handPos, &coin_bonus);


    printf("Checking number of cards in hand: ");
    testFailed += checkResult(testG.handCount[i], G.handCount[i] + 2 - 1); //Should draw 2 cards, discard adventurer
    printf("Checking number of cards in deck: ");
    testFailed += checkResult(testG.deckCount[i], G.deckCount[i] - 2); //Should take 2 cards out of deck
    printf("Checking number of cards in discard: ");
    testFailed += checkResult(testG.discardCount[i], G.discardCount[i]); //Should discard 0 cards


    if (testFailed == 0) {
        printf("All tests passed!\n\n");
    } else {
        printf("Some tests failed.\n\n");
    }

    return 0;
}
