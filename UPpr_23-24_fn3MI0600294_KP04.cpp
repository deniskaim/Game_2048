/**
*
* Solution to course project # 4
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Denis Kaim
* @idnumber 3MI0600294
* @compiler Visual Studio
*
* <Game 2048>
*
*/


#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>

const int NAME_SIZE = 101;
const int MAX_PLAYERS = 5;
using namespace std;
void clearCin()
{
	cin.clear();
	cin.ignore(INT_MAX, '\n');
}
void nicknameInput(char* nickname)
{
	if (!nickname)
		return;
	
	cout << "Enter your nickname: ";
	clearCin();
	cin.getline(nickname, NAME_SIZE);
}
int gridSizeInput()
{
	const int MIN_SIZE = 4, MAX_SIZE = 10;
	int gridSize;

	cout << endl;
	cout << "Enter dimension: ";

	do
	{
		cin >> gridSize;

		if (gridSize >= MIN_SIZE && gridSize <= MAX_SIZE)
			return gridSize;
		else
		{
			cout << "Please, enter an appropriate size for the grid! It should be between " << MIN_SIZE << " and " << MAX_SIZE << "." << endl;
			clearCin();
		}
	} while (true);

}
char commandInput()
{
	char command;
	bool isValidInput = false;

	cout << "Enter direction: ";
	do
	{
		cin >> command;
		isValidInput = (cin.peek() == '\n');
		clearCin();

		if (isValidInput && (command == 'w' || command == 'a' || command == 's' || command == 'd'))
		{
			return command;
		}
		else
			cout << "Choose one of the following: 'w', 'a', 's', 'd' ." << endl;
		

	} while (!isValidInput);
}

void getFilenameForGridSize(char* filename, int gridSize)
{
	// This function creates a filename specific to the grid size. 
	if (!filename)
		return;

	snprintf(filename, NAME_SIZE, "leaderboard_%dx%d.txt", gridSize, gridSize);
}
void writeResultsToLeaderboardFile(char* filename, char** nicknames, const int* scores, int numPlayers)
{
	// This function writes the nicknames and scores in the specific file in a descending order.

	if (!filename || !nicknames || !scores)
		return;

	ofstream MyFile(filename);
	if (!MyFile.is_open())
		return;

	for (int i = 0; i < numPlayers; i++)
	{
		MyFile << nicknames[i] << endl; 
		MyFile << scores[i] << endl;
	}
	MyFile.close();
}
void readLeaderboardFromFile(int gridSize)
{
	char filename[NAME_SIZE];
	getFilenameForGridSize(filename, gridSize);

	ifstream MyFile(filename);
	if (!MyFile.is_open())
	{
		cout << "The file is empty! No players yet!" << endl;
		cout << endl;
		return;
	}
	char nickname[NAME_SIZE];
	int score;
	int maxLength = 0;
	
	// With the maxLength variable we will be able to align the nicknames and scores perfectly in two columns
	while (MyFile.getline(nickname, NAME_SIZE) && MyFile >> score)
	{
		int length = strlen(nickname);
		if (length > maxLength)
			maxLength = length;

		MyFile.ignore(INT_MAX, '\n');

	}
	MyFile.clear();   
	MyFile.seekg(0);

	int place = 1;

	cout << endl;
	cout << "Leaderboard for " << gridSize << " x " << gridSize << " board:" << endl;
	while (MyFile.getline(nickname, NAME_SIZE) && MyFile >> score)
	{
		cout << place++ << ". " << left << setw(maxLength + 1) << nickname << score << endl;
		MyFile.ignore(INT_MAX, '\n');
	}
	MyFile.close();
	cout << endl;
}
void insertAndSort(char** nicknames, int* scores,  char* nicknamePlayer, int scorePlayer, int& numPlayers)
{
	// This function inserts the player's nickname and score in the array and sorts it in a descending order.
	if (!nicknames || !scores || !nicknamePlayer)
		return;


	int position = numPlayers;

	for (int i = 0; i < numPlayers; i++)
	{
		if (scorePlayer > scores[i])
		{
			position = i;
			break;
		}
	}
	if (position == MAX_PLAYERS)
		return;

	for (int i = numPlayers; i > position; i--)
	{
		if (i == MAX_PLAYERS)
			continue;

		strcpy_s(nicknames[i], NAME_SIZE,nicknames[i - 1]);
		scores[i] = scores[i - 1];
	}
	strcpy_s(nicknames[position], NAME_SIZE, nicknamePlayer);
	scores[position] = scorePlayer;

	if (numPlayers < MAX_PLAYERS)
		numPlayers++;
}
void initializeIntArray(int* scores)
{
	if (!scores)
		return;

	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		scores[i] = 0;
	}
}
void initializeCharArray(char** nicknames)
{
	if (!nicknames)
		return;

	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		nicknames[i][0] = '\0'; 
	}
}
void updateLeaderboard(int gridSize, char* nicknamePlayer, int scorePlayer)
{
	if (!nicknamePlayer)
		return;

	char filename[NAME_SIZE];
	getFilenameForGridSize(filename, gridSize);

	char nicknames[MAX_PLAYERS][NAME_SIZE];
	char* nicknamesPtr[MAX_PLAYERS];
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		nicknamesPtr[i] = nicknames[i];
	}
	int scores[MAX_PLAYERS];
	initializeIntArray(scores);
	initializeCharArray(nicknamesPtr);

	int numPlayers = 0;

	ifstream MyFile(filename);
	if (!MyFile.is_open())
	{
		insertAndSort(nicknamesPtr, scores, nicknamePlayer, scorePlayer, numPlayers);
		writeResultsToLeaderboardFile(filename, nicknamesPtr, scores, numPlayers);
		return;
	}

	char currentNickname[NAME_SIZE];
	int currentScore;

	while (MyFile.getline(currentNickname, NAME_SIZE) && MyFile >> currentScore && numPlayers < MAX_PLAYERS)
	{
		strcpy_s(nicknames[numPlayers],NAME_SIZE,currentNickname);
		scores[numPlayers] = currentScore;
		numPlayers++;

		MyFile.ignore(INT_MAX, '\n');

	}
	MyFile.close();
	insertAndSort(nicknamesPtr, scores, nicknamePlayer, scorePlayer, numPlayers);
	writeResultsToLeaderboardFile(filename, nicknamesPtr, scores, numPlayers);
}


