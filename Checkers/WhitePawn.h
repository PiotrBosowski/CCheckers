#pragma once
#include "WhitePiece.h"
class WhitePawn : public WhitePiece
{
public:
	WhitePawn(Gameboard * motherboard_, Position startingPosition);
	bool makeStepIfPossible(Position targetPosition) override;
	void printPiece() override;
	Position getPosition();
	bool canMove() override;
	virtual ~WhitePawn();
};

