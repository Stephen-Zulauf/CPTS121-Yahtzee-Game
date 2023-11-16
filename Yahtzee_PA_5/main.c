
#include "yahtzee.h"
#include "animation.h"

int main() {

	//seed random
	srand(time(NULL));

	/*begin main menu*/
	int choice = 0;

	printYahtTitle();

	printMenuOp("1", "Print Rules");
	printMenuOp("2", "Start Game");
	printMenuOp("3", "Exit");

	while (choice != 3) {
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			//rules menu
			rulesLoop();

			//reprint main menu
			system("cls");
			printYahtTitle();

			printMenuOp("1", "Print Rules");
			printMenuOp("2", "Start Game");
			printMenuOp("3", "Exit");
			break;
		case 2:
			//start game loop
			gameLoop();
			system("cls");
			printYahtTitle();

			printMenuOp("1", "Print Rules");
			printMenuOp("2", "Start Game");
			printMenuOp("3", "Exit");
			break;
		case 3:
			//exit
			system("cls");
			printf("goodbye");
			break;
		}
	}

}