int** createBoard(int gridSize)
{
	int** board = new int* [gridSize];
	for (int i = 0; i < gridSize; i++)
	{
		board[i] = new int[gridSize];
		for (int j = 0; j < gridSize; j++)
		{
			board[i][j] = 0;
		}
	}
	return board;
}
void deleteBoard(int** board, int gridSize)
{
	if (!board)
		return;

	for (int i = 0; i < gridSize; i++)
	{
		delete[] board[i];
	}
	delete[] board;
}
bool** createBoolMatrix(int gridSize)
{
	bool** mtx= new bool* [gridSize];
	for (int i = 0; i < gridSize; i++)
	{
		mtx[i] = new bool[gridSize];
		for (int j = 0; j < gridSize; j++)
		{
			mtx[i][j] = false;
		}
	}
	return mtx;
}
void deleteBoolMatrix(bool** mtx, int gridSize)
{
	if (!mtx)
		return;

	for (int i = 0; i < gridSize; i++)
	{
		delete[] mtx[i];
	}
	delete[] mtx;
}

int calculateScore(int** board, int gridSize)
{
	if (!board)
		return 0;

	int score = 0;
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			score += board[i][j];
		}
	}
	return score;
}
void printBoardAndScore(int** board, int gridSize, int score)
{
	if (!board)
		return;

	cout << endl;

	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			cout << setw(5) << board[i][j];
		}
		cout << endl;
		cout << endl;
	}
	cout << "Score: " << score << endl;
	cout << endl;
}

void moveTileUpInColumn(int** board, int gridSize, int row, int column, bool& isSuccessfulCommand, bool** isUsed)
{
	if (!board || !isUsed)
		return;

	int i = row;

	while (i - 1 >= 0 && board[i - 1][column] == 0)
	{
		i--;
	}
	// if the tile above has the same value and it is allowed to make a combination in that cell, combine them
	if (i - 1 >= 0 && board[i - 1][column] == board[row][column] && !isUsed[i - 1][column])
	{
		board[i - 1][column] *= 2;
		board[row][column] = 0;
		isSuccessfulCommand = true;
		isUsed[i - 1][column] = true;
		return;
	}

	if (i == row)
		return;

	board[i][column] = board[row][column];
	board[row][column] = 0;
	isSuccessfulCommand = true;
}
void moveTilesUp(int** board, int gridSize, bool& isSuccessfulCommand, bool** isUsed)
{
	if (!board || !isUsed)
		return;

	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			if (board[i][j] != 0)
				moveTileUpInColumn(board, gridSize, i, j, isSuccessfulCommand, isUsed);
		}
	}
}

