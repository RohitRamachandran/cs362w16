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

//Unit test for Adventurer Card
//function accepts: currentplayer, struct gameState *state 

//oracle makes sure returns valid 
int unitTest(int player,struct gameState *post){
    srand(time(NULL));

    //define variables
    struct gameState pre;
    memcpy(&pre,post,sizeof(struct gameState));

    //call function
    adventurerCard(player, post);

    //memcmp game state size
    if(memcmp(&pre,post, sizeof(struct gameState))!=0){
        printf("gameState memory is wrong");
        exit(3);
    }
    //card specific checks 
    //player hand size should be 2 larger after gaining treasure
    if(post->handCount != pre.handCount +2){
        printf("Player did not receive 2 additional cards correctly");
        exit(1);
    }
    //player should have at least 2 more treasures
    if(post->coins < pre.coins +2){
        printf("player did not receive 2 additional coins");
        exit(2);
    }

    return 0;
}

//section directly uses code from betterCardTest.c
int main () {
  //define variables  
  int i, n, r, p, deckCount, discardCount, handCount;
  //define a array of cards
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  //define a gamestate
  struct gameState G;

  printf ("Testing adventurer card.\n");

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
    unitTest(p, &G);

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
        unitTest(p, &G);
	    }
      }
    }
  }
  printf ("FIXED TESTS Complete.\n");  
  return 0;
}
