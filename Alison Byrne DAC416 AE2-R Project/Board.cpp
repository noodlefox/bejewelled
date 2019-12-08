#include<iostream>
#include<random>
#include<Windows.h>
#include "Board.h"

char GameBoard::generatePiece()
{
	// This generates a specific piece to use for the generateBoard function
	int piece = rand() % 6;
	switch (piece)
	{
	case Blue:
		return 'B';
	case Green:
		return 'G';
	case Purple:
		return 'P';
	case Red:
		return 'R';
	case White:
		return 'W';
	case Yellow:
		return 'Y';
	}
}

void GameBoard::generateBoard()
{
	// This generates the initial game board array at the start of the game
	for (int y = 0; y < boardSize; y++)
	{
		for (int x = 0; x < boardSize; x++)
		{
			do
			{
				boardArray[x][y] = generatePiece();
			} while ((boardArray[x][y] == boardArray[x - 1][y] && boardArray[x][y] == boardArray[x - 2][y]) || (boardArray[x][y] == boardArray[x][y - 1] && boardArray[x][y] == boardArray[x][y - 2]));
			// This loop will ensure that the board contains no 3 string matches when generated
		}
	}
}

void GameBoard::displayBoard()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// This displays the x co-ordinates of the game board on the top line
	std::cout << "  ";
	for (int i = 0; i < boardSize; i++)
	{
		std::cout << axis[i] << " ";
	}
	std::cout << std::endl;

	for (int y = 0; y < boardSize; y++)
	{
		// This displays the y co-ordinates of the game board on the left side
		SetConsoleTextAttribute(hConsole, 7);
		std::cout << axis[y] << " ";
		
		// This loop displays the appropriate character in the appropriate colour for the game piece in the array at that location
		for (int x = 0; x < boardSize; x++)
		{
			switch (boardArray[x][y])
			{
			case 'B':
				SetConsoleTextAttribute(hConsole, 1);
				std::cout << "B ";
				break;
			case 'G':
				SetConsoleTextAttribute(hConsole, 2);
				std::cout << "G ";
				break;
			case 'P':
				SetConsoleTextAttribute(hConsole, 5);
				std::cout << "P ";
				break;
			case 'R':
				SetConsoleTextAttribute(hConsole, 4);
				std::cout << "R ";
				break;
			case 'Y':
				SetConsoleTextAttribute(hConsole, 6);
				std::cout << "Y ";
				break;
			case 'W':
				SetConsoleTextAttribute(hConsole, 15);
				std::cout << "W ";
				break;
			default:
				std::cout << "Error";
			}
		}
		SetConsoleTextAttribute(hConsole, 7);
		std::cout << std::endl;
	}
}

void GameBoard::getInput()
{
	int xChoice = 0, yChoice = 0, directionChoice = 0, returnDirection = 0, movedPieceX = 0, movedPieceY = 0;
	std::cout << "\nEnter the x co-ordinate of the piece you want to move, then enter the y co-ordinate:\n";
	std::cin >> xChoice;
	std::cin >> yChoice;

	while (xChoice < 0 || xChoice > boardSize || yChoice < 0 || yChoice > boardSize)
	{
		std::cout << "\nInvalid co-ordinates, please enter again:\n";
		std::cin >> xChoice;
		std::cin >> yChoice;
	}
	// Loop for validating the co-ordinate input

	std::cout << "\nChoose a direction to move the piece at (" << xChoice << ", " << yChoice << "):\n\n1. Up\n2. Down\n3. Left\n4. Right\n\nPress 0 to cancel and select another piece.\n";
	std::cin >> directionChoice;

	while (directionChoice < Cancel || directionChoice > Right)
	{
		std::cout << "Invalid choice, please enter again:\n";
		std::cin >> directionChoice;
	}
	while ((xChoice == 0 && directionChoice == Left) || (xChoice == boardSize && directionChoice == Right) || (yChoice == 0 && directionChoice == Up) || (yChoice == boardSize && directionChoice == Down))
	{
		std::cout << "\nThis piece cannot move in that direction, please choose a different direction:\n";
	}
	// Loops for validating the direction input

	// This is so that the piece can easily be swapped back if no match is made by the move
	movedPieceX = xChoice;
	movedPieceY = yChoice;
	switch (directionChoice)
	{
	case Up:
		returnDirection = Down;
		movedPieceY = yChoice - 1;
		break;
	case Down:
		returnDirection = Up;
		movedPieceY = yChoice + 1;
		break;
	case Left:
		returnDirection = Right;
		movedPieceX = xChoice - 1;
		break;
	case Right:
		returnDirection = Left;
		movedPieceX = xChoice + 1;
		break;
	default:
		std::cout << "There was an error with return direction.\n";
	}
	std::cout << std::endl;

	// Piece movement called directly from this function to avoid breaking input down into three seperate functions and returning the inputs to main()
	movePiece(xChoice, yChoice, directionChoice);
	checkBoard(movedPieceX, movedPieceY, returnDirection);
}

