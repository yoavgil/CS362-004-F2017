/* This file tests the function fullDeckCount
 *
 *
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 *
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int checkResult(int player, int hand, int discard, int deck, int result, int expected) {
    printf("player %d, hand %d, discard %d, deck %d, return value = %d, expected = %d\n", player, hand, discard, deck, result, expected);

    if (result == expected) {
        printf("Test passed\n");
        return 0;
    } else {
        printf("TEST FAILED\n");
        return 1;
    }
}


int main() {
    printf("TESTING FUNCTION fullDeckCount()...........\n\n");

    int testFailed = 0;
    int expected;
    int result;

    int i, j, k, l;
    int seed = 500;
    int kingdom[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    
    struct gameState G;

    int numPlayer = 2;

    int adventurerArray[MAX_HAND];
    int feastArray[MAX_HAND];

    for (i = 0; i < MAX_DECK; i++) {
        adventurerArray[i] = adventurer;
        feastArray[i] = feast;
    }

    for (i = 0; i < numPlayer; i++) {
        for (j = 1; j < 3; j++) {
            for (k = 1; k < 3; k++) {
                for (l = 1; l < 3; l++) {
                    
                    memset(&G, 23, sizeof(struct gameState));   // clear the game state
                    initializeGame(numPlayer, kingdom, seed, &G); // initialize a new game
                    G.handCount[i] = j;
                    G.discardCount[i] = k;
                    G.deckCount[i] = l;

                    //Set all the cards to adventurer
                    printf("Testing Adventurer: ");
                    memcpy(G.hand[i], adventurerArray, sizeof(int) * j);
                    memcpy(G.discard[i], adventurerArray, sizeof(int) * k);
                    memcpy(G.deck[i], adventurerArray, sizeof(int) * l);

                    expected = j + k + l;
                    result = fullDeckCount(i, adventurer, &G);
                    testFailed += checkResult(i, j, k, l, result, expected);

                    //Set all the cards to feast
                    printf("Testing Feast: ");
                    memcpy(G.hand[i], feastArray, sizeof(int) * j);
                    memcpy(G.discard[i], feastArray, sizeof(int) * k);
                    memcpy(G.deck[i], feastArray, sizeof(int) * l);

                    expected = j + k + l;
                    result = fullDeckCount(i, feast, &G);
                    testFailed += checkResult(i, j, k, l, result, expected);

                    //Leabe all cards as feast, except first card adventurer
                    printf("Testing first card Adventurer, all others Feast: ");
                    G.hand[i][0] = adventurer;
                    G.discard[i][0] = adventurer;
                    G.deck[i][0] = adventurer;

                    expected = j + k + l;
                    result = fullDeckCount(i, feast, &G);
                    testFailed += checkResult(i, j, k, l, result, expected);
                }
            }
        }
    }

    if (testFailed == 0) {
        printf("All tests passed!\n\n");
    } else {
        printf("Some tests failed.\n\n");
    }

    return 0;
}
