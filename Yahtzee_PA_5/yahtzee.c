#include "yahtzee.h"

//init scorecard
struct scoreCard initScoreCard() {
	struct scoreCard newCard;
	int i;

	//set score to 0
	for (i = 0; i < 16; i++) {
		newCard.p1Score[i] = 0;
	}
	for (i = 0; i < 16; i++) {
		newCard.p2Score[i] = 0;
	}

	//set preview to 0
	for (i = 0; i < 16; i++) {
		newCard.p1Preview[i] = 0;
	}
	for (i = 0; i < 16; i++) {
		newCard.p2Preview[i] = 0;
	}

	//set status to 0
	for (i = 0; i < 16; i++) {
		newCard.p1Status[i] = 0;
	}
	for (i = 0; i < 16; i++) {
		newCard.p2Status[i] = 0;
	}

	newCard.p1finished = 0;
	newCard.p2finished = 0;

	return newCard;
}

//update scorecard and reset preview
struct scoreCard updatePlayerScore(struct scoreCard players, int currentPlayer, int option) {
	struct scoreCard newScore = players;
	int i;
	switch (currentPlayer) {
	case 1:
		if (newScore.p1Status[option] == 0) {
			newScore.p1Score[option] = newScore.p1Preview[option];

			for (i = 0; i < 16; i++) {
				newScore.p1Preview[i] = 0;
			}

		}
		break;
	case 2:
		if (newScore.p2Status[option] == 0) {
			newScore.p2Score[option] = newScore.p1Preview[option];

			for (i = 0; i < 16; i++) {
				newScore.p2Preview[i] = 0;
			}
		}
		break;
	}

	return newScore;
}

//calculate preview array
struct scoreCard calcPreview(struct scoreCard score, int* dice, int currentPlayer) {

	struct scoreCard newScore = score;

	int tally[6] = { 0 };

	int i;
	for (i = 0; i < 5; i++) {
		switch (dice[i]) {
		case 1:
			tally[0] += 1;
			break;
		case 2:
			tally[1] += 1;
			break;
		case 3:
			tally[2] += 1;
			break;
		case 4:
			tally[3] += 1;
			break;
		case 5:
			tally[4] += 1;
			break;
		case 6:
			tally[5] += 1;
			break;
		}
	}

	//dice combo logic
	int preview[16] = { 0 };
	int threeOfaKind = 0;
	int fourOfaKind = 0;
	int j;

	for (i = 0; i < 6; i++) {
		//set ones-sixes
		if (tally[i] > 0) {
			preview[i] = tally[i] * (i + 1);
		}
		//three of a kind
		if (tally[i] == 3) {
			if (tally[i] * (i + 1) > threeOfaKind) {
				threeOfaKind = tally[i] * (i + 1);
			}
			//check for full house
			for (j = 0; j < 6; j++) {
				if (tally[j] == 2) {
					preview[10] = 25;
				}
			}
		}
		//four of a kind
		if (tally[i] == 4) {
			if (tally[i] * (i + 1) > fourOfaKind) {
				fourOfaKind = tally[i] * (i + 1);
			}
		}
		//yahtzee
		if (tally[i] == 5) {
			preview[14] = 50;
		}

		//chance
		preview[13] += tally[i] * (i + 1);
	}
	//small straight
	if (tally[0] && tally[1] && tally[2] && tally[3]) {
		preview[11] = 30;
	}
	if (tally[1] && tally[2] && tally[3] && tally[4]) {
		preview[11] = 30;
	}
	if (tally[2] && tally[3] && tally[4] && tally[5]) {
		preview[11] = 30;
	}
	
	//large straight
	if (tally[0] && tally[1] && tally[2] && tally[3] && tally[4]) {
		preview[12] = 40;
	}
	if (tally[1] && tally[2] && tally[3] && tally[4] && tally[5]) {
		preview[12] = 40;
	}

	//set highest three/four of a kind
	preview[8] = threeOfaKind;
	preview[9] = fourOfaKind;

