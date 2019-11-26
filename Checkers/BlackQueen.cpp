#include "BlackQueen.h"
#include "Gameboard.h"
#include <iostream>
using namespace std;

BlackQueen::BlackQueen(Gameboard * motherboard_, Position startingPosition) : BlackPiece{motherboard_, startingPosition}
{
}

bool BlackQueen::makeStepIfPossible(Position targetPosition)
{
	if (motherboard->checkIfCordsExist(targetPosition) == false) return false;
	Direction direction = Position::getDirection(position, targetPosition);
	if (direction == wrong) return false;
	int distance = position.getDistance(targetPosition);
	Piece * temp = motherboard->whatsStandingThere(targetPosition);
	if (temp != nullptr) return false;
	Position actualPosition = position.move(direction, 1);
	int numberOfCaptures = 0;
	for (int i = 1; i < distance - 1; i++)
	{
		Piece * temp2 = motherboard->getPiece(actualPosition);
		if (dynamic_cast<WhitePiece*>(temp2))
		{
			motherboard->removePiece(actualPosition);
			numberOfCaptures++;
		}
		else if (dynamic_cast<BlackPiece*>(temp2)) return false;
		actualPosition = actualPosition.move(direction, 1);
	}
	if (numberOfCaptures > 1) return false;
	motherboard->movePiece(position, targetPosition);
	return true;
}

void BlackQueen::printPiece()
{
	cout << "B";
}

bool BlackQueen::canMove()
{
	for (int i = 0; i < 4; i++)
	{
		Position actualPosition = position.move(Position::DirectionArray[i], 1);
		while (motherboard->checkIfCordsExist(actualPosition))
		{
			Piece * temp = motherboard->getPiece(actualPosition);
			int numberOfCaptures = 0;
			if (temp == nullptr)
			{
				return true;
			}
			else if (dynamic_cast<BlackPiece*>(temp))
			{
				break;
			}
			else if (dynamic_cast<WhitePiece*>(temp))
			{
				if (numberOfCaptures == 0) numberOfCaptures++;
				else break;
			}
			actualPosition = actualPosition.move(Position::DirectionArray[i], 1);
		}
	}
	return false;
}


BlackQueen::~BlackQueen()
{
}
