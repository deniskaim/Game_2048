#include <iostream>
using namespace std;
void nicknameInput(char* nickname, const int NAMESIZE)
{
	if (!nickname)
		return;
	
	cout << "Enter your nickname: " << endl;
	cin.getline(nickname, NAMESIZE);
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "This username is too long. Choose another one!" << endl;
		/// Tuk shte e umestno da pravq proverka dali imeto veche e zaeto
		cin.getline(nickname, NAMESIZE);
	}

}
int gridSizeInput()
{
	unsigned gridSize;
	cout << "Enter dimension: " << endl;
	cin >> gridSize;

	while (!(gridSize >= 4 && gridSize <= 10))
	{
		cout << "Please, enter an appropriate size for the grid!" << endl;
		cin >> gridSize;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Invalid input. Please enter a number." << endl;
		}
	}
	return gridSize;
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
void printBoard(int** board, int gridSize)
{
	if (!board)
		return;

	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
		cout << endl;
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
	printBoard(board, gridSize);
	deleteBoard(board, gridSize);
}