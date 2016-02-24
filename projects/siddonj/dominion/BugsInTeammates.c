/*************************************************
Onur's Code
*************************************************/
*Note: My test methods were ran against Onur's 'refactor.c' code as the card play methods
  were not defined in dominion.c. I renamed 'refactor.c' to 'dominion.c' to get the
  code to compile correctly.

Test method changes:
 Reduced the number of arguments passed in call to 'playAdventurer' to fit with his implementation of
 the adventurer card titled 'adventurerCard()'.

 Reduced the number of arguments passed in call to 'playSmithy' to fit with his implementation of
 the smithy card titled 'smithyCard()'.

 ==============================
 BUG 1
 ==============================

 Title: Smithy incorrect action decrement

 Class: "Logic Error"

 Date: 2/24/16
 Reported By: Justin Siddon
 Email: siddonj@oregonstate.edu


 Product: Dominion                       Version: 1.0
 Platform: Ubuntu                      Version: 12.04
 Browser: None                        Version:
 URL:

 Is it reproducible: Yes

 Description
 ===========
 The 'smithyCard' function doesn't correctly decrement the number of actions the player
 has when the function is called.


 Steps to Produce/Reproduce
 --------------------------
 Initialize a game of dominion
 Execute the 'smithyCard' function.
 Review the number of actions the player has remaining


 Expected Results
 ----------------
 Player whom played smithy card to have 1 less action than when they played the card.


 Actual Results
 --------------
 Player's action total is not decremented. Action total is the same before and after playing
 smithy card.


 Workarounds
 -----------
 Decrement the player's action after each call to 'smithyCard' function.


 Attachments (Code Causing Error)
 -----------
 // Smithy Card implementation
 int smithyCard (struct gameState *state, int handPos) {
   int i;
   int currentPlayer = whoseTurn(state);
   //+3 Cards
   for (i = 0; i < 3; i++)
   {
     drawCard(currentPlayer, state);
   }

   //discard card from hand
   discardCard(handPos, currentPlayer, state, 0);
   return 0;
 }


 Other Information
 -----------------

 ==============================
 BUG 2
 ==============================

Title: Smithy card incorrect post playment placement.

Class: "Logic Error"

Date: 2/24/16
Reported By: Justin Siddon
Email: siddonj@oregonstate.edu


Product: Dominion                       Version: 1.0
Platform: Ubuntu                      Version: 12.04
Browser: None                        Version:
URL:

Is it reproducible: Yes

Description
===========
The 'smithyCard' function places the played smithy card directly into the 'discard' pile.
Instead it should be placed into the 'played' card pile then discarded at the end of the
player's turn.


Steps to Produce/Reproduce
--------------------------
Initialize a game of dominion
Execute the 'smithyCard' function.
Review the size of the discard pile and compare it to the size of the played pile.



Expected Results
----------------
Player whom played smithy card to have 1 more card in played card pile, and no
additional cards in discard pile.


Actual Results
--------------
Discard will have 1 more card after calling method, played will have no additional
cards after calling method.


Workarounds
-----------
Decrement move the top discard card directly into the players played pile after
calling the 'smithyCard' function.


Attachments (Code Causing Error)
-----------
// Smithy Card implementation
int smithyCard (struct gameState *state, int handPos) {
    int i;
    int currentPlayer = whoseTurn(state);
      //+3 Cards
      for (i = 0; i < 3; i++)
  {
    drawCard(currentPlayer, state);
  }

      //discard card from hand
      discardCard(handPos, currentPlayer, state, 0);
      return 0;
}


Other Information
-----------------


==============================
BUG 3
==============================

Title: Adventurer incorrect amount of treasures added to players hand.

Class: "Logic Error"

Date: 2/24/16
Reported By: Justin Siddon
Email: siddonj@oregonstate.edu


Product: Dominion                       Version: 1.0
Platform: Ubuntu                      Version: 12.04
Browser: None                        Version:
URL:

Is it reproducible: Yes

Description
===========
The 'adventurerCard' function doesn't add the correct number of treasures to the
players hand.


Steps to Produce/Reproduce
--------------------------
Initialize a game of dominion
Execute the 'adventurerCard' function.
Review the number of treasures in the player's hand, compare it to the number they had when playing
the adventurer card.


Expected Results
----------------
Player whom played adventurer card to have 2 more treasure cards in hand than when they played the card.


Actual Results
--------------
Player's treasure total only increases by 1 treasure card.


Workarounds
-----------
None.


Attachments
-----------


Other Information
-----------------




==============================
BUG 4
==============================

Title: Adventurer doesn't validate the players card as an 'adventurer'.

Class: "Logic Error"

Date: 2/24/16
Reported By: Justin Siddon
Email: siddonj@oregonstate.edu


Product: Dominion                       Version: 1.0
Platform: Ubuntu                      Version: 12.04
Browser: None                        Version:
URL:

Is it reproducible: Yes

Description
===========
The 'adventurerCard' function doesn't validate that the players card they are playing is actually an adventurer card.


Steps to Produce/Reproduce
--------------------------
Initialize a game of dominion
Set the player's hand to just be treasure.
Execute the 'adventurerCard' function.
Function executes as normal.

Expected Results
----------------
Function call to return -1 since the player has no adventurers in hand.


Actual Results
--------------
Player is able to play adventurer card as normal


Workarounds
-----------
None.


Attachments (code causing error)
-----------
// There is no validation of the state of the player's hand prior to drawing a card and executing the adventurer logic.
    while(drawntreasure<2){
    if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
    shuffle(currentPlayer, state);
  }
  drawCard(currentPlayer, state);
  cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
  if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
    drawntreasure++;

