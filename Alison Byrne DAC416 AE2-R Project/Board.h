#pragma once
class GameBoard
{
	// These values will be used to handle the scoring system
	const int threeStringScore = 50, fourStringScore = 100, fiveStringScore = 500, tShapeMultiplier = 3, cascadeScore = 50, cascadeMultiplier = 2;

	// These values will be used for the game board
	const int boardSize = 8;
	int axis[8] = { 0,1,2,3,4,5,6,7 };
	char boardArray[8][8];

	enum colours
	{
		Blue,
		Green,
		Purple,
		Red,
		White,
		Yellow
	};

	enum directionsMenu
	{
		Cancel,
		Up,
		Down,
		Left,
		Right
	};

public:
	char generatePiece();
	void generateBoard();
	void displayBoard();
	void getInput();
	void movePiece(int xPosition, int yPosition, int direction);
	int checkBoard(int movedX, int movedY, int returnDirection);
	int checkPiece(int position1, int position2);
	void replacePiece(int xPosition, int yPosition);
};