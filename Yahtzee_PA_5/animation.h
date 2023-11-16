#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "yahtzee.h"

//print menu option
void printMenuOp(char* number, char* option);

// print the score card
void printScoreCard(struct scoreCard score);

// print the score preview
//todo: show preview for current player score for other player
void printScorePreview(struct scoreCard score, int currentPlayer);

//print dice animation
void printDice(int* diceArr, int* heldDiceArr);

//print Yahtzee title animation
void printYahtTitle();

//print game rules
void printRules();


#endif // !ANIMATION_H_
