/**************************************************************************
* CS 362-400 Assignment 4 
* By:  Lynn Herrick
* Date: 2/9/16
* Description: Write a random testers for two Dominion cards, one of which 
*       has to be the adventurer card. Check these random testers in.
***************************************************************************/
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>  //for floor()
#include <setjmp.h>
#include <signal.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//specific random test functions
int checkSmithy(struct gameState Test, int player);  //test oracle
void segfault(int sig_num);

//global vars
jmp_buf skipPoint;	//used for keeping randomizing alive if signal


int main(){  //test generator
	char testName[] = "Smithy";
	int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};
	int i, currentPlayer, deckcount, discardcount, handcount;
	struct gameState testState;
	srand(time(NULL));

	printf("---------------- Testing %s card. ----------------\n", testName);
	//amount of random tests -- similar to lecture
	for(i=0; i<2000; i++){	
		//set up proper preconditions and random input
		initializeGame(2, kingdomCards, 1000, &testState);
		currentPlayer = rand()%2;
		deckcount = floor(Random()*MAX_DECK);		//from lecture
		testState.deckCount[currentPlayer] = deckcount;
		discardcount = floor(Random()*MAX_DECK);   //from lecture
		testState.discardCount[currentPlayer] = discardcount;
		handcount = floor(Random()*MAX_HAND);		//from lecture
		testState.handCount[currentPlayer] = handcount;
		printf("Random Variables: Test number = %d Current Player = %d; Deck Count = %d; Discard Count = %d; Hand Count = %d\n", i+1, currentPlayer, deckcount, discardcount, handcount);
		checkVillage(testState, currentPlayer);
	}
	printf ("---------- Random Testing Complete -------------\n");
	return 0;
}


