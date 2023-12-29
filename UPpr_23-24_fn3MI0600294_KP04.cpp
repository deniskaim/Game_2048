#include <iostream>
#include <iomanip>
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
	printBoardAndScore(board, gridSize, score);
	deleteBoard(board, gridSize);
}
