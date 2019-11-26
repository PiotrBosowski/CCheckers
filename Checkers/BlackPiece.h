#pragma once
#include "Piece.h"
class BlackPiece : public Piece
{
public:
	BlackPiece(Gameboard * motherboard_, Position startingPosition);
	bool canBeMoved(Color color) override;
	virtual ~BlackPiece();
};

