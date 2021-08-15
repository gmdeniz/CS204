#pragma once

#ifndef _GDENIZ_GOZEN_MIRACDENIZ_HW6_BOARD_H
#define _GDENIZ_GOZEN_MIRACDENIZ_HW6_BOARD_H

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

template <class typeName>
struct Card {
	typeName value;    // card value of type "typeName"
	bool isOpen;       // bool to set card open/close
};

template <class typeName>
class Board
{
	public:
		Board();             // default constructor for Board class (unused)
		Board(int x, int y); // Parametric constructor for Board class
		~Board();            // destructor for Board class

		void readBoardFromFile(ifstream& ifstr); // mutator type function to set the board
		void displayBoard();                     // accessor type function to display the board
		void closeCard(int x, int y);            // mutator type function to close card given its coordinates
		int getRow();                            // accessor for rows value
		int getColumn();                         // accessor for cols value
		typeName showCard(int x, int y);         // mutator function that reveals the card at (x,y) and returns its value
		bool isCardRevealed(int x, int y);       // accessor to check if card (x,y) is open

	private:
		Card<typeName> **boardMatrix;      // pointer of card pointers to be used as board
		int rows;                          // board row size
		int cols;                          // board column size

};

#include "gdeniz_Gozen_MiracDeniz_hw6_Board.cpp"
#endif