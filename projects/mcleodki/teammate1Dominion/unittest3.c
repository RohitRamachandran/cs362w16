/*

isGameOver - 	if province cards are empty, game ends
		if three supply piles are at 0, game ends


- user gets all province cards 
- user empties 3 supply piles
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>
#include <math.h>


int initTestGame(int numPlayers, int kingdomCards[10], int randomSeed,
		   struct gameState *state);

int main (int argc, char** argv) {
  struct gameState state;
  struct gameState previousState;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,sea_hag, council_room, smithy};

  int seed = 2;
  
  
  int game_over;
  int numPlayers = 2;
  int player = 0;


	printf("\n\n\n\n---------------- unittest3 ----------------\n\n");

	printf("----------------Testing Card: isGameOver ----------------\n");

	/******* Test province cards running out *******/

	printf("*******Test1: Province cards running out *******\n");
	initTestGame(2, k, seed, &state);
	assert(numHandCards(&state) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(gainCard(province,&state,2,player) == 0);
	assert(numHandCards(&state) == 8);
	previousState = state;
	endTurn(&state);
	game_over = isGameOver(&state);
	if(state.supplyCount[province] == 0 && game_over == 1)
	{
		printf("PASS: Province cards running out\n\n\n");
		
	}
	else
	{	printf("FAIL: Province cards running out\n\n\n"); }






	/******* Test Three supply piles empty *******/

	printf("*******Test2: Three supply piles empty *******\n");
	initTestGame(3, k, seed, &state);
	assert(numHandCards(&state) == 0);
	assert(gainCard(village,&state,2,player) == 0);
	assert(gainCard(village,&state,2,player) == 0);
	assert(gainCard(village,&state,2,player) == 0);
	assert(gainCard(village,&state,2,player) == 0);
	assert(gainCard(village,&state,2,player) == 0);
	assert(gainCard(village,&state,2,player) == 0);
	assert(gainCard(village,&state,2,player) == 0);
	assert(gainCard(village,&state,2,player) == 0);
	assert(gainCard(village,&state,2,player) == 0);
	assert(gainCard(village,&state,2,player) == 0);


	assert(gainCard(smithy,&state,2,player) == 0);
	assert(gainCard(smithy,&state,2,player) == 0);
	assert(gainCard(smithy,&state,2,player) == 0);
	assert(gainCard(smithy,&state,2,player) == 0);
	assert(gainCard(smithy,&state,2,player) == 0);
	assert(gainCard(smithy,&state,2,player) == 0);
	assert(gainCard(smithy,&state,2,player) == 0);
	assert(gainCard(smithy,&state,2,player) == 0);
	assert(gainCard(smithy,&state,2,player) == 0);
	assert(gainCard(smithy,&state,2,player) == 0);


	assert(gainCard(adventurer,&state,2,player) == 0);
	assert(gainCard(adventurer,&state,2,player) == 0);
	assert(gainCard(adventurer,&state,2,player) == 0);
	assert(gainCard(adventurer,&state,2,player) == 0);
	assert(gainCard(adventurer,&state,2,player) == 0);
	assert(gainCard(adventurer,&state,2,player) == 0);
	assert(gainCard(adventurer,&state,2,player) == 0);
	assert(gainCard(adventurer,&state,2,player) == 0);
	assert(gainCard(adventurer,&state,2,player) == 0);
	assert(gainCard(adventurer,&state,2,player) == 0);

	assert(numHandCards(&state) == 30);
	previousState = state;
	endTurn(&state);
	game_over = isGameOver(&state);

	int i;
	int j = 0;
  	for(i = 0; i < 25; i++)
    	{
      		if (state.supplyCount[i] == 0)
		{
	  		j++;
		}
    	}
  	
	
	if(j >= 3 && game_over == 1)
	{
		printf("PASS: Three supply piles empty\n\n\n");
		
	}
	else
	{	printf("FAIL: Three supply piles empty\n\n\n"); }




	


	printf("*******Testing isGameOver Complete!*******\n\n\n");
	return 0;
} // main



