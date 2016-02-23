/******************
 * Eric Olson
 * CS362_Assignment5
 * Village Function Test (Draw 1; +2 Actions)
 ******************/

#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int validate(struct gameState *pre, struct gameState *post, int errors);
void basic_setup(struct gameState *pre, struct gameState *post);

int main(){
  struct gameState *pre = malloc(sizeof(struct gameState)), *post = malloc(sizeof(struct gameState));
  struct infosStruct infos;
  int i, errors = 0;
  srand(time(NULL));
  
  printf("\n|------------------------------------------|\n");
  printf("  Running tests on village_play():\n");
  printf("|------------------------------------------|\n");
  
  /***** SCENARIO 1 - New game, hand=6, deck=5, discard=0  *****/
  printf("Running Scenario 1...\n");
  //Setup Scenario:
  basic_setup(pre, post);
  //Stage infos for teammates funciton:
  infos.currentPlayer = 0;
  infos.handPos = 5;
  //Have player 0 play Village card.
  effectVillage(post, &infos);
  //Check hand went from 6 to 6, deck went from 5 to 4, actions from 1 - 3, and played went from 0 - 1.
  errors = validate(pre, post, errors);
  
  /***** SCENARIO 2 - Shuffle Required, hand=6, deck=0, discard=10  *****/
  printf("Running Scenario 2...\n");
  //Setup Scenario:
  basic_setup(pre, post);
  //Empty Decks:
  memset(pre->deck[0], 0, 20 * sizeof(int));
  memset(post->deck[0], 0, 20 * sizeof(int));
  memset(pre->deck[1], 0, 20 * sizeof(int));
  memset(post->deck[1], 0, 20 * sizeof(int));
  pre->deckCount[0] = post->deckCount[0] = pre->deckCount[1] = post->deckCount[1] = 0;
  //Ensure cards in discard:
  for (i = 0; i < 10; i++){ pre->discard[0][i] = post->discard[0][i] = pre->discard[1][i] = post->discard[1][i] = rand() % 26; }
  pre->discardCount[0] = post->discardCount[0] = pre->discardCount[1] = post->discardCount[1] = 10;
  //Stage infos for teammates funciton:
  infos.currentPlayer = 0;
  infos.handPos = 5;
  //Have player 0 play Village card.
  effectVillage(post, &infos);
  //Check hand went from 6 to 6, deck went from 0 to 9(after shuffle of 10 cards), actions from 1 - 3 and played went from 0 - 1.
  errors = validate(pre, post, errors);
  
  //Report Findings
  if (errors) { printf("Tests Complete: village_play() failed %d tests.\n", errors); }
  else { printf("Tests Complete: No errors found.\n"); }

  return 0;  
}
  
void basic_setup(struct gameState *pre, struct gameState *post){
  int i, j, try, k[10] = { 0 };
  //Clear any previous data.
  memset(pre, 0, sizeof(struct gameState));
  memset(post, 0, sizeof(struct gameState));
  
  //randomize kingdom cards & initalize a game.
  k[0] = village;
  for (i = 1; i < 10; i++) {
    do{
      //Pick random kingdom card.
      try = ((rand() % 20) + 7);
      for (j = 0; j <= i; j++) {
        if (k[j] == try) { break; }  //If already used, break and try another random kingdom card.
        if (j == i) { k[i] = try; }  //If no duplicates found, assigned random kingdom card to array.
      }
    } while (k[i] == 0);      
  }
  if (initializeGame(2, k, ((rand() % 500) + 1), post) != 0) { printf( "Initalization of game failed.\n"); }
  
  //Ensure player 0 has village card in hand.
  post->hand[0][5] = village;
  post->handCount[0]++;
  
  //And create identical copies of gamestate before test.
  memcpy(pre, post, sizeof(struct gameState));
}
  
