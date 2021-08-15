#include "gdeniz_Gozen_MiracDeniz_hw6_Player.h"

template<class typeName>
Player<typeName>::Player(Board<typeName>& boardIn): board(boardIn), score(0)
{
	// Summary: Consturctor for player class, sets player score to 0 and stores the board info as reference
}

template<class typeName>
typeName Player<typeName>::openCard(int row, int col)
{
	// Summary: opens the card at (row,col) and returns its value

	return board.showCard(row, col);
}

template<class typeName>
bool Player<typeName>::validMove(int row, int col)
{
	// Summary: Checks if the move on (row,col) coordinates is valid
	// Returns: true if move is valid, else false

	if (!(board.getRow() > row && board.getColumn() > col) || row < 0 || col < 0) return false;
	if (board.isCardRevealed(row, col)) return false;
	return true;
}

template<class typeName>
void Player<typeName>::increaseNumberOfSuccess()
{
	// Summary: Increments player score by 1

	score++;
}

template<class typeName>
int Player<typeName>::getNumberOfSuccess()
{
	// Returns: score of the player

	return score;
}