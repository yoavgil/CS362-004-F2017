/* This file tests the function isGameOver
 *
 *
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
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
    printf("TESTING FUNCTION isGameOver()...........\n\n");

	int testFailed = 0;  //change to nonzero value if any tests fail

	int result;
	int seed = 500;
	int numPlayer = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	
	struct gameState G;

	memset(&G, 23, sizeof(struct gameState));   // clear the game state
  	initializeGame(numPlayer, k, seed, &G); // initialize a new game


    //Test when provinces is 1 (not empty)
    printf("Testing when there is 1 province left: ");
    G.supplyCount[province] = 1;
    result = isGameOver(&G);
    testFailed += checkResult(result, 0);

    //Test when provinces is empty
    printf("Testing when provinces is empty: ");
    G.supplyCount[province] = 0;
    result = isGameOver(&G);
    testFailed += checkResult(result, 1);

    //Test when 1 supply pile is empty
    printf("Testing when 1 supply pile is empty: ");
    G.supplyCount[province] = 1;
    G.supplyCount[17] = 0;
    result = isGameOver(&G);
    testFailed += checkResult(result, 0);

    //Test when 2 supply piles are empty
    printf("Testing when 2 supply piles are empty: ");
    G.supplyCount[0] = 0;
    result = isGameOver(&G);
    testFailed += checkResult(result, 0);

    //Test when 3 supply piles are empty
    printf("Testing when 3 supply piles are empty: ");
    G.supplyCount[5] = 0;
    result = isGameOver(&G);
    testFailed += checkResult(result, 1);

    if (testFailed == 0) {
    	printf("All tests passed!\n\n");
    } else {
    	printf("Some tests failed\n\n");
    }

	return 0;
}
