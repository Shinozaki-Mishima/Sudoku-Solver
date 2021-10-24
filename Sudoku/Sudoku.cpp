#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define SIZE 9
#define blankSpace 0
#define completeBoard std::make_pair(9, 9)

// utility function to print board 
void display_board(int board[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		cout << "  " << " " << " " << " " << "\n";
		cout << "------------------------------------------------------" << "\n";
		for (int j = 0; j < SIZE; j++)
		{
			cout << " ";
			if (board[i][j] == 0)
			{
				cout << " ";
			}
			else
			{
				cout << board[i][j];
			}
			cout << " ";
			cout << " | ";
		}
	}
	cout << "\n" << "------------------------------------------------------" << "\n" << "\n";
} // end of function
// function that searches the board for empty spaces, if found, the parameters 'i' and 'j' will be assigned the position that is empty.
pair<int, int> findEmptyLocation(int board[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (board[i][j] == blankSpace)
			{
				return make_pair(i, j);
			}
		}
	}
	return completeBoard;
} // end of function
// function that checks the validity of the specified column
bool isColValid(int board[SIZE][SIZE], int num, int j)  // j = column
{
	// check column
	for (int i = 0; i < SIZE; i++)
	{
		if (board[i][j] == num)
		{
			return true;  // returns true if an entry in the specified column matches the num
		}
	}
	return false;
} // end of function
// function that checks the validity of the specified row 
bool isRowValid(int board[SIZE][SIZE], int num, int j)  // j = row
{
	// check row 
	for (int i = 0; i < SIZE; i++)
	{
		if (board[j][i] == num)  
		{
			return true;  // returns true if an entry in the specified row matches the num
		}
	}
	return false;
} // end of function
// function that checks the validity of the specified box (3 x 3)
bool isBoxValid(int board[SIZE][SIZE], int num, int boxRS, int boxCS)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i + boxRS][j + boxCS] == num)
			{
				return true;  //  returns true if an entry in the specified 3x3 box matches the num
			}
		}
	}
	return false;
} // end of function
// function that checks whether it would be valid to assign a number to a specified index
bool isValid(int board[SIZE][SIZE], int num, int row, int column)
{
	// verify whether the number to be assigned was not already placed in the current box, row or column
	return !isRowValid(board, num, row) && 
		   !isColValid(board, num, column) && 
		   !isBoxValid(board, num, row - row % 3, column - column % 3);
} // end of function
// function that attepts to solve a partically assigned board, 
bool solveBoard(int board[SIZE][SIZE])
{
	// if there are no empty locations, return true, the board is complete
	if (findEmptyLocation(board) == completeBoard)
	{
		return true;
	}
	// Get an empty board location
	pair<int, int> position = findEmptyLocation(board);
	int x = position.first;
	int y = position.second;

	// examine numbers 1 - 9
	for (int i = 1; i <= 9; i++)
	{
		// check if the value is valid
		if (isValid(board, i, x, y))
		{
			// store value at location (x, y)  
			board[x][y] = i;

			// using recursion, to scan through for all possible locations on the board and return true 
			if (solveBoard(board))
			{
				return true;
			}
			// default condition, in the event of failure to solve 
			board[x][y] = blankSpace;
		}
	}
	return false;
}  // end of function

int main()
{
	// take user input 
	string input;
	cout << "Enter a number 1 through 3 to select a board.";
	cin >> input;

	// create a grid as a 2d array
	int board[SIZE][SIZE]{};

	// read boards from file 
	ifstream file{ input+".txt" };
	if (!file) {
		cout << "Error, file couldn't be opened" << endl;
		return 1;
	}
	// iteratively store the board in the 2d array
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			file >> board[i][j];
			if (!file) {
				cout << "Error reading file for element " << i << "," << j << endl;
				return 1;
			}
		}
	}
	// display the partially complete board
	display_board(board);
	// solve the sudoku board 
	if(true == solveBoard(board))
	{
		cout << "\nSolution:\n";
		display_board(board);
	} else {
		cout << "A solution could not be found.";  
	}
	return 0;
}  // end of main

