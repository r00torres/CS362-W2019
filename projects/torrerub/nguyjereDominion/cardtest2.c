#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "rngs.h"
#include "assertTests.h"
#include <string.h>

int main(int argc, char** argv){
	

	//testing outpost card
	printf("____TESTING OUTPOST CARD___\n");
	int card = 23;

	//game structs
	struct gameState game, compGame;
	int choice1 = 0, choice2 = 0, choice3 = 0; //not used forthis card  
	int handPos = 0, bonus = 0;
	int newCards = 0;
	int discardedCards = 0, shuffledCards = 0;
	int seed = 1000;
	int numPlayers = 2;
	int testPlayer = 0;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};

	//init game
	initializeGame(numPlayers, k, seed, &game);

	//copy game to test
	memcpy(&compGame, &game, sizeof(struct gameState));

	//take effect
	cardEffect(card, choice1, choice2, choice3, &game, handPos, &bonus);

	//outpost: outpost set so next player should be same player again, discard
	discardedCards = 1;

	//check no card was drawn
	isEqual(game.deckCount[testPlayer], (compGame.deckCount[testPlayer] - newCards + shuffledCards), "DECKCOUNT TEST");
	printf("\tEXPECTED DECKCOUNT %d. ACTUAL DECKCOUNT %d.\n", (compGame.deckCount[testPlayer] - newCards + shuffledCards), game.deckCount[testPlayer]);
	
	//check card was played
	isEqual(game.handCount[testPlayer], (compGame.handCount[testPlayer] + newCards - discardedCards), "HANDCOUNT TEST");
	printf("\tEXPECTED HANDCOUNT %d. ACTUAL HANDCOUNT %d.\n", (compGame.handCount[testPlayer] + newCards - discardedCards), game.handCount[testPlayer]);

	//check that the same player gets to go again
	isEqual(whoseTurn(&game), whoseTurn(&compGame), "OUTPOST ALLOWS PLAYER SECOND TURN TEST");
	printf("\tEXPECTED NEXT PLAYER %d. ACTUAL NEXT PLAYER %d.\n", whoseTurn(&compGame), whoseTurn(&game));

	printf("____OUTPOST TEST DONE____\n\n");

	return 0;
}

