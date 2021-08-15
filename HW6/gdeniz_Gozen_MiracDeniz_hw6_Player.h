#pragma once

#ifndef _GDENIZ_GOZEN_MIRACDENIZ_HW6_PLAYER_H
#define _GDENIZ_GOZEN_MIRACDENIZ_HW6_PLAYER_H

#include "gdeniz_Gozen_MiracDeniz_hw6_Board.h"

using namespace std;

template <class typeName>
class Player
{
	public:
		Player();                            // default constructor for Player class (unused)
		Player(Board<typeName>& boardIn);    // constructor for Player class, sets the board and score

		typeName openCard(int row, int col); // opens card at (row,col), returns its value
		bool validMove(int row, int col);    // checks validity of move (row,col)
		void increaseNumberOfSuccess();      // mutator for score, increments score by 1
		int getNumberOfSuccess();            // accessor for score

	private:
		int score;               // variable to store player score
		Board<typeName>& board;  // board stored as reference variable
};

#include "gdeniz_Gozen_MiracDeniz_hw6_Player.cpp"
#endif