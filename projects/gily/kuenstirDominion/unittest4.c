/* This file tests the function supplyCount
 *
 *
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 *
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int checkResult(int result, int expected) {
    printf("return value = %d, expected = %d\n", result, expected);

    if (result == expected) {
        printf("Test passed\n");
        return 0;
    } else {
        printf("TEST FAILED\n");
        return 1;
    }
}


int main() {
    printf("TESTING FUNCTION supplyCount()...........\n\n");

    int testFailed = 0;
    int expected;
    int result;

    int i;
    int seed = 500;
    int numPlayer = 2;
    int kingdom[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    
    struct gameState G;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, kingdom, seed, &G); // initialize a new game

    for (i = 0; i < 10; i++) {
        G.supplyCount[kingdom[i]] = 10 * i;
    }    

    for (i = 0; i < 10; i++) {
        printf("Testing kingdom card %d: ", i);
        expected = i * 10;
        result = supplyCount(kingdom[i], &G);
        testFailed += checkResult(result, expected);
    }

    if (testFailed == 0) {
        printf("All tests passed!\n\n");
    } else {
        printf("Some tests failed.\n\n");
    }

    return 0;
}
