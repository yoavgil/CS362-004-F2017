/* This file tests the card baron
 *
 *
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
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
    printf("TESTING CARD Baron...........\n\n");

    int card = baron;
    int choice1;
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

    //Test when choosing not to discard an estate, gain an estate
    choice1 = 0;
    G.numBuys = 1;
    G.supplyCount[estate] = 10;

    printf("Testing choice to not discard an estate (gain an estate)\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(card, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

    printf("Checking number of buys: ");
    testFailed += checkResult(testG.numBuys, G.numBuys + 1); //Should gain 1 buy
    printf("Checking number of cards in hand: ");
    testFailed += checkResult(testG.handCount[i], G.handCount[i] - 1); //Played card no longer in hand
    printf("Checking number of cards in discard pile: ");
    testFailed += checkResult(testG.discardCount[i], G.discardCount[i] + 1); //Gained estate is in discard pile (but played card not yet in discard)
    printf("Checking number of estates in the supply: ");
    testFailed += checkResult(testG.supplyCount[estate], G.supplyCount[estate] - 1); //Supply of estates should decrease by 1
    printf("Checking number of coins: ");
    testFailed += checkResult(testG.coins, G.coins); //No change in number of coins


    //Test when choosing not to discard an estate, no estates in supply to gain
    choice1 = 0;
    G.numBuys = 1;
    G.supplyCount[estate] = 0;

    printf("Testing choice to not discard an estate (no estates in supply to gain)\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(card, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

    printf("Checking number of buys: ");
    testFailed += checkResult(testG.numBuys, G.numBuys + 1); //Should gain 1 buy
    printf("Checking number of cards in hand: ");
    testFailed += checkResult(testG.handCount[i], G.handCount[i] - 1); //Played card no longer in hand
    printf("Checking number of cards in discard pile: ");
    testFailed += checkResult(testG.discardCount[i], G.discardCount[i]); //No change, because no card is gained
    printf("Checking number of estates in the supply: ");
    testFailed += checkResult(testG.supplyCount[estate], 0); //Supply of estates should still be 0
    printf("Checking number of coins: ");
    testFailed += checkResult(testG.coins, G.coins); //No change in number of coins


    //Test when choosing to discard an estate, with an estate in hand
    choice1 = 1;
    G.numBuys = 1;
    G.supplyCount[estate] = 10;

    G.handCount[0] = 0;
    for (j = 0; j < 3; j++) {
        G.hand[0][j] = smithy;
        G.handCount[0]++;
    }
    for (j = 3; j < 4; j++) {
        G.hand[0][j] = estate;
        G.handCount[0]++;
    }

    printf("Testing choice to discard an estate (gain coins)\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(card, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

    printf("Checking number of buys: ");
    testFailed += checkResult(testG.numBuys, G.numBuys + 1); //Should gain 1 buy
    printf("Checking number of cards in hand: ");
    testFailed += checkResult(testG.handCount[i], G.handCount[i] - 1); //Played card no longer in hand
    printf("Checking number of cards in discard pile: ");
    testFailed += checkResult(testG.discardCount[i], G.discardCount[i]); //No change, because no card is gained
    printf("Checking number of estates in the supply: ");
    testFailed += checkResult(testG.supplyCount[estate], G.supplyCount[estate]); //No change to supply of estates
    printf("Checking number of coins: ");
    testFailed += checkResult(testG.coins, G.coins + 4); //Gain 4 coins


    //Test when choosing to discard an estate, no estates in hand
    choice1 = 1;
    G.numBuys = 1;
    G.supplyCount[estate] = 10;

    G.handCount[0] = 0;
    for (j = 0; j < 4; j++) {
        G.hand[0][j] = smithy;
        G.handCount[0]++;
    }

    printf("Testing choice to discard an estate (no estate in hand, so gain an estate)\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(card, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

    printf("Checking number of buys: ");
    testFailed += checkResult(testG.numBuys, G.numBuys + 1); //Should gain 1 buy
    printf("Checking number of cards in hand: ");
    testFailed += checkResult(testG.handCount[i], G.handCount[i] - 1); //Played card no longer in hand
    printf("Checking number of cards in discard pile: ");
    testFailed += checkResult(testG.discardCount[i], G.discardCount[i] + 1); //Gained estate is in discard pile (but played card not yet in discard)
    printf("Checking number of estates in the supply: ");
    testFailed += checkResult(testG.supplyCount[estate], G.supplyCount[estate] - 1); //Supply of estates should decrease by 1
    printf("Checking number of coins: ");
    testFailed += checkResult(testG.coins, G.coins); //No change in number of coins


    //Test when choosing to discard an estate, no estates in hand or supply
    choice1 = 1;
    G.numBuys = 1;
    G.supplyCount[estate] = 0;

    G.handCount[0] = 0;
    for (j = 0; j < 4; j++) {
        G.hand[0][j] = smithy;
        G.handCount[0]++;
    }

    printf("Testing choice to discard an estate (no estate in hand or supply)\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    cardEffect(card, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

    printf("Checking number of buys: ");
    testFailed += checkResult(testG.numBuys, G.numBuys + 1); //Should gain 1 buy
    printf("Checking number of cards in hand: ");
    testFailed += checkResult(testG.handCount[i], G.handCount[i] - 1); //Played card no longer in hand
    printf("Checking number of cards in discard pile: ");
    testFailed += checkResult(testG.discardCount[i], G.discardCount[i]); //No change, because no card is gained
    printf("Checking number of estates in the supply: ");
    testFailed += checkResult(testG.supplyCount[estate], 0); //Supply of estates should still be 0
    printf("Checking number of coins: ");
    testFailed += checkResult(testG.coins, G.coins); //No change in number of coins



    if (testFailed == 0) {
        printf("All tests passed!\n\n");
    } else {
        printf("Some tests failed.\n\n");
    }

    return 0;
}
