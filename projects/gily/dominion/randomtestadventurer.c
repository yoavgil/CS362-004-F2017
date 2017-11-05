/* This file tests the card adventurer
 *
 *
 * Include the following lines in your makefile:
 *
 * randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *      gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
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

    printf("TESTING CARD Adventurer........... seed = %d\n\n", seed);

    int card = adventurer;
    int choice1 = 0;
    int choice2 = 0;
    int choice3 = 0;
    int handPos;
    int coin_bonus = 0;

    int testFailed = 0;

    int i, j, k, l, randomCard;
    int numPlayer = MAX_PLAYERS;
    int kingdom[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    
    struct gameState G, testG;

    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    initializeGame(numPlayer, kingdom, seed, &G); // initialize a new game

    for (k = 0; k < NUM_TESTS; k++) {
        printf("Test #%d\n", k + 1);
        i = rand() % numPlayer;
        G.whoseTurn = i;

        l = rand() % (MAX_HAND - 1);
        G.handCount[i] = 0;
        for (j = 0; j < l + 1; j++) {
            randomCard = rand() % (treasure_map + 1);
            G.hand[i][j] = randomCard;
            G.handCount[i]++;
        }

        l = rand() % MAX_DECK;
        G.deckCount[i] = 0;
        for (j = 0; j < l; j++) {
            randomCard = rand() % (treasure_map + 1);
            G.deck[i][j] = randomCard;
            G.deckCount[i]++;
        }

        //Ensure that one card in the hand is an adventurer
        handPos = rand() % G.handCount[i];
        G.hand[i][handPos] = card;


        memcpy(&testG, &G, sizeof(struct gameState));
        cardEffect(card, choice1, choice2, choice3, &testG, handPos, &coin_bonus);

        /*int treasuresDrawn = 0;
        int cardsDrawn = 0;
        while (treasuresDrawn < 2) {
            if (G.deck[i][deckCount[i]] == copper || G.deck[i][deckCount[i]] == silver || G.deck[i][deckCount[i]] == gold) {
                treasuresDrawn++;
            }
            cardsDrawn = 0;
        }*/

        printf("Checking number of cards in hand: ");
        testFailed += checkResult(testG.handCount[i], G.handCount[i] + 2 - 1); //Should draw 2 treasure cards, discard adventurer
        printf("Ckecking number of cards in deck + discard: ");
        testFailed += checkResult(testG.deckCount[i] + testG.discardCount[i],
                G.deckCount[i] + G.discardCount[i] - 2); //Deck + discard should have 2 fewer cards
    }

    return 0;
}