	//compare status array to preview and set
	switch (currentPlayer) {
	case 1:
		for (i = 0; i < 16; i++) {
			if (newScore.p1Status[i] == 0) {
				newScore.p1Preview[i] = preview[i];
			}
		}
		break;
	case 2:
		for (i = 0; i < 16; i++) {
			if (newScore.p2Status[i] == 0) {
				newScore.p2Preview[i] = preview[i];
			}
		}
		break;
	}

	return newScore;
	
}

//switch player
int switchPlayer(int currentPlayer) {
	int nextPlayer;
	if (currentPlayer == 1) {
		nextPlayer = 2;
	}
	else {
		nextPlayer = 1;
	}
	return nextPlayer;
}

//reset dice array,fill with rand/ overwrite with held dice
void rollDice(int* diceArr, int* heldDiceArr, int size) {
	int i;

	for (i = 0; i < size; i++) {

		diceArr[i] = 0;
	}

	for (i = 0; i < size; i++) {

		diceArr[i] = (rand() % 6) + 1;
	}

	//overwrite with held dice
	for (i = 0; i < size; i++) {
		if (heldDiceArr[i] > 0) {
			diceArr[i] = heldDiceArr[i];
		}
	}

}

//rules loop
void rulesLoop() {

	//print rules
	system("cls");
	printRules();

	//print menu
	printMenuOp("1", "Exit to Menu");

	int choice = 0;

	while (choice != 1) {
		scanf("%d", &choice);
	}
}

//hold dice menu
void holdDice(int* diceArr, int* heldDiceArr, int size) {
	int choice = 0;

	while (choice != 6) {
		choice = 0;
		system("cls");
		printDice(diceArr, heldDiceArr);
		printf("\n");
		printMenuOp("1", "one");
		printMenuOp("2", "two");
		printMenuOp("3", "three");
		printMenuOp("4", "four");
		printMenuOp("5", "five");
		printMenuOp("6", "exit to game");

		scanf("%d", &choice);

		switch (choice) {
		case 1:
			if (diceArr[0] == 0) {
				diceArr[0] = heldDiceArr[0];
				heldDiceArr[0] = 0;
			}
			else {
				heldDiceArr[0] = diceArr[0];
				diceArr[0] = 0;
			}
			break;
		case 2:
			if (diceArr[1] == 0) {
				diceArr[1] = heldDiceArr[1];
				heldDiceArr[1] = 0;
			}
			else {
				heldDiceArr[1] = diceArr[1];
				diceArr[1] = 0;
			}
			break;
		case 3:
			if (diceArr[2] == 0) {
				diceArr[2] = heldDiceArr[2];
				heldDiceArr[2] = 0;
			}
			else {
				heldDiceArr[2] = diceArr[2];
				diceArr[2] = 0;
			}
			break;
		case 4:
			if (diceArr[3] == 0) {
				diceArr[3] = heldDiceArr[3];
				heldDiceArr[3] = 0;
			}
			else {
				heldDiceArr[3] = diceArr[3];
				diceArr[3] = 0;
			}
			break;
		case 5:
			if (diceArr[4] == 0) {
				diceArr[4] = heldDiceArr[4];
				heldDiceArr[4] = 0;
			}
			else {
				heldDiceArr[4] = diceArr[4];
				diceArr[4] = 0;
			}
			break;
		case 6:
			break;
		default:
			break;

		}
	}
}

//bank score menu
//todo: update status array
struct scoreCard bankScore(struct scoreCard players, int currentPlayer, int* diceArr, int* heldDiceArr) {

	struct scoreCard newScore = players;

	int choice = 0;

