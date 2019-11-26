#include "Piece.h"
#include "Gameboard.h"

Piece::Piece(Gameboard * board_, Position startingPosition)
	: motherboard{ board_ }, position{ startingPosition }
{
}

void Piece::reposition(Position newPosition)
{
	position = newPosition;
}

Piece::~Piece()
{
}

void Piece::die()
{
	isAlive = false;
}

void Piece::resurrect()
{
	isAlive = true;
}
