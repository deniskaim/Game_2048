#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;
void nicknameInput(char* nickname, const int NAMESIZE)
{
	if (!nickname)
		return;

	cout << "Enter your nickname: " << endl;
	do
	{
		cin.getline(nickname, NAMESIZE);
		if (!cin.fail())
			return;

		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "This username is too long. Choose another one!" << endl;
		/// Tuk shte e umestno da pravq proverka dali imeto veche e zaeto

	} while (true);

}
int gridSizeInput()
{
	unsigned gridSize;
	cout << "Enter dimension: " << endl;

	do
	{
		cin >> gridSize;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid input. Please enter a number." << endl;
		}
		else if (gridSize >= 4 && gridSize <= 10)
			return gridSize;
		else
			cout << "Please, enter an appropriate size for the grid!" << endl;
	} while (true);

}
char commandInput()
{
	char command;
	const int SIZE = 2;
	char input[SIZE];

	cout << "Enter direction:" << endl;
	do
	{
		cin.getline(input, SIZE);
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		else
		{
			command = input[0];
			if (command == 'w' || command == 'a' || command == 's' || command == 'd')
				return command;
		}
		cout << "Please, enter a correct command!" << endl;
	} 
	while (true);
}

void initialiseBoard(int** board, int gridSize)
{
	if (!board)
		return;

	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			board[i][j] = 0;
		}
	}
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

void moveTilesUp(int** board, int gridSize)
{

}
void moveTilesLeft(int** board, int gridSize)
{

}
void moveTilesDown(int** board, int gridSize)
{

}
void moveTilesRight(int** board, int gridSize)
{

}

void moveTiles(int** board, int gridSize, char command)
{
	if (!board)
		return;

	if (command == 'w')moveTilesUp(board, gridSize);
	if (command == 'a')moveTilesLeft(board, gridSize);
	if (command == 's')moveTilesDown(board, gridSize);
	if (command == 'd')moveTilesRight(board, gridSize);
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
void beginGame(int** board, int gridSize, int score)
{
	if (!board)
		return;

	char command;
	addRandomTile(board, gridSize);
	addRandomTile(board, gridSize);

	score = calculateScore(board, gridSize);
	printBoardAndScore(board, gridSize, score);

	while (true)
	{
		command = commandInput();
		moveTiles(board, gridSize, command);
	}
}

int main()
{
	const int NAMESIZE = 50;
	int score = 0;
	unsigned gridSize;
	char nickname[NAMESIZE];

	nicknameInput(nickname, NAMESIZE);
	gridSize = gridSizeInput();

	int** board = new int* [gridSize];
	for (int i = 0; i < gridSize; i++)
	{
		board[i] = new int[gridSize];
	}

	initialiseBoard(board, gridSize);
	beginGame(board, gridSize, score);
	deleteBoard(board, gridSize);
}
