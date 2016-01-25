#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>

#define DEBUG 0
#define NOISY_TEST 1

//Unit test for isgameOver function
//Preconditions:
//function accepts struct gameState *state 

//oracle makes sure returns valid 
int unitTest(struct gameState *post){
    srand(time(NULL));

    //define variables
    int sucess;
    struct gameState pre;
    memcpy(&pre,post,sizeof(struct gameState));
    //create an array to hold four integer inputs
    int input[4];
    //randomly generate 4 ints
    for(int i=0; i<4; i++){
        input[i]= rand();
    }

    //call function
    sucess=isGameOver(post);
    //memcmp game state size
    assert (memcmp(&pre,post, sizeof(struct gameState))==0);
    //if stack of Province cards is empty, the game ends
    assert (post->supplyCount[province] > 0);

    assert (sucess == 0);
    return 0;
}

int main () {
  //define variables  
  int i, n, r, p, deckCount, discardCount, handCount;
  //define a array of cards
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  //define a gamestate
  struct gameState G;

  printf ("Testing game is over function.\n");

  printf ("RANDOM TESTS.\n");
  //create random seed
  SelectStream(2);
  PutSeed(3);
  //for 2000 test cases
  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      //fill gamestate with random bits between 0-256 using ofset
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    //call function with test input
    unitTest(&G);

  }
  printf ("ALL TESTS OK\n");

  //fixed tests
  printf ("SIMPLE FIXED TESTS.\n");
  for (p = 0; p < 2; p++) {
    for (deckCount = 0; deckCount < 5; deckCount++) {
      for (discardCount = 0; discardCount < 5; discardCount++) {
	for (handCount = 0; handCount < 5; handCount++) {
	  memset(&G, 23, sizeof(struct gameState)); 
	  r = initializeGame(2, k, 1, &G);
	  G.deckCount[p] = deckCount;
	  memset(G.deck[p], 0, sizeof(int) * deckCount);
	  G.discardCount[p] = discardCount;
	  memset(G.discard[p], 0, sizeof(int) * discardCount);
	  G.handCount[p] = handCount;
	  memset(G.hand[p], 0, sizeof(int) * handCount);
	  //run unit test.
      unitTest(&G);

	}
      }
    }
  }

  return 0;
}