void GameBoard::movePiece(int xPosition, int yPosition, int direction)
{
	// Temporary variable to hold the character being swapped
	char swappedPiece = ' ';

	switch (direction)
	{
	case Up:
		swappedPiece = boardArray[xPosition][yPosition - 1];
		boardArray[xPosition][yPosition - 1] = boardArray[xPosition][yPosition];
		boardArray[xPosition][yPosition] = swappedPiece;
		break;
	case Down:
		swappedPiece = boardArray[xPosition][yPosition + 1];
		boardArray[xPosition][yPosition + 1] = boardArray[xPosition][yPosition];
		boardArray[xPosition][yPosition] = swappedPiece;
		break;
	case Left:
		swappedPiece = boardArray[xPosition - 1][yPosition];
		boardArray[xPosition - 1][yPosition] = boardArray[xPosition][yPosition];
		boardArray[xPosition][yPosition] = swappedPiece;
		break;
	case Right:
		swappedPiece = boardArray[xPosition + 1][yPosition];
		boardArray[xPosition + 1][yPosition] = boardArray[xPosition][yPosition];
		boardArray[xPosition][yPosition] = swappedPiece;
		break;
	case Cancel:
		// Runs input function again so the player can enter different co-ordinate values
		getInput();
		break;
	default:
		std::cout << "There was an error with piece movement.\n";
	}
}

int GameBoard::checkBoard(int movedX, int movedY, int returnDirection)
{
	int totalScoreBonus = 0;
	for (int y = 0; y < (boardSize - 2); y++)
	{
		for (int x = 0; x < (boardSize - 2); y++)
		{
			totalScoreBonus += checkPiece(x, y);
			totalScoreBonus += checkPiece(y, x);
		}
	}
	if (totalScoreBonus == 0)
	{
		movePiece(movedX, movedY, returnDirection);
		std::cout << "No match was made by this move, so the piece was returned to its original position.\n\n";
	}
	return totalScoreBonus;
}

int GameBoard::checkPiece(int position1, int position2)
{
	int scoreBonus = 0, cascadeCount = 0;
	do
	{
		if (boardArray[position1][position2] == boardArray[position1 + 1][position2] && boardArray[position1][position2] == boardArray[position1 + 2][position2])
		{
			//cascadeCount++;
			if (boardArray[position1][position2] == boardArray[position1 + 3][position2] && boardArray[position1][position2] == boardArray[position1 + 4][position2])
			{
				if (boardArray[position1 + 2][position2] == boardArray[position1 + 2][position2 + 1] && boardArray[position1][position2] == boardArray[position1 + 2][position2 + 2])
				{
					// 5 x 3 T-shape string
					scoreBonus += (fiveStringScore * tShapeMultiplier);
					std::cout << "+" << (fiveStringScore * tShapeMultiplier) << " points!\n";
					for (int i = position1; i < 4; i++)
					{
						replacePiece(i, position2);
					}
					for (int i = position2 + 1; i < 2; i++)
					{
						replacePiece(position1 + 2, i);
					}
				}
				else
				{
					// 5 string
					scoreBonus += fiveStringScore;
					std::cout << "+" << fiveStringScore << " points!\n";
					for (int i = position1; i < 4; i++)
					{
						replacePiece(i, position2);
					}
				}
			}
			else if (boardArray[position1][position2] == boardArray[position1 + 3][position2])
			{
				// 4 string
				scoreBonus += fourStringScore;
				std::cout << "+" << fourStringScore << " points!\n";
				for (int i = position1; i < 3; i++)
				{
					replacePiece(i, position2);
				}
			}
			else
			{
				if (boardArray[position1 + 1][position2] == boardArray[position1 + 1][position2 + 1] && boardArray[position1][position2] == boardArray[position1 + 1][position2 + 2])
				{
					// 3 x 3 T-shape string
					scoreBonus += (threeStringScore * tShapeMultiplier);
					std::cout << "+" << (threeStringScore * tShapeMultiplier) << " points!\n";
					for (int i = position1; i < 2; i++)
					{
						replacePiece(i, position2);
					}
					for (int i = position2 + 1; i < 2; i++)
					{
						replacePiece(position1 + 2, i);
					}
				}
				else
				{
					// 3 string
					scoreBonus += threeStringScore;
					std::cout << "+" << threeStringScore << " points!\n";
					for (int i = position1; i < 2; i++)
					{
						replacePiece(i, position2);
					}
				}
			}
			scoreBonus += (cascadeScore * (cascadeCount ^ cascadeMultiplier));
		}
		else
		{
			cascadeCount = 0;
		}
	} while (cascadeCount > 0);
	return scoreBonus;
}

void GameBoard::replacePiece(int xPosition, int yPosition)
{
	for (int i = yPosition; i < boardSize; i++)
	{
		if (i == boardSize)
		{
			boardArray[xPosition][i] = generatePiece();
		}
		else
		{
			boardArray[xPosition][i] = boardArray[xPosition][i + 1];
		}
	}
}