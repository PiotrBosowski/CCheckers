#include "Square.h"

Square::Square(Color color_) : squareColor{color_}
{
}

Color Square::getSquareColor()
{
	return squareColor;
}

Piece * Square::getPiece()
{
	return piecePointer;
}

void Square::setPiece(Piece * newPiece)
{
	piecePointer = newPiece;
}

void Square::removePiece()
{
	piecePointer = nullptr;
}


Square::~Square()
{
}
