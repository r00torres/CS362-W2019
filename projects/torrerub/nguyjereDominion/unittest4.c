#include "dominion.h"
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "rngs.h"

int main(int argc, char** argv){

	struct gameState game;
	int testPlayer = 0;
	int testCard = 0;
	int testLim = 5;
	int i;

	//init state before testing
	game.deckCount[testPlayer] = testLim;
	game.handCount[testPlayer] = testLim;
	game.discardCount[testPlayer] = testLim;

	//init deck, hand, and discard with all card 1
	for(i = 0; i < testLim; i++){
		game.deck[testPlayer][i] = 1;	
	}

	for(i = 0; i < testLim; i++){
                game.hand[testPlayer][i] = 1;
        }

	for(i = 0; i < testLim; i++){
                game.discard[testPlayer][i] = 1;
        }

	//testing isGameOver() which accepts game state
	printf("____TESTING fullDeckCount():\n");

	//test when province cards are zero
	printf("____UNIT TEST 1 OF 4: COUNT FOR CARD 0 IN DECK/HAND/DISCARD IS 0:\n");
	
	assert(fullDeckCount(testPlayer, testCard, &game) == 0);

	printf("____UNIT TEST 1 of 4: PASSED\n");

	//test when province cards is not zero but 3 or more supply is empty
	printf("____UNIT TEST 2 of 4: COUNT FOR CARD 0 IN DECK/HAND/DISCARD IS 1:\n");

	//set all supply to at least 1
	game.deck[testPlayer][1] = 0;

	assert(fullDeckCount(testPlayer, testCard, &game) == 1);

	printf("____UNIT TEST 2 OF 4: PASSED\n");

	//test when province cards is not zero but less than 3 supply is empty
	printf("____UNIT TEST 3 OF 4: COUNT FOR CARD 0 IN DECK/HAND/DISCARD IS 2:\n");

	game.hand[testPlayer][2] = 0;

	assert(fullDeckCount(testPlayer, testCard, &game) == 2);

	printf("____UNIT TEST 3 OF 4: PASSED\n");
	
	printf("____UNIT TEST 4 OF 4: COUNT FOR CARD 0 IN DECK/HAND/DISCARD:\n");

        game.discard[testPlayer][3] = 0;

        assert(fullDeckCount(testPlayer, testCard, &game) == 3);

        printf("____UNIT TEST 4 OF 4: PASSED\n");

	return 0;
}

