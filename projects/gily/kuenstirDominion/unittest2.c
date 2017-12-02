/* This file tests the function scoreFor
 *
 *
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
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
    printf("TESTING FUNCTION scoreFor()...........\n\n");

    int testFailed = 0;
    int expected;
    int result;

    int i, j, k, l;
	int seed = 500;
	int kingdom[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	
	struct gameState G;

    int numPlayer = 2;

    int curseArray[MAX_HAND];
    int estateArray[MAX_HAND];
    int duchyArray[MAX_HAND];
    int provinceArray[MAX_HAND];
    int great_hallArray[MAX_HAND];
    int gardensArray[MAX_HAND];
    for (i = 0; i < MAX_DECK; i++) {
        curseArray[i] = curse;
        estateArray[i] = estate;
        duchyArray[i] = duchy;
        provinceArray[i] = province;
        great_hallArray[i] = great_hall;
        gardensArray[i] = gardens;
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

                    //Set all the cards to curse
                    printf("Testing Curse: ");
                    memcpy(G.hand[i], curseArray, sizeof(int) * j);
                    memcpy(G.discard[i], curseArray, sizeof(int) * k);
                    memcpy(G.deck[i], curseArray, sizeof(int) * l);

                    expected = -1 * (j + k + l);
                    result = scoreFor(i, &G);
                    testFailed += checkResult(i, j, k, l, result, expected);

                    //Set all the cards to estate
                    printf("Testing Estate: ");
                    memcpy(G.hand[i], estateArray, sizeof(int) * j);
                    memcpy(G.discard[i], estateArray, sizeof(int) * k);
                    memcpy(G.deck[i], estateArray, sizeof(int) * l);

                    expected = j + k + l;
                    result = scoreFor(i, &G);
                    testFailed += checkResult(i, j, k, l, result, expected);

                    //Set all the cards to duchy
                    printf("Testing Duchy: ");
                    memcpy(G.hand[i], duchyArray, sizeof(int) * j);
                    memcpy(G.discard[i], duchyArray, sizeof(int) * k);
                    memcpy(G.deck[i], duchyArray, sizeof(int) * l);

                    expected = 3 * (j + k + l);
                    result = scoreFor(i, &G);
                    testFailed += checkResult(i, j, k, l, result, expected);

                    //Set all the cards to province
                    printf("Testing Province: ");
                    memcpy(G.hand[i], provinceArray, sizeof(int) * j);
                    memcpy(G.discard[i], provinceArray, sizeof(int) * k);
                    memcpy(G.deck[i], provinceArray, sizeof(int) * l);

                    expected = 6 * (j + k + l);
                    result = scoreFor(i, &G);
                    testFailed += checkResult(i, j, k, l, result, expected);

                    //Set all the cards to great_hall
                    printf("Testing Great Hall: ");
                    memcpy(G.hand[i], great_hallArray, sizeof(int) * j);
                    memcpy(G.discard[i], great_hallArray, sizeof(int) * k);
                    memcpy(G.deck[i], great_hallArray, sizeof(int) * l);

                    expected = j + k + l;
                    result = scoreFor(i, &G);
                    testFailed += checkResult(i, j, k, l, result, expected);

                    
                }
            }
        }
    }

    //Set different values for Gardens to test when total number of cards > 10
    for (i = 0; i < numPlayer; i++) {
        for (j = 9; j < 30; j+=10) {
            for (k = 9; k < 30; k+=10) {
                for (l = 9; l < 30; l+=10) {
                    
                    memset(&G, 23, sizeof(struct gameState));   // clear the game state
                    initializeGame(numPlayer, kingdom, seed, &G); // initialize a new game
                    G.handCount[i] = j;
                    G.discardCount[i] = k;
                    G.deckCount[i] = l;

                     //Set all the cards to gardens
                    printf("Testing Gardens: ");
                    memcpy(G.hand[i], gardensArray, sizeof(int) * j);
                    memcpy(G.discard[i], gardensArray, sizeof(int) * k);
                    memcpy(G.deck[i], gardensArray, sizeof(int) * l);

                    expected = (j + k + l) / 10;
                    result = scoreFor(i, &G);
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
