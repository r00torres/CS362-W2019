#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "rngs.h"
#include "assertTests.h"
#include <string.h>
#include <time.h>

int main(int argc, char** argv){
	
	//set rand
	srand(time(NULL));

	//testing village card
	printf("____TESTING VILLAGE CARD___\n");
	int card = 14;

	//test results and controls
	int deckTests[2] = { 0, 0};
	int handTests[2] = { 0, 0};
	int playedCardTests[2] = { 0, 0};
	int passed =  0, failed = 0;
	int testLimit = 100;	//increase to increase number of tests run

	//cardeffect params
	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0; //not used for this card

	//game structs
	struct gameState game, compGame;
	
	//will randomize
	int seed;
	int numPlayers;
	int testPlayer;
	
	//not worth random
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int handPos = 0;

	//number of random tests = testLimit
	for(int i = 0; i < testLimit; i++){
		
		printf("____NEW TEST #%d___\n", i+1);

		//random number of players from 2-4 for init
		numPlayers = (rand() % 3) + 2;

		//random seed for init
		seed = (rand() % 5000);

		//init game
		initializeGame(numPlayers, k, seed, &game);

		//random test player from 0-numPlayers
		testPlayer =  (rand() % numPlayers);

		//place card at play position
		game.hand[testPlayer][handPos] = card;

		//set turn to testPlayer
		game.whoseTurn = testPlayer;
		
		//copy game to test
		memcpy(&compGame, &game, sizeof(struct gameState));
		
		//card effect	
		cardEffect(card, choice1, choice2, choice3, &game, handPos, &bonus);
		
		//village +1 card, +2 action, discard village
		int newCards = 1;
		int playedCards = 1;
		int newActions = 2;

		//testing deck count should be less playedCards
		isEqual(game.deckCount[testPlayer], (compGame.deckCount[testPlayer] - newCards), "DECKCOUNT TEST");
		printf("-EXPECTED DECK COUNT %d. ACTUAL DECK COUNT %d.\n" , (compGame.deckCount[testPlayer] - newCards), game.deckCount[testPlayer]);
		if (game.deckCount[testPlayer] == (compGame.deckCount[testPlayer] - newCards)){
			deckTests[0] += 1;
		}
		else{
			deckTests[1] += 1;
		}

		//testing hand count should be more by newCards and less by playedCards
		isEqual(game.handCount[testPlayer], (compGame.handCount[testPlayer] + newCards - playedCards), "HANDCOUNT TEST");
		printf("-EXPECTED HANDCOUNT %d. ACTUAL HANDCOUNT %d.\n" , (compGame.handCount[testPlayer] + newCards - playedCards), game.handCount[testPlayer]);
		if (game.handCount[testPlayer] == (compGame.handCount[testPlayer] + newCards - playedCards)){
			handTests[0] += 1;
		}
		else{
			handTests[1] += 1;
		}

		//playedCardCount should be more by playedCards
		isEqual(game.playedCardCount, (compGame.playedCardCount + playedCards), "PLAYED COUNT TEST");
		printf("-EXPECTED PLAYED COUNT %d. ACTUAL PLAYED COUNT %d.\n", (compGame.playedCardCount + playedCards), game.playedCardCount);
		if (game.playedCardCount == (compGame.playedCardCount + playedCards)){
			playedCardTests[0] += 1;
		}
		else{
			playedCardTests[1] += 1;
		}

		//numActions more by newActions
		isEqual(game.numActions, (compGame.numActions + newActions), "NUMACTIONS TEST");
		printf("-EXPECTED NUM ACTION %d. ACTUAL NUM ACTION %d.\n", (compGame.numActions + newActions), game.numActions);
		if (game.numActions == (compGame.numActions + newActions)){
			passed++;
		}
		else{
			failed++;
		}

		printf("____END TEST #%d___\n", i+1);
	}

	printf("____VILLAGE CARD TEST SUMMARY____\n");
	printf("\tVILLAGE DECK TESTS, %d PASSES, %d FAILS\n", deckTests[0], deckTests[1]);
	printf("\tVILLAGE HAND TESTS, %d PASSES, %d FAILS\n", handTests[0], handTests[1]);
	printf("\tVILLAGE PLAYED TESTS, %d PASSES, %d FAILS\n", playedCardTests[0], playedCardTests[1]);
	printf("\tVILLAGE ACTIONS TESTS, %d PASSES, %d FAILS\n", passed, failed);
	printf("\tVILLAGE ALL TESTS, %d PASSES, %d FAILS\n", deckTests[0]+handTests[0]+playedCardTests[0]+passed, deckTests[1]+handTests[1]+playedCardTests[1]+failed);
	printf("____END VILLAGE CARD TEST____\n\n");
	
	return 0;
}

