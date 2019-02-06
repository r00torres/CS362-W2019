#include "dominion.h"
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "rngs.h"

int main(int argc, char** argv){

	struct gameState game;
	int i;
	//SelectStream(2);
	//PutSeed(3);

	//testing isGameOver() which accepts game state
	printf("____TESTING isGameOver():\n");

	//test when province cards are zero
	printf("____UNIT TEST 1 OF 3: PROVINCE CARDS IS 0:\n");

	game.supplyCount[province] = 0;
	
	assert(isGameOver(&game) == 1);

	printf("____UNIT TEST 1 of 3: PASSED\n");

	//test when province cards is not zero but 3 or more supply is empty
	printf("____UNIT TEST 2 of 3: PROVINCE CARDS IS 2, 3 OR MORE SUPPLY IS 0:\n");

	//set all supply to at least 1
	for(i = 0; i < 25; i++){
		game.supplyCount[i] = 2;
	}
	
	//set 3 supply to 0
	for(i = 0; i < 3; i++){
		game.supplyCount[i] = 0;
	}

	
	//set province count to 1
	if(game.supplyCount[province] == 0){
		game.supplyCount[province] = 1;

		//set next card to 0
		game.supplyCount[3] = 0;
	}
	
	else{
		game.supplyCount[province] = 1;
	}

	assert(isGameOver(&game) == 1);

	printf("____UNIT TEST 2 OF 3: PASSED\n");

	//test when province cards is not zero but less than 3 supply is empty
	printf("____UNIT TEST 3 OF 3: PROVINCE CARDS IS 2, LESS THAN 3 SUPPLY IS 0:\n");

	for(i = 0; i < 25; i++){
		game.supplyCount[i] = 2;
	}

	for(i = 0; i < 2; i++){
		game.supplyCount[i] = 0;
	}

	assert(isGameOver(&game) == 0);

	printf("____UNIT TEST 3 OF 3: PASSED\n");
	
	return 0;
}

