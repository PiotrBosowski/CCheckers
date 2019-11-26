#pragma once
#include "BlackPiece.h"
class BlackPawn : public BlackPiece
{
public:
	BlackPawn(Gameboard * motherboard_, Position startingPosition);
	bool makeStepIfPossible(Position targetPosition) override;
	void printPiece() override;
	Position getPosition();
	bool canMove() override;
	virtual ~BlackPawn();
};

