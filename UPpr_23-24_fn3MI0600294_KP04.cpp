#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>

const int NAME_SIZE = 100;
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
	if (!filename)
		return;

	snprintf(filename, NAME_SIZE, "leaderboard_%dx%d.txt", gridSize, gridSize);
}
void writeResultsToLeaderboardFile(char* filename, char** nicknames, const int* scores, int numPlayers)
{
	if (!filename || !nicknames || !scores)
		return;

	ofstream MyFile(filename);
	if (!MyFile.is_open())
		return;

	for (int i = 0; i < numPlayers; i++)
	{
		MyFile << nicknames[i] << " " << scores[i] << endl;
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
	const size_t LINE_SIZE = 110;
	char nickname[LINE_SIZE];
	int score;
	int maxLength = 0;
	
	while (MyFile >> nickname >> score)
	{
		int length = strlen(nickname);
		if (length > maxLength)
			maxLength = length;
	}
	MyFile.close();

	ifstream MyFile2(filename);
	cout << endl;
	cout << "Leaderboard for " << gridSize << " x " << gridSize << " board:" << endl;
	while (MyFile2 >> nickname >> score)
	{
		cout << left << setw(maxLength + 1) << nickname << score << endl;
	}
	MyFile2.close();
	cout << endl;
}
void insertAndSort(char* nicknames[], int* scores,  char* nicknamePlayer, int scorePlayer, int& numPlayers)
{
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
	for (int i = numPlayers; i > position; i--)
	{
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

	char currentNickname[NAME_SIZE];
	int currentScore;

	while (MyFile >> currentNickname >> currentScore && numPlayers < MAX_PLAYERS)
	{
		strcpy_s(nicknames[numPlayers],NAME_SIZE,currentNickname);
		scores[numPlayers] = currentScore;
		numPlayers++;
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

void moveTilesUpInColumn(int** board, int gridSize, int row, int column, bool& isSuccessfulCommand, bool** isUsed)
{
	if (!board || !isUsed)
		return;

	int i = row;

	while (i - 1 >= 0 && board[i - 1][column] == 0)
	{
		i--;
	}
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
				moveTilesUpInColumn(board, gridSize, i, j, isSuccessfulCommand, isUsed);
		}
	}
}

void moveTilesLeftInRow(int** board, int gridSize, int row, int column, bool& isSuccessfulCommand, bool** isUsed)
{
	if (!board || !isUsed)
		return;

	int j = column;

	while (j - 1 >= 0 && board[row][j - 1] == 0)
	{
		j--;
	}

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
				moveTilesLeftInRow(board, gridSize, i, j, isSuccessfulCommand, isUsed);
		}
	}
}

void moveTilesDownInColumn(int** board, int gridSize, int row, int column, bool& isSuccessfulCommand, bool** isUsed)
{
	if (!board || !isUsed)
		return;

	int i = row;

	while (i + 1 < gridSize && board[i + 1][column] == 0)
	{
		i++;
	}

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
				moveTilesDownInColumn(board, gridSize, i, j, isSuccessfulCommand, isUsed);
		}
	}
}

void moveTilesRightInRow(int** board, int gridSize, int row, int column, bool& isSuccessfulCommand, bool** isUsed)
{
	if (!board || !isUsed)
		return;

	int j = column;

	while (j + 1 < gridSize && board[row][j + 1] == 0)
	{
		j++;
	}

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
				moveTilesRightInRow(board, gridSize, i, j, isSuccessfulCommand, isUsed);
		}
	}
}

void moveTiles(int** board, int gridSize, char command, bool& isSuccesfulCommand)
{
	if (!board)
		return;
	
	bool** isUsed = createBoolMatrix(gridSize);
	
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

bool checkFor2048(int** board, int gridSize, int score)
{
	const int winningNumber = 2048;

	if (!board)
		return false;

	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			if (board[i][j] == winningNumber)
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

	if (areCoordinates(row - 1, col, gridSize) && board[row - 1][col] == board[row][col])
		return true;
	if (areCoordinates(row + 1, col, gridSize) && board[row + 1][col] == board[row][col])
		return true;
	if (areCoordinates(row, col - 1, gridSize) && board[row][col - 1] == board[row][col])
		return true;
	if (areCoordinates(row, col + 1, gridSize) && board[row][col + 1] == board[row][col])
		return true;

	return false;


}
bool availableMoves(int** board, int gridSize)
{
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
bool isGameOver(int** board, int gridSize, char* nickname, int score)
{
	/*
	The game is over if we have managed to get the number 2048 or we can't move in any direction.
	*/
	if (checkFor2048(board, gridSize, score) == true)
	{
		printWinMessage(score);
		return true;
	}
	if (!availableMoves(board, gridSize))
	{
		printLossMessage(score);
		return true;
	}

	return false;
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

	int value = (rand() % 2 + 1) * 2;
	board[row][column] = value;
}
void beginGame(int** board, int gridSize, char* nickname)
{
	if (!board)
		return;
	

	char command;
	addRandomTile(board, gridSize);
	addRandomTile(board, gridSize);

	int score = calculateScore(board, gridSize);
	printBoardAndScore(board, gridSize, score);

	clearCin();

	while (!isGameOver(board, gridSize, nickname, score))
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
	updateLeaderboard(gridSize,nickname, score);
	
}
void consoleMenu()
{
	unsigned gridSize;
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
