#include "animation.h"

//print menu option
void printMenuOp(char* number, char* option) {
	printf("(%s) %s\n", number, option);
}

void printScoreCard(struct scoreCard score) {

	printf("\n");
	printf("#-------player-1---player-2------#-----------------player-1---player-2------#\n");
	printf("| Ones    %3d         %3d        |Three of a kind     %3d         %3d       |\n", score.p1Score[0], score.p2Score[0], score.p1Score[8], score.p2Score[8]);
	printf("| Twos	  %3d         %3d        | Four of a kind     %3d         %3d       |\n", score.p1Score[1], score.p2Score[1], score.p1Score[9], score.p2Score[9]);
	printf("| Three   %3d         %3d        |  Full House        %3d         %3d       |\n", score.p1Score[2], score.p2Score[2], score.p1Score[10], score.p2Score[10]);
	printf("| Fours   %3d         %3d        | Small Straight     %3d         %3d       |\n", score.p1Score[3], score.p2Score[3], score.p1Score[11], score.p2Score[11]);
	printf("| Fives   %3d         %3d        | Large Straight     %3d         %3d       |\n", score.p1Score[4], score.p2Score[4], score.p1Score[12], score.p2Score[12]);
	printf("| sixes   %3d         %3d        |    Chance          %3d         %3d       |\n", score.p1Score[5], score.p2Score[5], score.p1Score[13], score.p2Score[13]);
	printf("| Bonus   %3d         %3d        |    YAHTZEE         %3d         %3d       |\n", score.p1Score[6], score.p2Score[6], score.p1Score[14], score.p2Score[14]);
	printf("| Sum     %3d         %3d        |    Total           %3d         %3d       |\n", score.p1Score[7], score.p2Score[7], score.p1Score[15], score.p2Score[15]);
	printf("#--------------------------------#------------------------------------------#\n");
	printf("\n");

}


// print the score preview
void printScorePreview(struct scoreCard score, int currentPlayer) {

	if (currentPlayer == 1) {
		printf("\n");
		printf("#-------player-1---player-2------#-----------------player-1---player-2------#\n");
		printf("| Ones   *%3d         %3d        |Three of a kind    *%3d         %3d       |\n", score.p1Preview[0], score.p2Score[0], score.p1Preview[8], score.p2Score[8]);
		printf("| Twos	 *%3d         %3d        | Four of a kind    *%3d         %3d       |\n", score.p1Preview[1], score.p2Score[1], score.p1Preview[9], score.p2Score[9]);
		printf("| Three  *%3d         %3d        |  Full House       *%3d         %3d       |\n", score.p1Preview[2], score.p2Score[2], score.p1Preview[10], score.p2Score[10]);
		printf("| Fours  *%3d         %3d        | Small Straight    *%3d         %3d       |\n", score.p1Preview[3], score.p2Score[3], score.p1Preview[11], score.p2Score[11]);
		printf("| Fives  *%3d         %3d        | Large Straight    *%3d         %3d       |\n", score.p1Preview[4], score.p2Score[4], score.p1Preview[12], score.p2Score[12]);
		printf("| sixes  *%3d         %3d        |    Chance         *%3d         %3d       |\n", score.p1Preview[5], score.p2Score[5], score.p1Preview[13], score.p2Score[13]);
		printf("| Bonus  *%3d         %3d        |    YAHTZEE        *%3d         %3d       |\n", score.p1Preview[6], score.p2Score[6], score.p1Preview[14], score.p2Score[14]);
		printf("| Sum    *%3d         %3d        |    Total          *%3d         %3d       |\n", score.p1Preview[7], score.p2Score[7], score.p1Preview[15], score.p2Score[15]);
		printf("#--------------------------------#------------------------------------------#\n");
		printf("\n");

	}
	else {
		printf("\n");
		printf("#-------player-1---player-2------#-----------------player-1---player-2------#\n");
		printf("| Ones    %3d        *%3d        |Three of a kind     %3d        *%3d       |\n", score.p1Score[0], score.p2Preview[0], score.p1Score[8], score.p2Preview[8]);
		printf("| Twos	  %3d        *%3d        | Four of a kind     %3d        *%3d       |\n", score.p1Score[1], score.p2Preview[1], score.p1Score[9], score.p2Preview[9]);
		printf("| Three   %3d        *%3d        |  Full House        %3d        *%3d       |\n", score.p1Score[2], score.p2Preview[2], score.p1Score[10], score.p2Preview[10]);
		printf("| Fours   %3d        *%3d        | Small Straight     %3d        *%3d       |\n", score.p1Score[3], score.p2Preview[3], score.p1Score[11], score.p2Preview[11]);
		printf("| Fives   %3d        *%3d        | Large Straight     %3d        *%3d       |\n", score.p1Score[4], score.p2Preview[4], score.p1Score[12], score.p2Preview[12]);
		printf("| sixes   %3d        *%3d        |    Chance          %3d        *%3d       |\n", score.p1Score[5], score.p2Preview[5], score.p1Score[13], score.p2Preview[13]);
		printf("| Bonus   %3d        *%3d        |    YAHTZEE         %3d        *%3d       |\n", score.p1Score[6], score.p2Preview[6], score.p1Score[14], score.p2Preview[14]);
		printf("| Sum     %3d        *%3d        |    Total           %3d        *%3d       |\n", score.p1Score[7], score.p2Preview[7], score.p1Score[15], score.p2Preview[15]);
		printf("#--------------------------------#------------------------------------------#\n");
		printf("\n");

	}

	

}