void moveTileLeftInRow(int** board, int gridSize, int row, int column, bool& isSuccessfulCommand, bool** isUsed)
{
	if (!board || !isUsed)
		return;

	int j = column;

	while (j - 1 >= 0 && board[row][j - 1] == 0)
	{
		j--;
	}
	// if the tile on the left has the same value and it is allowed to make a combination in that cell, combine them
	if (j - 1 >= 0 && board[row][j - 1] == board[row][column] && !isUsed[row][j - 1])
	{
		board[row][j - 1] *= 2;
		board[row][column] = 0;
		isSuccessfulCommand = true;
		isUsed[row][j - 1] = true;
		return;
	}

	if (j == column)
		return;

	board[row][j] = board[row][column];
	board[row][column] = 0;
	isSuccessfulCommand = true;
}
void moveTilesLeft(int** board, int gridSize, bool& isSuccessfulCommand, bool** isUsed)
{
	if (!board || !isUsed)
		return;

	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			if (board[i][j] != 0)
				moveTileLeftInRow(board, gridSize, i, j, isSuccessfulCommand, isUsed);
		}
	}
}

void moveTileDownInColumn(int** board, int gridSize, int row, int column, bool& isSuccessfulCommand, bool** isUsed)
{
	if (!board || !isUsed)
		return;

	int i = row;

	while (i + 1 < gridSize && board[i + 1][column] == 0)
	{
		i++;
	}
	// if the tile beneath has the same value and it is allowed to make a combination in that cell, combine them
	if (i + 1 < gridSize && board[i + 1][column] == board[row][column] && !isUsed[i + 1][column])
	{
		board[i + 1][column] *= 2;
		board[row][column] = 0;
		isSuccessfulCommand = true;
		isUsed[i + 1][column] = true;
		return;
	}

	if (i == row)
		return;

	board[i][column] = board[row][column];
	board[row][column] = 0;
	isSuccessfulCommand = true;
}
void moveTilesDown(int** board, int gridSize, bool& isSuccessfulCommand, bool** isUsed)
{
	if (!board || !isUsed)
		return;

	for (int i = gridSize - 1; i >= 0; i--)
	{
		for (int j = 0; j < gridSize; j++)
		{
			if (board[i][j] != 0)
				moveTileDownInColumn(board, gridSize, i, j, isSuccessfulCommand, isUsed);
		}
	}
}

void moveTileRightInRow(int** board, int gridSize, int row, int column, bool& isSuccessfulCommand, bool** isUsed)
{
	if (!board || !isUsed)
		return;

	int j = column;

	while (j + 1 < gridSize && board[row][j + 1] == 0)
	{
		j++;
	}
	// if the tile on the right has the same value and it is allowed to make a combination in that cell, combine them
	if (j + 1 < gridSize && board[row][j + 1] == board[row][column] && !isUsed[row][j + 1])
	{
		board[row][j + 1] *= 2;
		board[row][column] = 0;
		isSuccessfulCommand = true;
		isUsed[row][j + 1] = true;
		return;
	}

	if (j == column)
		return;

	board[row][j] = board[row][column];
	board[row][column] = 0;
	isSuccessfulCommand = true;
}
void moveTilesRight(int** board, int gridSize, bool& isSuccessfulCommand, bool** isUsed)
{
	if (!board || !isUsed)
		return;

	for (int i = 0; i < gridSize; i++)
	{
		for (int j = gridSize - 1; j >= 0 ; j--)
		{
			if (board[i][j] != 0)
				moveTileRightInRow(board, gridSize, i, j, isSuccessfulCommand, isUsed);
		}
	}
}

void moveTiles(int** board, int gridSize, char command, bool& isSuccesfulCommand)
{
	if (!board)
		return;
	
	bool** isUsed = createBoolMatrix(gridSize); 
	/* 
	* With the bool matrix we will check whether there has been a combination of two equal adjacent numbers, 
	* so we can know whether it is allowed to make another combination in the same cell.
	*/
	
	if (command == 'w')
		moveTilesUp(board, gridSize, isSuccesfulCommand, isUsed);

	else if (command == 'a')
		moveTilesLeft(board, gridSize, isSuccesfulCommand, isUsed);

	else if (command == 's')
		moveTilesDown(board, gridSize, isSuccesfulCommand, isUsed);

	else if (command == 'd')
		moveTilesRight(board, gridSize, isSuccesfulCommand, isUsed);

	deleteBoolMatrix(isUsed, gridSize);
}

