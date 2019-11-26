#include "WhiteQueen.h"
#include <iostream>
#include "Gameboard.h"
using namespace std;

WhiteQueen::WhiteQueen(Gameboard * motherboard_, Position position_) : WhitePiece{ motherboard_, position_ }
{
}

bool WhiteQueen::makeStepIfPossible(Position targetPosition)
{
	if (motherboard->checkIfCordsExist(targetPosition) == false) return false;
	Direction direction = Position::getDirection(position, targetPosition);
	if (direction == wrong) return false;
	int distance = position.getDistance(targetPosition);
	Piece * temp = motherboard->whatsStandingThere(targetPosition);
	if (temp != nullptr) return false;
	Position actualPosition = position.move(direction, 1);
	int numberOfCaptures = 0;
	for(int i = 1; i<distance - 1; i++)
	{
		Piece * temp2 = motherboard->getPiece(actualPosition);
		if (dynamic_cast<BlackPiece*>(temp2))
		{
			motherboard->removePiece(actualPosition);
			numberOfCaptures++;
		}
		else if (dynamic_cast<WhitePiece*>(temp2)) return false;
		actualPosition = actualPosition.move(direction, 1);
	}
	if (numberOfCaptures > 1) return false;
	motherboard->movePiece(position, targetPosition);
	return true;
}

void WhiteQueen::printPiece()
{
	cout << "W";
}

bool WhiteQueen::canMove()
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
			else if (dynamic_cast<WhitePiece*>(temp))
			{
				break;
			}
			else if (dynamic_cast<BlackPiece*>(temp))
			{
				if(numberOfCaptures == 0) numberOfCaptures++;
				else break;
			}
			actualPosition = actualPosition.move(Position::DirectionArray[i], 1);
		}
	}
	return false;
}

WhiteQueen::~WhiteQueen() 
{
}