void printDice(int* diceArr, int* heldDiceArr) {

	printf("#----------Current Roll-----------------#--------------Held Dice------------------#\n");
	printf("#-----#	#-----#	#-----#	#-----#	#-----# | #-----# #-----# #-----# #-----# #-----#\n");
	printf("|%3d  | |%3d  | |%3d  | |%3d  | |%3d  | | |%3d  | |%3d  | |%3d  | |%3d  | |%3d  |\n", diceArr[0], diceArr[1], diceArr[2], diceArr[3], diceArr[4], heldDiceArr[0], heldDiceArr[1], heldDiceArr[2], heldDiceArr[3], heldDiceArr[4]);
	printf("#-----# #-----# #-----# #-----#	#-----# # #-----# #-----# #-----# #-----# #-----#\n");
	printf("\n");
}

//print Yahtzee title animation
void printYahtTitle() {
	printf("\n");
	printf("  ____	\n");
	printf(" /\\' .\\    _____  __     __     _    _ _______ ____________ ______ \n");
	printf("/: \\___\\  / .  /\\ \\ \\   / //\\  | |  | |__   __|___  /  ____|  ____|\n");
	printf("\\' / . / /____/..\\\\\\ \\_/ //  \\ | |__| |  | |     / /| |__  | |\n");
	printf(" \\/___/  \\'  '\\  /  \\   // /\\ \\|  __  |  | |    / / |  __| |  __| \n");
	printf("          \\'__'\\/    | |/ ____ \\ |  | |  | |   / /__| |____| |___\n");
	printf("                     |_/_/    \\ _|  |_|  |_|  /_____|______|______|\n");
}

//print game rules
void printRules() {
	printYahtTitle();
	printf("\n");
	printf("The objective of YAHTZEE is to get as many points as possible by rolling five dice\n");
	printf("and getting certain combinations of dice. \n");
	printf("\n");
	printf("In each turn a player may throw the dice up to three times. A player doesn't have to roll \n");
	printf("all five dice on the second and third throw of a round, he may put as many dice as he\n");
	printf("wants to the side and only throw the ones that don't have the numbers he's trying to\n");
	printf("get. For example, a player throws and gets 1,3,3,4,6. He decides he want to try for the\n");
	printf("large straight, 1,2,3,4,5. So, he puts 1,3,4 to the side and only throws 3 and 6 again,\n");
	printf("hoping to get 2 and 5. \n");
	printf("\n");
	printf("In this game you select the dice you want to keep. They will be moved down and will\n");
	printf("not be thrown the next time you select 'Roll' option. If you decide after the\n");
	printf("second throw in a turn that you don't want to keep the same dice before the third throw\n");
	printf("then you can select them again and they will move back to the table and be thrown in the\n");
	printf("third throw.\n");
	printf("\n");
	printf("Upper section combinations\n");
	printf("\n");
	printf("Ones: Get as many ones as possible.\n");
	printf("Twos: Get as many twos as possible.\n");
	printf("Threes: Get as many threes as possible.\n");
	printf("Fours: Get as many fours as possible.\n");
	printf("Sixes: Get as many sixes as possible.\n");
	printf("\n");
	printf("For the six combinations above the score for each of them is the sum of dice of the\n");
	printf("right kind. E.g. if you get 1,3,3,3,5 and you choose Threes you will get 3*3 = 9 points\n");
	printf("The sum of all the above combinations is calculated and if it is 63 or more, the player \n");
	printf("will get a bonus of 35 points. On average a player needs three of each to reach 63, but \n");
	printf("it is not required to get three of each exactly, it is perfectly OK to have five sixes, and \n");
	printf("zero ones for example, as long as the sum is 63 or more the bonus will be awarded. \n");
	printf("\n");
	printf("Lower section combinations\n");
	printf("\n");
	printf("Three of a kind: Get three dice with the same number. Points are the sum all \n");
	printf("dice (not just the three of a kind).\n");
	printf("Four of a kind: Get four dice with the same number. Points are the sum all dice\n");
	printf("(not just the four of a kind).\n");
	printf("Full house: Get three of a kind and a pair, e.g. 1,1,3,3,3 or 3,3,3,6,6. Scores 25\n");
	printf("points.\n");
	printf("Small straight: Get four sequential dice, 1,2,3,4 or 2,3,4,5 or 3,4,5,6. Scores \n");
	printf("30 points.\n");
	printf("Large straight: Get five sequential dice, 1,2,3,4,5 or 2,3,4,5,6. Scores 40 \n");
	printf("points.\n");
	printf("Chance: You can put anything into chance, it's basically like a garbage can \n");
	printf("when you don't have anything else you can use the dice for. The score is simply\n");
	printf("the sum of the dice.\n");
	printf("YAHTZEE: Five of a kind. Scores 50 points.\n");
}