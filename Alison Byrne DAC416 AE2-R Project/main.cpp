#include<iostream>
#include<random>
#include<ctime>
#include "Board.h"

int main()
{
	int score = 0;
	// Initial game setup
	srand(time(0));
	GameBoard board;
	board.generateBoard();
	board.displayBoard();

	// User inputs their move 
	board.getInput();
	// Movement function is called inside input function so that parameters can be passed in directly instead of returning multiple values to main()

	board.displayBoard();
	std::cout << "Current score: " << score << std::endl;
}