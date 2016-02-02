/*Jonathan Lagrew
 *cardtest4.c
 *test playCouncil_Room()
 *Notes:
 *Adventurer is an action card that draws cards from the player's deck until 2 treasure cards are drawn.
 */
 /*
 * Basic Requirements of Adventurer:
 * 1. Current player should receive a total of 2 treasure cards.
 * 2. If drawn card is not a treasure card, then discard and pick a new card.
 * 3. No state change should occur for other players.
 * 4. No state change should occur to the victory drawnCard piles and kingdom card piles.
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

#define MAX_HAND_TEST 200
#define MAX_DECK_TEST 200
#define TESTCARD "Adventurer"

int testPlayCouncil_Room(struct gameState *after, int handPos)
{
	int i;
	int p = after->whoseTurn;
	struct gameState before;
	memcpy(&before, after, sizeof(struct gameState));
	
	playCouncil_Room(after, handPos);
	
	//drawing 4 cards and discard council_room. Net gain = 3;
	before.handCount[p] = before.handCount[p] + 3;
	if(before.handCount[p] != after->handCount[p])
	{
		printf("ERROR 1: current player %d should have net gain of 3 cards in hand! before count: %d after count: %d\n", p, before.handCount[p], after->handCount[p]);
	}
	//numBuys is incremented by 1
	before.numBuys++;
	if(before.numBuys != after->numBuys)
	{
		printf("ERROR 2: player did not get another Buy point. before numBuys: %d, after numBuys: %d.\n", before.numBuys, after->numBuys);
	}
	//every other player should have an extra card in their deck
	for(i = 0; i < before.numPlayers; i ++)
	{
		if(i != p)
		{
			before.handCount[i]++;
			
			if(before.handCount[i] != after->handCount[i])
			{
				printf("ERROR 3: player %d did not recieve a card! before count: %d after count: %d\n", i, before.handCount[i], after->handCount[i]);
			}
		}
	}

	//still current player?
	if(before.whoseTurn != after->whoseTurn)
		printf("ERROR: Current player has changed from %i to %i", before.whoseTurn, after->whoseTurn);
	
	//check coins
	if(before.coins != after->coins)
		printf("ERROR: Number of coins changed from %i to %i", before.coins, after->coins);
	//check number of actions
	if(before.numActions != after->numActions)
		printf("ERROR: Number of actions has changed from %i to %i", before.numActions, after->numActions);
	
	return 0;
}

int main()
{
	int p;
	int numTests = 600;
	struct gameState G;
	int handPos;
	int numPlayers;
	int maxPlayers = 5;
	int i, j, m, n, q, r, s;
	
	//generates random tests
	printf("STARTING RANDOM TESTS.\n");
	
	SelectStream(2);
	PutSeed(3);
	printf("Testing playCouncil_Room() cardtest4.\n");
	
	for(s = 0; s < numTests; s++)
	{
		for(numPlayers = 2; numPlayers < maxPlayers; numPlayers++)
		{
			for(p = 0; p < numPlayers; p++)
			{
				for (i = 0; i < sizeof(struct gameState); i++) { //from the lessons, random gameState
					((char*)&G)[i] = floor(Random() * 256);
				}
				
				G.whoseTurn = p;
				G.numPlayers = numPlayers;
				
				//filling in random cards based on lecture 11 and 12 Random Testing 
				//give cards to all players
				for(j = 0; j < numPlayers; j++)
				{
					G.handCount[j] = floor(Random() * MAX_HAND_TEST)+1;//need at least one village in our hand
					G.deckCount[j] = floor(Random() * MAX_DECK_TEST);
					G.discardCount[j] = floor(Random() * MAX_DECK_TEST);
					
					for(m = 0; m < G.handCount[j]; m++)
					{
						G.hand[j][m] = floor(Random() * treasure_map) + 1;
					}
					
					for(r = 0; r < G.discardCount[j]; r++)
					{
						G.discard[j][r] = floor(Random() * treasure_map) + 1;
					}

					for(n = 0; n < G.deckCount[j]; n++)
					{
						G.deck[j][n] = floor(Random() * treasure_map) + 1;
					}

				}
				
				//only current player has played cards
				G.playedCardCount = floor(Random() * MAX_DECK_TEST);
				for(q = 0; q < G.playedCardCount; q++)
				{
					G.playedCards[q] = floor(Random() * treasure_map) + 1;
				}	
				G.numBuys = 1; //not buying cards so any number will do
				handPos = floor(Random() * G.handCount[p]);//place council_room in a random pos
				G.hand[p][handPos] = council_room;
				
				testPlayCouncil_Room(&G, handPos);
				
			}
		}
	}
	
	printf("PLAY COUNCIL_ROOM TESTS FINISHED.\n\n");
	return 0;
}