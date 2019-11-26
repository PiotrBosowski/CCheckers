#pragma once
#include "BlackPiece.h"
class BlackQueen :
	public BlackPiece
{
public:
	BlackQueen(Gameboard * motherboard_, Position startingPosition);
	bool makeStepIfPossible(Position targetPosition) override;
	void printPiece() override;
	bool canMove() override;
	virtual ~BlackQueen();
};

