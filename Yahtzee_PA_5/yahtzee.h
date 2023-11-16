#ifndef YAHTZEE_H_
#define YAHTZEE_H_

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "animation.h"

//keep track of scores
struct scoreCard {

	//player one
	int p1Score[16];
	int p1Preview[16];
	int p1Status[16];
	int p1finished;

	//player two
	int p2Score[16];
	int p2Preview[16];
	int p2Status[16];
	int p2finished;

	//score addresses
	/*int ones;0
	int twos;1
	int threes;2
	int fours;3
	int fives;4
	int sixes;5
	int bonus;6
	int sum;7
	int TOAK;8
	int FOAK;9
	int FH;10
	int SMST;11
	int LGST;12
	int CH;13
	int YAH;14
	//int total;15*/
};

//init scorecards
struct scoreCard initScoreCard();

//update scorecard//ran out of time to implement
struct scoreCard updatePlayerScore(struct scoreCard players, int currentPlayer, int option);

//calculate preview array
struct scoreCard calcPreview(struct scoreCard score, int* dice, int currentPlayer);

//switch player
int switchPlayer(int currentPlayer);

//populate dice array with random #s/populate with held dice.
void rollDice(int* diceArr, int* heldDiceArr, int size);

//rules loop
void rulesLoop();

//hold dice menu
void holdDice(int* diceArr, int* heldDiceArr, int size);

//bank score menu
struct scoreCard bankScore(struct scoreCard players, int currentPlayer, int* diceArr, int* heldDiceArr);

//print score options
void printScoreOptions(int* statusArr);

//check winner
void checkWinner(struct scoreCard players);

//player turn
struct scoreCard playerTurn(struct scoreCard players, int currentPlayer);

//GameLoop
void gameLoop();


#endif // !YAHTZEE_H_
