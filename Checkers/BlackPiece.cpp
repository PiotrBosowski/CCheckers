#include "BlackPiece.h"

BlackPiece::BlackPiece(Gameboard * motherboard_, Position startingPosition) : Piece{motherboard_, startingPosition}
{
}

bool BlackPiece::canBeMoved(Color color)
{
	if (color == black) return true;
	return false;
}

BlackPiece::~BlackPiece()
{
}
