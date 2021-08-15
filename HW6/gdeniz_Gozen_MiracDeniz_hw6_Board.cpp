#include "gdeniz_Gozen_MiracDeniz_hw6_Board.h"

template<class typeName>
Board<typeName>::Board(int x, int y)
{
	// Summary: Parametric constructor for board class, creates a dynamic 2D matrix given row (x) and column (y) sizes
	rows = x;
	cols = y;

	boardMatrix = new Card<typeName>*[x];
	for (int k = 0; k < x; k++) {
		boardMatrix[k] = new Card<typeName>[y];
	}

}

template<class typeName>
Board<typeName>::~Board()
{
	// Summary: Destructor for board class, deletes the dynamic matrix
	for (int i = 0; i < rows; i++) {
		delete[] boardMatrix[i];
		boardMatrix[i] = NULL;
	}

	delete[] boardMatrix;
	boardMatrix = NULL;
}

template<class typeName>
void Board<typeName>::readBoardFromFile(ifstream& ifstr)
{
	// Summary: Sets up the card values given an ifstream buffer
	string line;
	typeName word;
	for (int i = 0; i < rows; i++) {
		getline(ifstr, line);
		istringstream lineInput(line);
		for (int j = 0; j < cols; j++) {
			lineInput >> word;
			boardMatrix[i][j].value = word;
			boardMatrix[i][j].isOpen = false;
		}
	}
}

template<class typeName>
void Board<typeName>::displayBoard()
{
	// Summary: Iterates over the matrix and prints it row by row
	for (int x = 0; x < rows; x++) {
		for (int y = 0; y < cols; y++) {
			if (boardMatrix[x][y].isOpen) {
				cout << boardMatrix[x][y].value << "  ";
			}
			else {
				cout << "x" << "  ";
			}
		}
		cout << endl;
	}
}

template<class typeName>
void Board<typeName>::closeCard(int x, int y)
{
	// Summary: Sets card state "isOpen" to false (closes the card)
	boardMatrix[x][y].isOpen = false;
}

template<class typeName>
int Board<typeName>::getRow()
{
	// Returns: the row size of the board
	return rows;
}

template<class typeName>
int Board<typeName>::getColumn()
{
	// Returns: the column size of the board
	return cols;
}

template<class typeName>
typeName Board<typeName>::showCard(int x, int y)
{
	// Summary: Opens the card and returns its value
	boardMatrix[x][y].isOpen = true;
	return boardMatrix[x][y].value;
}

template<class typeName>
bool Board<typeName>::isCardRevealed(int x, int y)
{
	// Summary: checks if the card is open or not (true if open)
	return boardMatrix[x][y].isOpen;
}