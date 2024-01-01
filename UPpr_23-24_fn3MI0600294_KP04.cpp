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
	cin.clear();
	cin.ignore(INT_MAX, '\n');
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
void fillCopyBoard(int** copyBoard, int** board, int gridSize)
{
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			copyBoard[i][j] = board[i][j];
		}
	}
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
	
	bool** isUsed = new bool*[gridSize];
	for (int i = 0; i < gridSize; i++)
	{
		isUsed[i] = new bool[gridSize];
		for (int j = 0; j < gridSize; j++)
		{
			isUsed[i][j] = false;
		}
	}
	
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

bool isGameOver(int** board, int gridSize, int score)
{
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			if (board[i][j] == 2048)
			{
				cout << "Congrats, you have won !!! :)" << endl;
				cout << "Your score is: " << score << endl;
				cout << endl;
				return true;
			}
		}
	}
	int** copyBoard = createBoard(gridSize);
	fillCopyBoard(copyBoard, board, gridSize);

	bool** isUsedCopy = new bool* [gridSize];
	for (int i = 0; i < gridSize; i++)
	{
		isUsedCopy[i] = new bool[gridSize];
		for (int j = 0; j < gridSize; j++)
		{
			isUsedCopy[i][j] = false;
		}
	}

	bool isPossible = false;
	moveTilesUp(copyBoard, gridSize, isPossible, isUsedCopy);

	fillCopyBoard(copyBoard, board, gridSize);
	moveTilesDown(copyBoard, gridSize, isPossible, isUsedCopy);

	fillCopyBoard(copyBoard, board, gridSize);
	moveTilesLeft(copyBoard, gridSize, isPossible, isUsedCopy);

	fillCopyBoard(copyBoard, board, gridSize);
	moveTilesRight(copyBoard, gridSize, isPossible, isUsedCopy);

	deleteBoard(copyBoard, gridSize);
	for (int i = 0; i < gridSize; i++)
	{
		delete[] isUsedCopy[i];
	}
	delete[] isUsedCopy;

	if (isPossible == false)
	{
		cout << "You have run out of moves ! Game over !!!" << endl;
		cout << endl;
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
	while (!isGameOver(board, gridSize, score))  /// tuk shte dobavq uslovieto igrata da ne e zavyrshila
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
void consoleMenu()
{
	const int NAMESIZE = 100;
	int score = 0;
	unsigned gridSize;
	char nickname[NAMESIZE];
	bool showMenu = true;

	int choice;
	while(true)
	{
		if (showMenu)
		{
			cout << "Select '1' to play, '2' to see the Leaderboard or '3' to quit!" << endl;
			cout << "1. Start game\n2. Leaderboard\n3. Quit" << endl;
		}
		cin >> choice;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid input. Please enter a number." << endl;
			showMenu = false;

		}
		else if (choice == 1)
		{
			nicknameInput(nickname, NAMESIZE);
			gridSize = gridSizeInput();
			int** board = createBoard(gridSize);

			beginGame(board, gridSize, score);
			deleteBoard(board, gridSize);
			showMenu = true;

		}
		/// else if (choice == 2)
		//tuk trqbva da dobavq leaderboard
		else if (choice == 3)
		{
			cout << "Hope to see you back soon!" << endl;
			break;
		}
		else
		{
			cout << "Please, try again. That's not a possible option" << endl;
			showMenu = false;
		}
	} 
}
int main()
{
	cout << "Welcome to the game 2048!" << endl;
	consoleMenu();
}
