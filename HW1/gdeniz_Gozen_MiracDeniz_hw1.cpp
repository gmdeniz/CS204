#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

//Mirac Deniz Gozen 27806

struct wordStats { // structure to store info about the word and its placement rules
	string word, direction, orientation;
	int row, col;
};


string filePrompt() {
/// Summary: Prompts user to enter a valid file name to be used in the main program. 
/// Returns: The first valid file name input as a string.                            
	
	string filename;
	bool inputNotVerified = true;
	ifstream input;

	cout << "Please enter the name of the file : "; // asks filename
	cin >> filename;

	while (inputNotVerified) {
		input.open(filename.c_str()); // attempts to open the file

		if (input.fail()) { // if the file cannot be opened, filename is asked again
			cout << "File name is incorrect, please enter again: ";
			cin >> filename;
		}
		else {
			inputNotVerified = false; 
			input.close(); // file is closed if filename is read successfully

			return filename;
		}
	}
}


int lineElementCount(string line) {
/// Summary: Counts the number of words in the input string.
/// Returns: Number of words as an integer.

	istringstream lineInput(line);
	string word;
	int valueCount = 0; // word count is initialized to 0.

	while (lineInput >> word) {
		valueCount++;  // incrementing word count by one for each word read.
	}
	return valueCount;
}

void placeWord(vector<vector<char>>& matrix, wordStats wordInfo) {
/// Summary: Creates a placeholder matrix equivalent to the input matrix and attempts to place the word according to the input parameters.
/// Upon the successful placement of the word, the input matrix which was taken as a reference parameter is set equal to the placeholder matrix.

	vector<vector<char>> testMatrix = matrix;   // Creates a placeholder matrix equivalent to input matrix
	int row = wordInfo.row, col = wordInfo.col; 
	string direction = wordInfo.direction, orientation = wordInfo.orientation;

	if (matrix[row][col] != '-') {         // if the character at starting position is not "-", an error message is printed
		cout << "\"" << wordInfo.word << "\"" << " could not be put into the matrix with given starting point : " << row << "," << col << "\t";
		cout << "direction: " << wordInfo.direction << "\t" << "orientation: " << wordInfo.orientation << endl;
	}

	else if (wordInfo.word.size() == 1) {  // if the character at starting position = "-" and letter count of the word is 1, word is put into the matrix
		testMatrix[row][col] = wordInfo.word[0]; 
		matrix = testMatrix;

		cout << "\"" << wordInfo.word << "\"" << " was put into the matrix with given starting point : " << wordInfo.row << "," << wordInfo.col << "\t"; 
		cout << "direction: " << wordInfo.direction << "\t" << "orientation: " << wordInfo.orientation << endl;
	}

	else { // character at starting position = "-" and the letter count of the word is > 1
		testMatrix[row][col] = wordInfo.word[0];        // first letter of the word is immediately placed.
		int lettersPlaced = 1;                          // as the first letter is immediately placed, number of placed letters is set equal to 1

		for (int j = 1; j < wordInfo.word.size(); j++) {   // iterates over the letters of the input word except the 1st letter.

			bool placementSuccessful = false; 

			int attempts = 0;								// number of unsuccesful placement attempts per letter
			direction = wordInfo.direction;					// preffered placement direction is set

			while (!placementSuccessful && attempts < 4) {		// upon successful placement or 4 failed attempts in each direction, loop exits.

				if (direction == "u") {							// checks if placement direction is "u"p

					if (row - 1 >= 0) {							// checks if there exists a cell that is 1 above the current.

						if (testMatrix[row - 1][col] == '-') {           // checks if the character in the cell is "-"
							testMatrix[row - 1][col] = wordInfo.word[j]; // letter is placed in the above cell
							lettersPlaced++;                             // increments # of placed letters by 1
							row--;                                       // current position is updated
							placementSuccessful = true; 
							break;
						}
						else {
							attempts++;                                // increments # of unsuccesful placement attempts by 1
							if (orientation == "CW") direction = "r";  // if the character in the cell is not "-", new direction is set based on CW orientation
							if (orientation == "CCW") direction = "l"; // if the character in the cell is not "-", new direction is set based on CCW orientation
						}
					}
					else {
						attempts++;                                    // increments # of unsuccesful placement attempts by 1
						if (orientation == "CW") direction = "r";      // if the above cell doesn't exist, new direction is set based on CW orientation
						if (orientation == "CCW") direction = "l";     // if the above cell doesn't exist, new direction is set based on CCW orientation
					}
				}

				if (direction == "r") { // Same functionality as the if statement with direction == "u"

					if (col + 1 <= matrix[0].size() - 1) { 

						if (testMatrix[row][col + 1] == '-') { 

							testMatrix[row][col + 1] = wordInfo.word[j];
							lettersPlaced++;
							col++;
							placementSuccessful = true;
							break;
						}
						else {
							attempts++;
							if (orientation == "CW") direction = "d";
							if (orientation == "CCW") direction = "u";
						}
					}
					else {
						attempts++;
						if (orientation == "CW") direction = "d";
						if (orientation == "CCW") direction = "u";
					}
				}

				if (direction == "d") {  // Same functionality as the if statement with direction == "u"
					if (row + 1 <= matrix.size() - 1) {
						if (testMatrix[row + 1][col] == '-') {
							testMatrix[row + 1][col] = wordInfo.word[j];
							lettersPlaced++;
							row++;
							placementSuccessful = true;
							break;
						}
						else {
							attempts++;
							if (orientation == "CW") direction = "l";
							if (orientation == "CCW") direction = "r";
						}
					}
					else {
						attempts++;
						if (orientation == "CW") direction = "l";
						if (orientation == "CCW") direction = "r";
					}
				}

				if (direction == "l") {  // Same functionality as the if statement with direction == "u"
					if (col - 1 >= 0) {
						if (testMatrix[row][col - 1] == '-') {
							testMatrix[row][col - 1] = wordInfo.word[j];
							lettersPlaced++;
							col--;
							placementSuccessful = true;
							break;
						}
						else {
							attempts++;
							if (orientation == "CW") direction = "u";
							if (orientation == "CCW") direction = "d";
						}
					}
					else {
						attempts++;
						if (orientation == "CW") direction = "u";
						if (orientation == "CCW") direction = "d";
					}
				}
			}
			if (lettersPlaced == wordInfo.word.size()) { // if # of placed letters is equal to letter count of the word, input matrix is set equal to the placeholder matrix
				cout << "\"" << wordInfo.word << "\"" << " was put into the matrix with given starting point : " << wordInfo.row << "," << wordInfo.col << "\t";
				cout << "direction: " << wordInfo.direction << "\t" << "orientation: " << wordInfo.orientation << endl;
				matrix = testMatrix;
			}
			if (!placementSuccessful && attempts >= 4) { // if placement of any letter was unsuccessful, a message states the situation.
				cout << "\"" << wordInfo.word << "\"" << " could not be put into the matrix with given starting point : " << wordInfo.row << "," << wordInfo.col << "\t";
				cout << "direction: " << wordInfo.direction << "\t" << "orientation: " << wordInfo.orientation << endl;
				break;
			}		
		}
	}
}

