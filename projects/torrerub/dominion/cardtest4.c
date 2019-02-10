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
	printf("____TESTING ADVENTURER CARD___\n");
	int card = 7;

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

	//set deck to have all treasure at top of deck
	game.deck[testPlayer][0] = 4;
	game.deck[testPlayer][1] = 5;
	game.deck[testPlayer][2] = 6;
	game.deck[testPlayer][3] = 4;
	
	
	//copy game to test
	memcpy(&compGame, &game, sizeof(struct gameState));

	
	//card effect	
	cardEffect(card, choice1, choice2, choice3, &game, handPos, &bonus);

	//adventurer +2 card in hand		
	newCards = 2;
	discardedCards = 1;
	
	//testing with no shuffle needed
	printf("TESTING EFFECT WITH NO SHUFFLE OF DECK AND DISCARD NEEDED\n");

	isEqual(game.deckCount[testPlayer], (compGame.deckCount[testPlayer] - newCards + shuffledCards), "DECKCOUNT TEST");
	printf("\tEXPECTED DECK COUNT %d. ACTUAL DECK COUNT %d.\n" , (compGame.deckCount[testPlayer] - newCards + shuffledCards), game.deckCount[testPlayer]);

	//check card was drawn
	isEqual(game.discardCount[testPlayer], (compGame.discardCount[testPlayer] + discardedCards), "DISCARD COUNT TEST");
	printf("\tEXPECTED DISCARD COUNT %d. ACTUAL DISCARD COUNT %d.\n", (compGame.discardCount[testPlayer] + discardedCards), game.discardCount[testPlayer]);

	//check card was played
	isEqual(game.handCount[testPlayer], (compGame.handCount[testPlayer] + newCards), "HANDCOUNT TEST");
	printf("\tEXPECTED HANDCOUNT %d. ACTUAL HANDCOUNT %d.\n", (compGame.handCount[testPlayer] + newCards), game.handCount[testPlayer]);

	//should test effects when a shuffle needed
	
	printf("____END ADVENTURER CARD TEST____\n\n");
	
	return 0;
}

