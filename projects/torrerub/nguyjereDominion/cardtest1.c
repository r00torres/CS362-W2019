#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "rngs.h"
#include "assertTests.h"
#include <string.h>

int main(int argc, char** argv){
	

	//testing village card
	printf("____TESTING VILLAGE CARD___\n");
	int card = 14;

	//game structs
	struct gameState game, compGame;
	int choice1 = 0, choice2 = 0, choice3 = 0; //not used forthis card  
	int handPos = 0, bonus = 0;
	int newCards = 0, newActions = 0;
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

	//village +1 card, +2 action, discard
	newCards = 1;
	newActions = 2;
	discardedCards = 1;

	//check card was drawn
	isEqual(game.deckCount[testPlayer], (compGame.deckCount[testPlayer] - newCards + shuffledCards), "DECKCOUNT TEST");
	printf("\tEXPECTED DECKCOUNT %d. ACTUAL DECKCOUNT %d.\n", (compGame.deckCount[testPlayer] - newCards + shuffledCards), game.deckCount[testPlayer]);

	//check card was played
	isEqual(game.handCount[testPlayer], (compGame.handCount[testPlayer] + newCards - discardedCards), "HANDCOUNT TEST");
	printf("\tEXPECTED DECKCOUNT %d. ACTUAL DECKCOUNT %d.\n", (compGame.handCount[testPlayer] + newCards - shuffledCards), game.handCount[testPlayer]);

	//check actions increased
	isEqual(game.numActions, (compGame.numActions + newActions), "ACTION COUNT TEST");
	printf("\tEXPECTED ACTIONS %d. ACTUAL ACTIONS %d.\n", (compGame.numActions + newActions), game.numActions);

	printf("____VILLAGE TEST DONE____\n\n");

	return 0;
}

