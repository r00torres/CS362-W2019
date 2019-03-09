#include "dominion.h"
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "rngs.h"

int main(int argc, char** argv){

	struct gameState game;

	//testing whoseTurn() which accepts game state
	printf("____TESTING numHandCards():\n");

	//test when province cards are zero
	printf("____UNIT TEST 1 OF 2: PLAYER IS 0, HANDCOUNT 0:\n");

	game.whoseTurn = 0;
	game.handCount[game.whoseTurn] = 0;
	
	assert(numHandCards(&game) == 0);

	printf("____UNIT TEST 1 of 2: PASSED\n");

	//test when province cards is not zero but 3 or more supply is empty
	printf("____UNIT TEST 2 of 2: PLAYER IS 1, HANDCOUNT IS 5:\n");
	
	//set province count to 1
	game.whoseTurn = 1;
	game.handCount[game.whoseTurn] = 5;

	//set next card to 
	assert(numHandCards(&game) == 5);

	printf("____UNIT TEST 2 OF 2: PASSED\n");

	return 0;
}