void printMatrix(vector<vector<char>> matrix) {
	/// Summary: Prints the input matrix

	int row = matrix.size(), col = matrix[0].size();
	for (int a = 0; a < row; a++) {
		for (int b = 0; b < col; b++) {

			if (b == (col - 1)) { // if at last column, prints the cell and ends the line
				cout << matrix[a][b] << endl;
			}

			else {
				cout << matrix[a][b] << "\t"; // if not at last column, prints the cell and a tab character
			}
		}
	}
}

int main() {
	string currentLine, file_name = filePrompt(); // filename is read by the filePrompt function as a string
	ifstream inputFile(file_name.c_str());
	int matrixRow, matrixCol;

	getline(inputFile, currentLine);

	istringstream lineStream(currentLine); // reads the first line of the file
	lineStream >> matrixRow >> matrixCol;  // matrix dimensions are read from the first line of the file

	if (matrixRow <= 0 || matrixCol <= 0) { // checks if matrix dimensions are valid (not 0 or negative) and if not, program exits
		cout << "Invalid number for row and/or column!" << endl;
		return 0;
	}

	vector<vector<char>> matrix(matrixRow, vector<char>(matrixCol, '-')); // creates a matrix with given dimensions, sets all cell to be "-"

	while (getline(inputFile, currentLine)) { // iterates over lines of the file (exluding line 1)
		istringstream lineStream(currentLine);

		if (lineElementCount(currentLine) == 5) { // checks if there are exactly 5 words in the current line
			wordStats mWord;
			lineStream >> mWord.word >> mWord.row >> mWord.col >> mWord.direction >> mWord.orientation; // words and their placement rules are read from the lines

			if (mWord.row <= (matrixRow - 1) && mWord.row >= 0 && mWord.col <= (matrixCol - 1) && mWord.col >= 0) { //checks if placement coordinates exceed the matrix dimensions

				if (mWord.direction == "r" || mWord.direction == "d" || mWord.direction == "l" || mWord.direction == "u") { // checks the validity of direction

					if (mWord.orientation == "CW" || mWord.orientation == "CCW") { // checks the validity of orientation
						placeWord(matrix, mWord); // attempts to place the word into the matrix
						printMatrix(matrix);      // prints the matrix
					}
					else {
						cout << "Invalid input for orientation! Orientation: " << mWord.orientation << endl;
					}
				}

				else {
					cout << "Invalid input for direction! Direction: " << mWord.direction << endl;
				}
			}

			else {
				cout << "Starting point is out of range! Point: " << mWord.row << "," << mWord.col << endl;
			}
		}

		else {
			cout << "Invalid line! Number of values is different than 5." << endl;
			lineStream.ignore();
		}
	}
	return 0;
}