	while (choice == 0) {

		choice = 0;

		//print score options
		system("cls");
		printScorePreview(newScore, currentPlayer);
		printDice(diceArr, heldDiceArr);
		if (currentPlayer == 1) {
			printScoreOptions(newScore.p1Status);
		}
		else {
			printScoreOptions(newScore.p2Status);
		}
		
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			//ones
			if (currentPlayer == 1) {
				if (newScore.p1Status[0] == 0) {
					newScore.p1Score[0] = newScore.p1Preview[0];
					newScore.p1Status[0] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}

			}
			else {
				if (newScore.p2Status[0] == 0) {
					newScore.p2Score[0] = newScore.p2Preview[0];
					newScore.p2Status[0] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}

			}
			
			break;
		case 2:
			//twos
			if (currentPlayer == 1) {
				if (newScore.p1Status[1] == 0) {
					newScore.p1Score[1] = newScore.p1Preview[1];
					newScore.p1Status[1] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			else {
				if (newScore.p2Status[1] == 0) {
					newScore.p2Score[1] = newScore.p2Preview[1];
					newScore.p2Status[1] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			
			break;
		case 3:
			//threes
			if (currentPlayer == 1) {
				if (newScore.p1Status[2] == 0) {
					newScore.p1Score[2] = newScore.p1Preview[2];
					newScore.p1Status[2] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			else {
				if (newScore.p2Status[2] == 0) {
					newScore.p2Score[2] = newScore.p2Preview[2];
					newScore.p2Status[2] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			
			break;
		case 4:
			//fours
			if (currentPlayer == 1) {
				if (newScore.p1Status[3] == 0) {
					newScore.p1Score[3] = newScore.p1Preview[3];
					newScore.p1Status[3] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			else {
				if (newScore.p2Status[3] == 0) {
					newScore.p2Score[3] = newScore.p2Preview[3];
					newScore.p2Status[3] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			break;
		case 5:
			//fives
			if (currentPlayer == 1) {
				if (newScore.p1Status[4] == 0) {
					newScore.p1Score[4] = newScore.p1Preview[4];
					newScore.p1Status[4] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			else {
				if (newScore.p2Status[4] == 0) {
					newScore.p2Score[4] = newScore.p2Preview[4];
					newScore.p2Status[4] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			
			break;
		case 6:
			//sixes
			if (currentPlayer == 1) {
				if (newScore.p1Status[5] == 0) {
					newScore.p1Score[5] = newScore.p1Preview[5];
					newScore.p1Status[5] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			else {
				if (newScore.p2Status[5] == 0) {
					newScore.p2Score[5] = newScore.p2Preview[5];
					newScore.p2Status[5] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			
			break;
		case 7:
			//Three of a kind
			if (currentPlayer == 1) {
				if (newScore.p1Status[8] == 0) {
					newScore.p1Score[8] = newScore.p1Preview[8];
					newScore.p1Status[8] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			else {
				if (newScore.p2Status[8] == 0) {
					newScore.p2Score[8] = newScore.p2Preview[8];
					newScore.p2Status[8] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			
			break;
		case 8:
			//four of a kind
			if (currentPlayer == 1) {
				if (newScore.p1Status[9] == 0) {
					newScore.p1Score[9] = newScore.p1Preview[9];
					newScore.p1Status[9] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			else {
				if (newScore.p2Status[9] == 0) {
					newScore.p2Score[9] = newScore.p2Preview[9];
					newScore.p2Status[9] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			
			break;
		case 9:
			//full house
			if (currentPlayer == 1) {
				if (newScore.p1Status[10] == 0) {
					newScore.p1Score[10] = newScore.p1Preview[10];
					newScore.p1Status[10] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			else {
				if (newScore.p2Status[10] == 0) {
					newScore.p2Score[10] = newScore.p2Preview[10];
					newScore.p2Status[10] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			
			break;
		case 10:
			//small straight
			if (currentPlayer == 1) {
				if (newScore.p1Status[11] == 0) {
					newScore.p1Score[11] = newScore.p1Preview[11];
					newScore.p1Status[11] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			else {
				if (newScore.p2Status[11] == 0) {
					newScore.p2Score[11] = newScore.p2Preview[11];
					newScore.p2Status[11] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			
			break;
		case 11:
			//large straight
			if (currentPlayer == 1) {
				if (newScore.p1Status[12] == 0) {
					newScore.p1Score[12] = newScore.p1Preview[12];
					newScore.p1Status[12] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			else {
				if (newScore.p2Status[12] == 0) {
					newScore.p2Score[12] = newScore.p2Preview[12];
					newScore.p2Status[12] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			
			break;
		case 12:
			//chance
			if (currentPlayer == 1) {
				if (newScore.p1Status[13] == 0) {
					newScore.p1Score[13] = newScore.p1Preview[13];
					newScore.p1Status[13] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			else {
				if (newScore.p2Status[13] == 0) {
					newScore.p2Score[13] = newScore.p2Preview[13];
					newScore.p2Status[13] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			
			break;
		case 13:
			//yahtzee
			if (currentPlayer == 1) {
				if (newScore.p1Status[14] == 0) {
					newScore.p1Score[14] = newScore.p1Preview[14];
					newScore.p1Status[14] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			else {
				if (newScore.p2Status[14] == 0) {
					newScore.p2Score[14] = newScore.p2Preview[14];
					newScore.p2Status[14] = 1;
				}
				else {
					printf("already filled\n");
					choice = 0;
				}
			}
			
			break;
		default:
			break;
		}

	}
	//update if finished
	int i;
	int unfinished;
	if (currentPlayer == 1) {
		unfinished = 0;
		for (i = 0; i < 16; i++) {
			if (newScore.p1Status[i] == 0) {
				unfinished += 1;
			}
		}
		if (unfinished > 0) {
			newScore.p1finished = 0;
		}
		else {
			newScore.p1finished = 1;
		}

	}
	else {
		unfinished = 0;
		for (i = 0; i < 16; i++) {
			if (newScore.p2Status[i] == 0) {
				unfinished += 1;
			}
		}
		if (unfinished > 0) {
			newScore.p2finished = 0;
		}
		else {
			newScore.p2finished = 1;
		}
	}
	//update bonus, sum
	int total;
	if (currentPlayer == 1) {
		total = 0;
		for (i = 0; i < 6; i++) {
			total += newScore.p1Score[i];
		}
		if (total > 63) {
			newScore.p1Score[6] = 35;
		}
		newScore.p1Score[7] = total;
	}
	else {
		total = 0;
		for (i = 0; i < 6; i++) {
			total += newScore.p2Score[i];
		}
		if (total > 63) {
			newScore.p2Score[6] = 35;
		}
		newScore.p2Score[7] = total;

	}
	//update total
	if (currentPlayer == 1) {
		total = 0;
		for (i = 5; i < 15; i++) {
			total += newScore.p1Score[i];
		}
		newScore.p1Score[15] = total;
	}
	else {
		total = 0;
		for (i = 5; i < 15; i++) {
			total += newScore.p2Score[i];
		}
		newScore.p2Score[15] = total;
	}

	return newScore;
}

//print score options
void printScoreOptions(int* statusArr) {
	if (statusArr[0] == 0) {
		printMenuOp("1", "ones");
	}
	if (statusArr[1] == 0) {
		printMenuOp("2", "twos");
	}
	if (statusArr[2] == 0) {
		printMenuOp("3", "threes");
	}
	if (statusArr[3] == 0) {
		printMenuOp("4", "fours");
	}
	if (statusArr[4] == 0) {
		printMenuOp("5", "fives");
	}
	if (statusArr[5] == 0) {
		printMenuOp("6", "sixes");
	}
	if (statusArr[8] == 0) {
		printMenuOp("7", "Three of a Kind");
	}
	if (statusArr[9] == 0) {
		printMenuOp("8", "Four of a kind");
	}
	if (statusArr[10] == 0) {
		printMenuOp("9", "Full House");
	}
	if (statusArr[11] == 0) {
		printMenuOp("10", "Small Straight");
	}
	if (statusArr[12] == 0) {
		printMenuOp("11", "Large Straight");
	}
	if (statusArr[13] == 0) {
		printMenuOp("12", "Chance");
	}
	if (statusArr[14] == 0) {
		printMenuOp("13", "YAHTZEE");
	}
}

//check winner
void checkWinner(struct scoreCard players) {
	
	int choice = 0;

	while (choice != 1) {
		if (players.p1Score[15] > players.p2Score[15]) {
			system("cls");
			printScoreCard(players);
			printf("player 1 wins!");
			printMenuOp("1", "Exit to main menu");
		}
		else {
			system("cls");
			printScoreCard(players);
			printf("player 2 wins!");
			printMenuOp("1", "Exit to main menu");
		}
	}
}

//player turn
struct scoreCard playerTurn(struct scoreCard players, int currentPlayer) {

	//return value
	struct scoreCard newScore = players;

	//dice array/held dice array
	int dice[5] = { 0 };
	int heldDice[5] = { 0 };

	//init roll
	rollDice(&dice, &heldDice, 5);
	
	//number of rolls left
	int roll = 3;

	//turn
	newScore = calcPreview(newScore, &dice, currentPlayer);
	system("cls");
	printScorePreview(newScore, currentPlayer);
	printDice(&dice, &heldDice);
	printf("Current Player: %3d\n", currentPlayer);
	printf("Roles Left: %3d\n", roll);

	int choice = 0;

	while (roll != 0) {
		choice = 0;

		//print options
		printMenuOp("1", "hold dice");
		printMenuOp("2", "bank score");
		printMenuOp("3", "Roll again");
		while (choice != 3 && choice != 2) {

			scanf("%d", &choice);

			switch (choice) {
			case 1:
				//hold dice menu
				holdDice(&dice, &heldDice, 5);

				//print options
				system("cls");
				printScorePreview(newScore, currentPlayer);
				printDice(dice,heldDice);
				printf("Current Player: %3d\n", currentPlayer);
				printf("Roles Left: %3d\n", roll);
				printMenuOp("1", "hold dice");
				printMenuOp("2", "bank score");
				printMenuOp("3", "Roll again");
				break;
			case 2:
				//exit loops
				roll = 1;
				choice = 2;
				break;
			case 3:
				//roll again
				break;
			default:
				break;
			}
		}

		//deccrement roll'
		roll -= 1;

		//reroll if chosen
		if (choice == 3) {
			//reroll dice
			rollDice(dice, heldDice, 5);

			//reprint score preview
			system("cls");
			newScore = calcPreview(newScore, dice, currentPlayer);
			printScorePreview(newScore, currentPlayer);
			printDice(dice, heldDice);
			printf("Current Player: %3d\n", currentPlayer);
			printf("Roles Left: %3d\n", roll);

		}

		

	}
	//bank score menu
	newScore = bankScore(newScore, currentPlayer, &dice, &heldDice);


	return newScore;

}

//GameLoop
void gameLoop() {

	//player scorecards
	struct scoreCard players = initScoreCard();

	//track current player
	int currentPlayer = (rand() % 2) + 1;

	//gameplay menu
	system("cls");
	printScoreCard(players);
	printf("player %d turn\n", currentPlayer);
	printMenuOp("1", "Roll");
	printMenuOp("2", "Exit to Menu");

	int choice = 0;

	while (choice != 2) {
		choice = 0;

		scanf("%d", &choice);

		switch (choice) {
		case 1:
			//begin turn
			players = playerTurn(players, currentPlayer);
			//switch player
			if (players.p1finished == 1 && players.p2finished == 0) {
				currentPlayer = 2;
				system("cls");
				printScoreCard(players);
				printf("player %d turn\n", currentPlayer);
				printMenuOp("1", "Roll");
				printMenuOp("2", "Exit to Menu");
			}
			else if (players.p2finished == 1 && players.p1finished == 0) {
				currentPlayer = 1;
				system("cls");
				printScoreCard(players);
				printf("player %d turn\n", currentPlayer);
				printMenuOp("1", "Roll");
				printMenuOp("2", "Exit to Menu");
			}
			else if (players.p1finished == 1 && players.p2finished == 1) {
				//winner menu
				checkWinner(players);

				//exit
				choice = 2;
			}
			else {
				currentPlayer = switchPlayer(currentPlayer);

				system("cls");
				printScoreCard(players);
				printf("player %d turn\n", currentPlayer);
				printMenuOp("1", "Roll");
				printMenuOp("2", "Exit to Menu");
			}

			break;
			
		case 2:
			//exit
			break;
		default:
			break;
		}



	}
	
}