bool contains2048(int** board, int gridSize)
{
	if (!board)
		return false;

	const int WINNING_NUMBER = 2048;

	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			if (board[i][j] == WINNING_NUMBER)
				return true;
		}
	}
	return false;
}
bool areCoordinates(int row, int col, int gridSize)
{
	return ((row >= 0 && row < gridSize) && (col >= 0 && col < gridSize));
}
bool equalAdjacentElements(int** board, int gridSize, int row, int col)
{
	if (!board)
		return false;

	if (areCoordinates(row - 1, col, gridSize) && board[row - 1][col] == board[row][col] ||
		areCoordinates(row + 1, col, gridSize) && board[row + 1][col] == board[row][col] ||
		areCoordinates(row, col - 1, gridSize) && board[row][col - 1] == board[row][col] ||
		areCoordinates(row, col + 1, gridSize) && board[row][col + 1] == board[row][col])
		return true;

	return false;


}
bool availableMoves(int** board, int gridSize)
{
	if (!board)
		return false;

	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			if (board[i][j] == 0 || equalAdjacentElements(board, gridSize, i, j))
				return true;
		}
	}
	return false;
}
void printWinMessage(int score)
{
	cout << "Congrats, you have won !!! :)" << endl;
	cout << "Your score is: " << score << endl;
	cout << endl;
}
void printLossMessage(int score)
{
	cout << "You have run out of moves ! Game over !!!" << endl;
	cout << "Your score is: " << score << endl;
	cout << endl;
}
void printEndGameMessage(int score, bool isWinner)
{
	if (isWinner)
		printWinMessage(score);

	else
		printLossMessage(score);
}
bool isGameOver(int** board, int gridSize, int score, bool& isWinner)
{
	if (!board)
		return false;

	/*
	The game is over if we have managed to get the number 2048 or we can't move in any direction.
	*/
	isWinner = contains2048(board, gridSize);
	return isWinner || !availableMoves(board, gridSize);
} 

void addRandomTile(int** board, int gridSize)
{
	if (!board)
		return;

	srand(time(NULL));
	int row, column;
	do
	{
		row = rand() % gridSize;
		column = rand() % gridSize;
	} while (board[row][column] != 0);


	int value = (rand() % 2 + 1) * 2; // That way we can get either 2 or 4 as a random tile.
	board[row][column] = value;
}
void beginGame(int** board, int gridSize, char* nickname)
{
	if (!board || !nickname)
		return;
	

	char command;
	addRandomTile(board, gridSize);
	addRandomTile(board, gridSize);

	int score = calculateScore(board, gridSize);
	printBoardAndScore(board, gridSize, score);

	clearCin();
	bool isWinner = false;
	while (!isGameOver(board, gridSize, score, isWinner))
	{
		command = commandInput();

		bool isSuccesfulCommand = false;
		moveTiles(board, gridSize, command, isSuccesfulCommand);

		if (isSuccesfulCommand == false)
		{
			cout << "Please, enter a new direction, the one you chose is not possible!" << endl;
			cout << endl;
			continue;
		}
		addRandomTile(board, gridSize);
		score = calculateScore(board, gridSize);
		printBoardAndScore(board, gridSize, score);
	}
	printEndGameMessage(score, isWinner);
	updateLeaderboard(gridSize,nickname, score);
	
}
void consoleMenu()
{
	int gridSize;
	char nickname[NAME_SIZE];
	bool showMenu = true;
	int choice;

	cout << "Welcome to the game 2048!" << endl;
	while(true)
	{
		if (showMenu)
		{
			cout << "Select '1' to play, '2' to see the Leaderboard or '3' to quit!" << endl;
			cout << "1. Start game\n2. Leaderboard\n3. Quit" << endl;
		}
		cin >> choice;
		if (choice == 1)
		{
			nicknameInput(nickname);
			gridSize = gridSizeInput();
			int** board = createBoard(gridSize);

			beginGame(board, gridSize, nickname);
			deleteBoard(board, gridSize);
			showMenu = true;

		}
		else if (choice == 2)
		{
			gridSize = gridSizeInput();
			readLeaderboardFromFile(gridSize);
			showMenu = true;
		}
		else if (choice == 3)
		{
			cout << "Hope to see you back soon!" << endl;
			break;
		}
		else
		{
			cout << "Please, try again. That's not a possible option" << endl;
			showMenu = false;
			clearCin();
		}
	} 
}
int main()
{
	consoleMenu();
}
