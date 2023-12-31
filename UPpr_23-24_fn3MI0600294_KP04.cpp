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
	cout << endl;
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

	cout << endl;

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
			cout << "Please, enter a correct command!" << endl;
		}
		else
		{
			command = input[0];
			if (command == 'w' || command == 'a' || command == 's' || command == 'd')
			{
				return command;
			}
			cout << "Choose one of the following: 'w', 'a', 's', 'd'" << endl;
		}
	} while (true);

	cout << endl;
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
	// TUK TRQBVA DA POLZVAM PROMENLIVA, KOQTO DA MI KAZVA DALI E IMALO OBEDINENIE V KLETKATA BOARD[I-1][COLUMN]
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
void moveTilesLeft(int** board, int gridSize, bool& isSuccessfulCommand, bool** isUsed)
{

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
void moveTilesRight(int** board, int gridSize, bool& isSuccessfulCommand, bool** isUsed)
{

}

void moveTiles(int** board, int gridSize, char command, bool& isSuccesfulCommand)
{
	if (!board)
		return;
	
	bool** isUsed = new bool*[gridSize];
	for (int i = 0; i < gridSize; i++)
	{
		isUsed[i] = new bool[gridSize];
		for (int j = 0; j < gridSize; j++)
		{
			isUsed[i][j] = false;
		}
	}
	
	// tuk shte napravq dinamichna matrica, koqto da pomni dali e imalo obedinenie v kletkata,
	/// za da moje 4 4 4 4 <- da stava 8 8, a ne 16
	if (command == 'w')
		moveTilesUp(board, gridSize, isSuccesfulCommand, isUsed);

	else if (command == 'a')
		moveTilesLeft(board, gridSize, isSuccesfulCommand, isUsed);

	else if (command == 's')
		moveTilesDown(board, gridSize, isSuccesfulCommand, isUsed);

	else if (command == 'd')
		moveTilesRight(board, gridSize, isSuccesfulCommand, isUsed);

	for (int i = 0; i < gridSize; i++)
	{
		delete[] isUsed[i];
	}
	delete[] isUsed;
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

	cin.clear();
	cin.ignore(INT_MAX, '\n');
	while (true)  /// tuk shte dobavq uslovieto igrata da ne e zavyrshila
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