int checkVillage(struct gameState Clean, int player){
	int i;
	int p1, p2, pos, result;
	int testNum = 0;
	int testTreasureCount = 0;
	int cleanTreasureCount = 0;
	char cardTested[] = "Smithy";
	struct gameState Test;
	signal(SIGSEGV, segfault); // keeps alive if func causes segfault

	//set the correct player as random current player (p1)
	pos = -1;
	if(player == 0){
		p1 = player;
		p2 = 1;
	}
	else{
		p1 = player;
		p2 = 0;
	}

	memcpy (&Test, &Clean, sizeof(struct gameState));

	//keeps test alive if signal, jmp in signal handler
	if(setjmp(skipPoint) == 0){  
		//test chosen function
		result = cardEffect(smithy, 0, 0, 0, &Test, 0, 0);
	}else{
		goto tests;
	}

tests:
	//print info from test case
	printf("\n%d. Did player 1's hand change:\n", testNum);
	if(Test.handCount[p1] == Clean.handCount[p1] + 3 - 1){ //acount for discard of smithy
		printf("Passed. Hand count is %d + 3 - 1 = %d\n", Clean.handCount[p1], Test.handCount[p1]);
	} 
	else{  //fail
		printf("Failed. Hand count is %d + 3 - 1 = %d\n", Clean.handCount[p1], Test.handCount[p1]);
	}
	testNum++;
	printf("\n%d. Did player 2's hand change:\n", testNum);
	if(Test.handCount[p2] == Clean.handCount[p2]){
		printf("Passed.  Hand count is %d - 0 = %d\n", Clean.handCount[p2], Test.handCount[p2]);
	}
	else{	//fail
		printf("Failed. Hand count is %d - 0 = %d\n", Clean.handCount[p2], Test.handCount[p2]);
	}
	testNum++;
	printf("\n%d. Did player 1's deck change - 3:\n", testNum);
	if(Test.deckCount[p1] == Clean.deckCount[p1]-3){
		printf("Passed. Deck count is %d - 3 = %d\n", Clean.deckCount[p1], Test.deckCount[p1]);
	}
	else{	//fail
		printf("Failed. Deck count is %d - 3 = %d\n", Clean.deckCount[p1], Test.deckCount[p1]);
	}
	testNum++;
	printf("\n%d. Did player 2's deck change - 0:\n", testNum);
	if(Test.deckCount[p2] == Clean.deckCount[p2]){
		printf("Passed. Deck count is %d - 0 = %d\n", Clean.deckCount[p2], Test.deckCount[p2]);
	}
	else{	//fail
		printf("Passed. Deck count is %d - 0 = %d\n", Clean.deckCount[p2], Test.deckCount[p2]);
	}
	testNum++;
	printf("\n%d. Did player 1's discard pile change - 1:\n", testNum);
	if(Test.discardCount[p1] == Clean.discardCount[p1]-1){
		printf("Passed. Discard count is %d - 1 = %d\n", Clean.discardCount[p1], Test.discardCount[p1]);
	}
	else{	//fail
		printf("Failed. Discard count is %d - 1 = %d\n", Clean.discardCount[p1], Test.discardCount[p1]);
	}
	testNum++;
	printf("\n%d. Did player 2's discard pile change - 0:\n", testNum);
	if(Test.discardCount[p2] == Clean.discardCount[p2]){
		printf("Passed. Discard count is %d - 1 = %d\n", Clean.discardCount[p2], Test.discardCount[p2]);
	}
	else{	//fail
		printf("Failed. Discard count is %d - 1 = %d\n", Clean.discardCount[p2], Test.discardCount[p2]);
	}
	testNum++;
	printf("\n%d. Did the number of players change - 0:\n", testNum);
	if(Test.numPlayers == Clean.numPlayers){
		printf("Passed. Player count is %d - 0 = %d\n", Clean.numPlayers, Test.numPlayers);
	}
	else{	//fail
		printf("Failed. Player count is %d - 0 = %d\n", Clean.numPlayers, Test.numPlayers);
	}
	testNum++;
	printf("\n%d. Did the outpost played change - 0:\n", testNum);
	if(Test.outpostPlayed == Clean.outpostPlayed){
		printf("Passed. Outpost played is %d - 0 = %d\n", Clean.outpostPlayed, Test.outpostPlayed);
	}
	else{	//fail
		printf("Failed. Outpost played is %d - 0 = %d\n", Clean.outpostPlayed, Test.outpostPlayed);
	}
	testNum++;
	printf("\n%d. Did the outpost turn change - 0:\n", testNum);
	if(Test.outpostTurn == Clean.outpostTurn){
		printf("Passed. Outpost turn is %d = %d\n", Clean.outpostTurn, Test.outpostTurn);
	}
	else{	//fail
		printf("Failed. Outpost turn is %d = %d\n", Clean.outpostTurn, Test.outpostTurn);
	}
	testNum++;
	printf("\n%d. Did whose turn it is not chage:\n", testNum);
	if(Test.whoseTurn == Clean.whoseTurn){
		printf("Passed. Player's turn is %d = %d\n", Clean.whoseTurn, Test.whoseTurn);
	}
	else{	//fail
		printf("Failed. Player turn is %d = %d\n", Clean.whoseTurn, Test.whoseTurn);
	}
	testNum++;
	printf("\n%d. Did the phase change + 0':\n", testNum);
	if(Test.phase == Clean.phase){
		printf("Passed. Phase is %d + 0 = %d\n", Clean.phase, Test.phase);
	}
	else{	//fail
		printf("Failed. Phase is %d + 0 = %d\n", Clean.phase, Test.phase);
	}
	testNum++;
	printf("\n%d. Did the number of actions change + 0':\n", testNum);
	if(Test.numActions == Clean.numActions){
		printf("Passed. Numbers of actions is %d + 0 = %d\n", Clean.numActions, Test.numActions);
	}
	else{	//fail
		printf("Failed. Phase is %d + 0 = %d\n", Clean.numActions, Test.numActions);
	}
	testNum++;
	printf("\n%d. Did the coins change + 0':\n", testNum);
	if(Test.coins == Clean.coins){
		printf("Passed. Coins are %d + 0 = %d\n", Clean.coins, Test.coins);
	}
	else{	//fail
		printf("Failed. Coins are %d + 0 = %d\n", Clean.coins, Test.coins);
	}
	testNum++;
	printf("\n%d. Did the number of buys change + 0':\n", testNum);
	if(Test.numBuys == Clean.numBuys){
		printf("Passed. Number of buys is %d + 0 = %d\n", Clean.numBuys, Test.numBuys);
	}
	else{	//fail
		printf("Failed. Number of buys is %d + 0 = %d\n", Clean.numBuys, Test.numBuys);
	}
	testNum++;
	printf("\n%d. Did the played card count change + 1':\n", testNum);
	if(Test.playedCardCount == Clean.playedCardCount + 1){
		printf("Passed. Played card count is %d + 1 = %d\n", Clean.playedCardCount, Test.playedCardCount);
	}
	else{	//fail
		printf("Failed. Played card count is %d + 1 = %d\n", Clean.playedCardCount, Test.playedCardCount);
	}
	testNum++;


	printf("\n-------Completed tests on the %s card.-------\n", cardTested);
	return 0;
} 



/****************************************************************************************
* Desc: ignores any sigal and continues with unit tests while showing what caused a
*		signal to occur.
* Parameters: int signal number
****************************************************************************************/
void segfault(int sig_num){
	printf("------------ WARNING: signal issues start here  -----------");
	printf("----cardEffect() DID NOT RETURN PROPERLY FOR THIS TEST-----");
	longjmp(skipPoint, 0);  //since seg fault, this exits infinite handler
}
