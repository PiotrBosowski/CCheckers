#pragma once
#include "Piece.h"
class WhitePiece : public Piece
{
public:
	WhitePiece(Gameboard * motherboard_, Position startingPosition);
	bool canBeMoved(Color color) override;
	virtual ~WhitePiece();
};