int validate(struct gameState *pre, struct gameState *post, int errors){
  int i;
  
  //Check pre vs post gameState's to ensure intended changes occured, and no unintended changes occured.
  if (pre->numPlayers != post->numPlayers){ 
    printf("state.numPlayers failed. (expected=%d, actual=%d)\n", pre->numPlayers, post->numPlayers);
    errors++;   
  }
  for (i = 0; i < treasure_map + 1; i++) {
    if (pre->supplyCount[i] != post->supplyCount[i]){ 
      printf("state.supplyCount[%d] failed. (expected=%d, actual=%d)\n", 
	     i, pre->supplyCount[i], post->supplyCount[i]);
      errors++;  
    }
    if (pre->embargoTokens[i] != post->embargoTokens[i]){ 
      printf("state.embargoTokens[%d] failed. (expected=%d, actual=%d)\n", 
	     i, pre->embargoTokens[i], post->embargoTokens[i]);
      errors++;  
    }
  }
  if (pre->outpostPlayed != post->outpostPlayed){ 
    printf("state.outpost->layed failed. (expected=%d, actual=%d)\n", pre->outpostPlayed, post->outpostPlayed);
    errors++;  
  }
  if (pre->outpostTurn != post->outpostTurn){ 
    printf("state.outpost->urn failed. (expected=%d, actual=%d)\n", pre->outpostTurn, post->outpostTurn);
    errors++;  
  }
  if (pre->whoseTurn != post->whoseTurn){ 
    printf("state.whoseTurn failed (expected=%d, actual=%d).\n", pre->whoseTurn, post->whoseTurn);
    errors++;  
  }
  if (pre->phase != post->phase){ 
    printf("state.phase failed. (expected=%d, actual=%d)\n", pre->phase, post->phase);
    errors++;  
  }
  //Confirm Actions increased by 2.
  if (pre->numActions != (post->numActions - 2)){ 
    printf("state.numActions failed. (expected=%d, actual=%d)\n", (pre->numActions + 2), post->numActions);
    errors++;  
  }
  if (pre->coins != post->coins){ 
    printf("state.coins failed. (expected=%d, actual=%d)\n", pre->coins, post->coins);
    errors++;  
  }
  if (pre->numBuys != post->numBuys){ 
     printf("state.numBuys failed. (expected=%d, actual=%d)\n", (pre->numBuys + 1), post->numBuys);
    errors++;  
  }
  //Actually check if player drew 1 card (and played 1 for no change):
  if (post->handCount[0] != pre->handCount[0]){ 
     printf("state.handCount failed. (expected=%d, actual=%d)\n", pre->handCount[0], post->handCount[0]);
    errors++;  
  }
  if (pre->handCount[1] != post->handCount[1]){ 
    printf("state.handCount[1] failed. (expected=%d, actual=%d)\n", pre->handCount[1], post->handCount[1]);
    errors++;
  }
  //Make sure 1 card was drawn from deck/discard.
  if ((pre->deckCount[0] + pre->discardCount[0]) != (post->deckCount[0] + post->discardCount[0] + 1)){ 
     printf("state.deckCount[0] failed. (expected=%d, actual=%d)\n", (pre->deckCount[0] + pre->discardCount[0] + 1), (post->deckCount[0] + post->discardCount[0]));
    errors++;
  }
  if (pre->deckCount[1] != post->deckCount[1]){
     printf("state.deckCount[1] failed. (expected=%d, actual=%d)\n", pre->deckCount[1], post->deckCount[1]);
     errors++;
  }
  if (pre->discardCount[1] != post->discardCount[1]){
     printf("state.deckCount[1] failed. (expected=%d, actual=%d)\n", pre->deckCount[1], post->deckCount[1]);
     errors++;
  }
  //Confirm village card was moved to played after use.
  if (post->playedCardCount != (pre->playedCardCount + 1)){ 
     printf("state.playedCardCount failed. (expected=%d, actual=%d)\n", (pre->playedCardCount + 1), post->playedCardCount);
    errors++;
  }

  return errors;
}
