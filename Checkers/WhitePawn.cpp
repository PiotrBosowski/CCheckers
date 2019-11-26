#include "WhitePawn.h"
#include <iostream>
#include "Gameboard.h"
using namespace std;

WhitePawn::WhitePawn(Gameboard * motherboard_, Position startingPosition) : WhitePiece{ motherboard_, startingPosition }
{
}

bool WhitePawn::makeStepIfPossible(Position targetPosition)
{
	if (motherboard->checkIfCordsExist(targetPosition) == false) return false;
	Direction direction = Position::getDirection(position, targetPosition);
	if (direction == wrong) return false;
	int distance = position.getDistance(targetPosition);
	Piece * temp1 = motherboard->getPiece(targetPosition);
	if (temp1 != nullptr) return false;
	if (distance == 1) //gdy poruszamy sie po skosie i nie bijemy niczego
	{
		if (direction == NE || direction == NW)
		{
			motherboard->movePiece(position, targetPosition);
			if (targetPosition.rank == motherboard->getSize() - 1) motherboard->promotePawn(targetPosition);
			return true;
		}
	}
	else if (distance == 2) //gdy poruszamy sie po skosie i bijemy cos
	{
		Position middle{ (targetPosition.file + position.file) / 2, (targetPosition.rank + position.rank) / 2 };
		Piece * temp2 = motherboard->getPiece(middle);
		if (dynamic_cast<BlackPiece*>(temp2)) //jesli bijemy czarnego
		{
			motherboard->movePiece(position, targetPosition);
			motherboard->removePiece(middle);
			if (targetPosition.rank == motherboard->getSize() - 1) motherboard->promotePawn(targetPosition);
			return true;
		}
	}
	return false;
}

void WhitePawn::printPiece()
{
	cout << "w";
}

Position WhitePawn::getPosition()
{
	return position;
}

bool WhitePawn::canMove() //zajebista funkcja fajny kod wreszcie
{
	for (int i = 0; i < 4; i++)
	{
		Position step1 = position.move(Position::DirectionArray[i], 1);
		if (motherboard->checkIfCordsExist(step1))
		{
			Piece * temp1 = motherboard->getPiece(step1);
			if (temp1 == nullptr)
			{
				if (Position::DirectionArray[i] == NE || Position::DirectionArray[i] == NW)
					return true;
			}
			if (dynamic_cast<BlackPiece*>(temp1))
			{
				Position step2 = position.move(Position::DirectionArray[i], 2);
				if (motherboard->checkIfCordsExist(step2))
				{
					if (motherboard->getPiece(step2) == nullptr) return true;
				}
			}
		}
	}
	return false;
}

WhitePawn::~WhitePawn()
{
}
