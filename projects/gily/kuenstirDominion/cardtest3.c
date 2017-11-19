/* This file tests the card village
 *
 *
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
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
    printf("TESTING CARD Village...........\n\n");

    int card = village;
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    int handPos = 0;
    int coin_bonus = 0;

    int testFailed = 0;

    int i = 0;
    int j;
    int seed = 500;
    int numPlayer = 2;
    int kingdom[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    
    struct gameState G, testG;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, kingdom, seed, &G); // initialize a new game

    G.whoseTurn = 0;

    G.handCount[0] = 0;
    for (j = 0; j < 3; j++) {
        G.hand[0][j] = smithy;
        G.handCount[0]++;
    }

    //Test when deck has 50 cards
    printf("Testing when deck has 50 cards, discard has 0\n");
    G.deckCount[i] = 50;
    G.discardCount[i] = 0;
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(card, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

    printf("Checking number of cards in hand: ");
    testFailed += checkResult(testG.handCount[i], G.handCount[i]); //Should draw 1 card, discard 1 card
    printf("Checking number of cards in deck + discard: ");
    testFailed += checkResult(testG.deckCount[i] + testG.discardCount[i],
            G.deckCount[i] + G.discardCount[i] - 1); //Should be 5 fewer cards in deck + discard
    printf("Checking number of actions: ");
    testFailed += checkResult(testG.numActions, G.numActions + 2); //Should have 2 more actions

    //Test when deck has 1 card
    printf("Testing when deck has 1 card, discard has 20\n");
    G.deckCount[i] = 1;
    G.discardCount[i] = 20;
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(card, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

    printf("Checking number of cards in hand: ");
    testFailed += checkResult(testG.handCount[i], G.handCount[i]); //Should draw 1 card, discard 1 card
    printf("Checking number of cards in deck + discard: ");
    testFailed += checkResult(testG.deckCount[i] + testG.discardCount[i],
            G.deckCount[i] + G.discardCount[i] - 1); //Should be 5 fewer cards in deck + discard
    printf("Checking number of actions: ");
    testFailed += checkResult(testG.numActions, G.numActions + 2); //Should have 2 more actions


    if (testFailed == 0) {
        printf("All tests passed!\n\n");
    } else {
        printf("Some tests failed.\n\n");
    }

    return 0;
}
