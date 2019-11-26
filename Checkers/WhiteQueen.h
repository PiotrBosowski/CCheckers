#pragma once
#include "WhitePiece.h"
class WhiteQueen : public WhitePiece
{
public:
	WhiteQueen(Gameboard * motherboard_, Position startingPosition);
	bool makeStepIfPossible(Position targetPosition) override;
	void printPiece() override;
	bool canMove() override;
	virtual ~WhiteQueen();
};