#include "WhitePiece.h"



WhitePiece::WhitePiece(Gameboard * motherboard_, Position startingPosition) : Piece{ motherboard_, startingPosition }
{
}

bool WhitePiece::canBeMoved(Color color)
{
	if (color == white) return true;
	return false;
}

WhitePiece::~WhitePiece()
{
}

