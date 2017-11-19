/* This file tests the card baron
 *
 *
 * Include the following lines in your makefile:
 *
 * randomtestcard2: randomtestcard2.c dominion.o rngs.o
 *      gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
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

    printf("TESTING CARD Baron........... seed = %d\n\n", seed);

    int card = baron;
    int choice1;
    int choice2 = 0;
    int choice3 = 0;
    int handPos = 0;
    int coin_bonus = 0;

    int testFailed = 0;
    int numPlayer = MAX_PLAYERS;

    int i = 0;
    int j, k, l;
    int kingdom[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

    int randomCard, changeBuys, changeHand, changeDiscard, changeSupply, changeCoins, estateInHand;
    
    struct gameState G, testG;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, kingdom, seed, &G); // initialize a new game

    for (k = 0; k < NUM_TESTS; k++) {
        printf("Test #%d\n", k + 1);

        i = rand() % MAX_PLAYERS;
        G.whoseTurn = i;
        choice1 = rand() % 2;

        //Randomize hand, ensuring at least 1 card is baron
        l = rand() % (MAX_HAND - 1); //prevents handCount of 0
        G.handCount[i] = 0;
        for (j = 0; j < l + 1; j++) { //prevents handCount of 0
            randomCard = rand() % (treasure_map + 1);
            G.hand[i][j] = randomCard;
            G.handCount[i]++;
        }
        handPos = rand() % G.handCount[i]; //will crash if handCount == 0
        G.hand[i][handPos] = card;

        G.numBuys = rand() % 5 + 1; //Randomize number of buys (1 to 5)
        G.supplyCount[estate] = rand() % 13; //Randomize number of estates (0 to 12 estates)

        memcpy(&testG, &G, sizeof(struct gameState));
        cardEffect(card, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

        estateInHand = 0; //false
        for (j = 0; j < G.handCount[i]; j++) {
            if (G.hand[i][j] == estate) {
                estateInHand = 1; //true
            }
        }

        //Choose not to discard an estate, estates are availables
        if (choice1 == 0 && G.supplyCount[i] > 0) {
            changeBuys = 1;
            changeHand = -1; //played card removed from hand
            changeDiscard = 2; //played card and gained estate both added to discard
            changeSupply = -1; //gained estate removed from supply
            changeCoins = 0;
        }

        //Choose not to discard an estate, no estates are available
        else if (choice1 == 0 && G.supplyCount[i] == 0) {
            changeBuys = 1;
            changeHand = -1; //played card removed from hand
            changeDiscard = 1; //played card added to discard
            changeSupply = 0;
            changeCoins = 0;
        }

        //Choose to discard an estate, have estate in hand
        else if (choice1 == 1 && estateInHand == 1) {
            changeBuys = 1;
            changeHand = -2; //played card and discarded estate removed from hand
            changeDiscard = 2; //played card and discarded estate added to discard
            changeSupply = 0;
            changeCoins = 4;
        }

        //Choose to discard an estate, no estates in hand, estates are available in supply
        if (choice1 == 1 && estateInHand == 0 && G.supplyCount[i] > 0) {
            changeBuys = 1;
            changeHand = -1; //played card removed from hand
            changeDiscard = 2; //played card and gained estate both added to discard
            changeSupply = -1; //gained estate removed from supply
            changeCoins = 0;
        }

        //Choose to discard an estate, no estates in hand or supply
        else if (choice1 == 1 && estateInHand == 0 && G.supplyCount[i] == 0) {
            changeBuys = 1;
            changeHand = -1; //played card removed from hand
            changeDiscard = 1; //played card added to discard
            changeSupply = 0;
            changeCoins = 0;
        }

        printf("Checking number of buys: ");
        testFailed += checkResult(testG.numBuys, G.numBuys + changeBuys);
        printf("Checking number of cards in hand: ");
        testFailed += checkResult(testG.handCount[i], G.handCount[i] + changeHand);
        printf("Checking number of cards in discard pile: ");
        testFailed += checkResult(testG.discardCount[i], G.discardCount[i] + changeDiscard);
        printf("Checking number of estates in the supply: ");
        testFailed += checkResult(testG.supplyCount[estate], G.supplyCount[estate] + changeSupply);
        printf("Checking number of coins: ");
        testFailed += checkResult(testG.coins, G.coins + changeCoins);
    }

    if (testFailed == 0) {
        printf("All tests passed!\n\n");
    } else {
        printf("Some tests failed.\n\n");
    }

    return 0;
}