// added my own game initialization to use with assignment 3
int initTestGame(int numPlayers, int kingdomCards[10], int randomSeed,
		   struct gameState *state) {

  int i;
  int j;
  int it;			
  //set up random number generator
  SelectStream(1);
  PutSeed((long)randomSeed);
  
  //check number of players
  if (numPlayers > MAX_PLAYERS || numPlayers < 2)
    {
      return -1;
    }

  //set number of players
  state->numPlayers = numPlayers;

  //check selected kingdom cards are different
  for (i = 0; i < 10; i++)
    {
      for (j = 0; j < 10; j++)
        {
	  if (j != i && kingdomCards[j] == kingdomCards[i])
	    {
	      return -1;
	    }
        }
    }


  //initialize supply
  ///////////////////////////////

  //set number of Curse cards
  if (numPlayers == 2)
    {
      state->supplyCount[curse] = 10;
    }
  else if (numPlayers == 3)
    {
      state->supplyCount[curse] = 20;
    }
  else
    {
      state->supplyCount[curse] = 30;
    }

  //set number of Victory cards
  if (numPlayers == 2)
    {
      state->supplyCount[estate] = 8;
      state->supplyCount[duchy] = 8;
      state->supplyCount[province] = 8;
    }
  else
    {
      state->supplyCount[estate] = 12;
      state->supplyCount[duchy] = 12;
      state->supplyCount[province] = 12;
    }

  //set number of Treasure cards
  state->supplyCount[copper] = 60 - (7 * numPlayers);
  state->supplyCount[silver] = 40;
  state->supplyCount[gold] = 30;

  //set number of Kingdom cards
  for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
    {
      for (j = 0; j < 10; j++)           		//loop chosen cards
	{
	  if (kingdomCards[j] == i)
	    {
	      //check if card is a 'Victory' Kingdom card
	      if (kingdomCards[j] == great_hall || kingdomCards[j] == gardens)
		{
		  if (numPlayers == 2){ 
		    state->supplyCount[i] = 8; 
		  }
		  else{ state->supplyCount[i] = 12; }
		}
	      else
		{
		  state->supplyCount[i] = 10;
		}
	      break;
	    }
	  else    //card is not in the set choosen for the game
	    {
	      state->supplyCount[i] = -1;
	    }
	}

    }

  ////////////////////////
  //supply intilization complete

  //set player decks
  // start all players with empty decks for the test games
 
  for (i = 0; i < numPlayers; i++)
    {
      state->deckCount[i] = 0;
      for (j = 0; j < 3; j++)
	{
	  state->deck[i][j] = estate;
	  state->deckCount[i]++;
	}
      for (j = 3; j < 10; j++)
	{
	  state->deck[i][j] = copper;
	  state->deckCount[i]++;		
	}
    }

  //shuffle player decks
  for (i = 0; i < numPlayers; i++)
    {
      if ( shuffle(i, state) < 0 )
	{
	  return -1;
	}
    }

  // set counts to 0
  for (i = 0; i < numPlayers; i++)
    {  
      //initialize hand size to zero
      state->handCount[i] = 0;
      state->discardCount[i] = 0;
    }
  
  //set embargo tokens to 0 for all supply piles
  for (i = 0; i <= treasure_map; i++)
    {
      state->embargoTokens[i] = 0;
    }

  //initialize first player's turn
  state->outpostPlayed = 0;
  state->phase = 0;
  state->numActions = 1;
  state->numBuys = 1;
  state->playedCardCount = 0;
  state->whoseTurn = 0;
  state->handCount[state->whoseTurn] = 0;
  //int it; move to top

  //Moved draw cards to here, only drawing at the start of a turn
  //for (it = 0; it < 5; it++){
  //  drawCard(state->whoseTurn, state);
  //}

  updateCoins(state->whoseTurn, state, 0);

  return 0;
}

