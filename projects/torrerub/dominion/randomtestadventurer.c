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
	printf("____TESTING ADVENTURER CARD___\n");
	int card = 7;

	//test results and controls
	int deckTests[2] = { 0, 0};
	int handTests[2] = { 0, 0};
	int discardTests[2] = { 0, 0};
	int playedCardTests[2] = {0, 0};
	int passed =  0, failed = 0;
	int testLimit = 100;	//increase to increase number of tests run

	//game structs
	struct gameState game, compGame;

	//cardeffect params
	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0; //not used for this card

	//will randomize for each test
	int seed;
	int numPlayers;
	int testPlayer;
	
	//not worth random
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	int handPos = 0;

	//number of random tests = testLimit
	for(int i = 0; i < testLimit; i++){
		
		printf("____NEW TEST #%d___\n", i+1);

	 	//random number of players from 2-4
		numPlayers = (rand() % 3) + 2;

		//random seed
		seed = (rand() % 5000);

		//random test player from 0-numPlayers
		testPlayer =  (rand() % numPlayers);

		//init game
		initializeGame(numPlayers, k, seed, &game);

		//place card at play position
		game.hand[testPlayer][handPos] = card;

		//set turn to testPlayer
		game.whoseTurn = testPlayer;

		//some play factors
		int treas = 0; //track number of treasure in deck
		int discardedCards = 0; //cards that will be discarded if not treas
		int playedCards = 1;
		int shuffledCards = 0;
		int treasFromShuffle = 0;
		int q = 0, s = 0;
		
		//set turn to testPlayer
		game.whoseTurn = testPlayer;

		//loop through deck, count until 2 treasure, this is what would be discarded  + 2
		while((treas < 2) && (q < game.deckCount[testPlayer])){
			if (game.deck[testPlayer][q] == 4 || game.deck[testPlayer][q] == 5 || game.deck[testPlayer][q] == 6){
				treas ++;
			}
			else{
				discardedCards++;
			}

			q++;
		}

		//to handle shuffle, build a discard pile
		//managing a shuffle of discard may be challenging, manipulate discard to include only 5 treasure
		if (treas < 2){

			game.discardCount[testPlayer] = 0; 

			if(rand() % 2 == 0){

				for(s = 0; s < 5; s++){
					//add treausre to discard for shuffle
					game.discardCount[testPlayer]++;
					game.discard[testPlayer][game.discardCount[testPlayer] - 1] = 4; //copper
					shuffledCards++;
				}

				/*if (treas == 1){
					treasFromShuffle = 1;
				}
				else if (treas == 0){
					treasFromShuffle = 2;
				}*/
			}

			
		}

		//place card at play position
		game.hand[testPlayer][handPos] = card;
		
		//copy game to test
		memcpy(&compGame, &game, sizeof(struct gameState));
		
		//card effect	
		cardEffect(card, choice1, choice2, choice3, &game, handPos, &bonus);

		//adventurer +2 treasure from deck, discard any seen cards other than treasure
		treas = 2;

		//testing deck count should be minus 2 treasure, less by any discarded cards, and 
		isEqual(game.deckCount[testPlayer], (compGame.deckCount[testPlayer] - treas - discardedCards + shuffledCards), "DECKCOUNT TEST");
		printf("-EXPECTED DECK COUNT %d. ACTUAL DECK COUNT %d.\n" , (compGame.deckCount[testPlayer] - treas - discardedCards + shuffledCards), game.deckCount[testPlayer]);
		if (game.deckCount[testPlayer] == (compGame.deckCount[testPlayer] - treas - discardedCards + shuffledCards)){
			deckTests[0] += 1;
		}
		else{
			deckTests[1] += 1;
		}

		//testing hand count should be more by trea and shuffle accounting for shuffle used as treas
		isEqual(game.handCount[testPlayer], (compGame.handCount[testPlayer] + treas ), "HANDCOUNT TEST");
		printf("-EXPECTED HANDCOUNT %d. ACTUAL HANDCOUNT %d.\n" , (compGame.handCount[testPlayer] + treas), game.handCount[testPlayer]);
		if (game.handCount[testPlayer] == (compGame.handCount[testPlayer] + treas)){
			handTests[0] += 1;
		}
		else{
			handTests[1] += 1;
		}

		//check card was played
		isEqual(game.playedCardCount, (compGame.playedCardCount + playedCards), "PLAYED COUNT TEST");
		printf("-EXPECTED PLAYED COUNT %d. ACTUAL PLAYED COUNT %d.\n", (compGame.playedCardCount + playedCards), game.playedCardCount);
		if (game.playedCardCount == (compGame.playedCardCount + playedCards)){
			playedCardTests[0] += 1;
		}
		else{
			playedCardTests[1] += 1;
		}

		//check appropriate discard 
		isEqual(game.discardCount[testPlayer], (compGame.discardCount[testPlayer] + discardedCards), "DISCARD COUNT TEST");
		printf("-EXPECTED DISCARD COUNT %d. ACTUAL DISCARD COUNT %d.\n", (compGame.discardCount[testPlayer] + discardedCards), game.discardCount[testPlayer]);
		if (game.discardCount[testPlayer] == (compGame.discardCount[testPlayer] + discardedCards)){
			discardTests[0] += 1;
		}
		else{
			discardTests[1] += 1;
		}

		printf("____END TEST #%d___\n", i+1);


	}

	printf("____ADVENTURER CARD TEST SUMMARY____\n");
	printf("\tADVENTURER DECK TESTS, %d PASSES, %d FAILS\n", deckTests[0], deckTests[1]);
	printf("\tADVENTURER HAND TESTS, %d PASSES, %d FAILS\n", handTests[0], handTests[1]);
	printf("\tADVENTURER PLAYED TESTS, %d PASSES, %d FAILS\n", playedCardTests[0], playedCardTests[1]);
	printf("\tADVENTURER DISCARD TESTS, %d PASSES, %d FAILS\n", discardTests[0], discardTests[1]);
	printf("\tADVENTURER ALL TESTS, %d PASSES, %d FAILS\n", deckTests[0]+handTests[0]+playedCardTests[0]+discardTests[0]+passed, deckTests[1]+handTests[1]+playedCardTests[1]+discardTests[1]+failed);
	printf("____END ADVENTURER CARD TEST____\n\n");
	
	return 0;
}

