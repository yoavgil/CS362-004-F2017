/* This file tests the card Smithy
 *
 *
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
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
    printf("TESTING CARD Smithy...........\n\n");

    int card = smithy;
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    int handPos;
    int coin_bonus = 0;

    int testFailed = 0;

    int startDeck = 30;
    int startDiscard = 10;

    int i, j;
    int seed = 500;
    int numPlayer = 2;
    int kingdom[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    
    struct gameState G, testG;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, kingdom, seed, &G); // initialize a new game

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 5; j++) {
            handPos = j;
            G.whoseTurn = i;
            G.handCount[i] = j;
            G.hand[i][handPos] = card;
            G.deckCount[i] = startDeck - (2 * j);
            G.discardCount[i] = startDiscard - j;

            memcpy(&testG, &G, sizeof(struct gameState));
            cardEffect(card, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

            //check that hand has +2 cards, because smithy is removed from hand and 3 cards are drawn
            printf("Checking number of cards in hand: ");
            testFailed += checkResult(testG.handCount[i], j - 1 + 3);

            //check that deck+discard has -3 cards, because Smithy is "played" (but not yet discarded)
            printf("Checking number of cards in deck + discard: ");
            testFailed += checkResult(testG.deckCount[i] + testG.discardCount[i],
                    G.deckCount[i] + G.discardCount[i] - 3);
        }
    }    

    if (testFailed == 0) {
        printf("All tests passed!\n\n");
    } else {
        printf("Some tests failed.\n\n");
    }

    return 0;
}
