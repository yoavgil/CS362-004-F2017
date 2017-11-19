/* This file tests the card Smithy
 *
 *
 * Include the following lines in your makefile:
 *
 * randomtestcard1: randomtestcard1.c dominion.o rngs.o
 *      gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
 *
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_TESTS 500
#define SEED 500


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
    int seed = SEED;
    srand(seed);

    printf("TESTING CARD Smithy........... seed = %d\n\n", seed);

    int card = smithy;
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    int handPos;
    int coin_bonus = 0;

    int testFailed = 0;
    int numPlayers = MAX_PLAYERS;

    int i, j, k, l, m;
    int kingdom[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    
    struct gameState G, testG;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayers, kingdom, seed, &G); // initialize a new game

    for (k = 0; k < NUM_TESTS; k++) {
        printf("Test #%d\n", k + 1);
        i = rand() % MAX_PLAYERS;
        j = rand() % (MAX_HAND - 1);
        handPos = rand() % (j + 1);

        G.whoseTurn = i;
        G.handCount[i] = j + 1;
        G.hand[i][handPos] = card;
        l = rand() % (MAX_DECK - 1); //Deck count must be greater than 0
        G.deckCount[i] = l + 1;
        m = rand() % MAX_DECK;
        G.discardCount[i] = m;

        memcpy(&testG, &G, sizeof(struct gameState));
        cardEffect(card, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

        //check that hand has +2 cards, because smithy is removed from hand and 3 cards are drawn
        printf("Checking number of cards in hand: player = %d, hand = %d, card position = %d, deck = %d, discard = %d\n", i, testG.handCount[i], handPos, testG.deckCount[i], testG.discardCount[i]);
        testFailed += checkResult(testG.handCount[i], G.handCount[i] - 1 + 3);

        //check that deck+discard has -3 cards, because Smithy is "played" (but not yet discarded)
        printf("Checking number of cards in deck + discard: ");
        testFailed += checkResult(testG.deckCount[i] + testG.discardCount[i],
                G.deckCount[i] + G.discardCount[i] - 3);

    }

    if (testFailed == 0) {
        printf("All tests passed!\n\n");
    } else {
        printf("Some tests failed.\n\n");
    }

    return 0;
}