Other Information
-----------------

/******************************* END ONUR's CODE ***************************/


/*************************************************
Martin's Code
*************************************************/
Changed the name of the playSmithy function in my code to smithyCard.
Changed the order of the smithyCard function in my from: smithyCard(testGame, testGame->whoseTurn, 0) to: smithyCard(int handPos, int currentPlayer, struct gameState *state)
Changed the name of the playAdventurer function in my code to adventurerCard.
Changed the order of the adventurerCard params from: adventurerCard(testGame, testGame->whoseTurn) to: adventurerCard(testGame->whoseTurn, testGame)
Changed the name of the playVillage function in my code to villageCard.
Changed the order of the villageCard arguments from: villageCard(testGame, testGame->whoseTurn, 0) to: villageCard(int handPos, int currentPlayer, struct gameState *state)
Removed cardtest3 from tests as he didn't implement the 'remodel' card.

==============================
BUG 1
==============================

Title: Smithy doesn't increase the players hand total by the correct amount.

Class: "Logic Error"

Date: 2/24/16
Reported By: Justin Siddon
Email: siddonj@oregonstate.edu


Product: Dominion                       Version: 1.0
Platform: Ubuntu                      Version: 12.04
Browser: None                        Version:
URL:

Is it reproducible: Yes

Description
===========
The 'smithyCard' function draw the correct number of cards into the players hand.


Steps to Produce/Reproduce
--------------------------
Initialize a game of dominion
Execute the 'smithyCard' function.


Expected Results
----------------
Player who played the smithy card hand size increases by a total of 2 cards.
Draw 3 and discard 1 (smithy) so net increase is 2.


Actual Results
--------------
Player's hand size only increases by 1.


Workarounds
-----------
None.


Attachments (code causing error)
-----------
	// You are initilizing 'i' to the 1, should be 0.
    for (i = 1; i < 3; i++)
	{
		drawCard(currentPlayer, state);
	}

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);
    return 0;

Other Information
-----------------

==============================
BUG 2
==============================

Title: Adventurer draw's to many cards.

Class: "Logic Error"

Date: 2/24/16
Reported By: Justin Siddon
Email: siddonj@oregonstate.edu


Product: Dominion                       Version: 1.0
Platform: Ubuntu                      Version: 12.04
Browser: None                        Version:
URL:

Is it reproducible: Yes

Description
===========
The 'adventurerCard' function doesn't draw the correct number of cards into the players hand.


Steps to Produce/Reproduce
--------------------------
Initialize a game of dominion
Execute the 'adventurerCard' function.


Expected Results
----------------
Player who played the adventurer card hand size increases by a total of 1 cards.
Draw cards until 2 treasures are revealed and discard 1 (adventurer) so net increase is 1.


Actual Results
--------------
Player's hand size increases by 3.


Workarounds
-----------
None.


Attachments (code causing error)
-----------
// This while loop is incorrectly testing the number of drawn treasures, allowing the person to draw 3
// treasures instead of 2.
int z = 0;	// this is the counter for the temp hand

while(drawntreasure <= 2)
{
  if (state->deckCount[currentPlayer] < 1)	//if the deck is empty we need to shuffle discard and add to deck
  {
      shuffle(currentPlayer, state);
  }
  drawCard(currentPlayer, state);

Other Information
-----------------

==============================
BUG 3
==============================

Title: Village doesn't incorrectly subtracts player's buy total.

Class: "Logic Error"

Date: 2/24/16
Reported By: Justin Siddon
Email: siddonj@oregonstate.edu


Product: Dominion                       Version: 1.0
Platform: Ubuntu                      Version: 12.04
Browser: None                        Version:
URL:

Is it reproducible: Yes

Description
===========
The 'villageCard' function removes all of the player's buys.


Steps to Produce/Reproduce
--------------------------
Initialize a game of dominion
Execute the 'villageCard' function.


Expected Results
----------------
Player who played the village card buy amount to be the same before playing village.


Actual Results
--------------
Player's buy amount is set to -1.


Workarounds
-----------
None.


Attachments (code causing error)
-----------
I can't seem to figure out where there is an error getting introduced into the players number of buys.
It looks like the game initialization function is incorrectly setting the number of buys to 0 to start with
also and then at somepoint during the villageCard method it is getting decremented again.

I tested only calling the game initialization and it sets the buys to 0. I then immediatly call villageCard and
the number of buys after is -1.


Other Information
-----------------
/******************************* END MARTIN's CODE ***************************/



/*************************************************
Andrew's Code
*************************************************/

==============================
BUG 1
==============================

Title:

Class: "Logic Error"

Date: 2/24/16
Reported By: Justin Siddon
Email: siddonj@oregonstate.edu


Product: Dominion                       Version: 1.0
Platform: Ubuntu                      Version: 12.04
Browser: None                        Version:
URL:

Is it reproducible: Yes

Description
===========
The 'smithyCard' function draw the correct number of cards into the players hand.


Steps to Produce/Reproduce
--------------------------
Initialize a game of dominion
Execute the 'smithyCard' function.


Expected Results
----------------
Player who played the smithy card hand size increases by a total of 2 cards.
Draw 3 and discard 1 (smithy) so net increase is 2.


Actual Results
--------------
Player's hand size only increases by 1.


Workarounds
-----------
None.


Attachments (code causing error)
-----------
	// You are initilizing 'i' to the 1, should be 0.
    for (i = 1; i < 3; i++)
	{
		drawCard(currentPlayer, state);
	}

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);
    return 0;

Other Information
-----------------
