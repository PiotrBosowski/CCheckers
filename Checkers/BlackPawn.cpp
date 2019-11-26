#include "BlackPawn.h"
#include "Gameboard.h"
#include <iostream>
using namespace std;

BlackPawn::BlackPawn(Gameboard * motherboard_, Position startingPosition) : BlackPiece{ motherboard_, startingPosition }
{
}

bool BlackPawn::makeStepIfPossible(Position targetPosition)
{
	if (motherboard->checkIfCordsExist(targetPosition) != false)
	{
		Direction direction = Position::getDirection(position, targetPosition);
		if (direction != wrong)
		{
			Piece * temp1 = motherboard->getPiece(targetPosition);
			if (temp1 == nullptr)
			{
				int distance = position.getDistance(targetPosition);
				if (distance == 1) //gdy poruszamy sie po skosie i nie bijemy niczego
				{
					if (direction == SE || direction == SW)
					{
						motherboard->movePiece(position, targetPosition);
						if (targetPosition.rank == 0) motherboard->promote(motherboard->getPiece(targetPosition));
						return true;
					}
				}
				else if (distance == 2) //gdy poruszamy sie po skosie i bijemy cos
				{
					Position middle{ (targetPosition.file + position.file) / 2, (targetPosition.rank + position.rank) / 2 };
					Piece * temp2 = motherboard->getPiece(middle);
					if (dynamic_cast<WhitePiece*>(temp2)) //jesli bijemy bialego
					{
						motherboard->movePiece(position, targetPosition);
						motherboard->removePiece(middle);
						if (targetPosition.rank == motherboard->getSize() - 1) motherboard->promote(motherboard->getPiece(targetPosition));
						return true;
					}
				}
			}
		}
	}
	return false;
}

void BlackPawn::printPiece()
{
	cout << "b";
}

Position BlackPawn::getPosition()
{
	return position;
}

bool BlackPawn::canMove() //sprawdzamy tylko pola, ktore istnieja (tutaj kontrolujemy, czy nie wyjezdzamy za plansze)
{
	for (int i = 0; i < 4; i++)
	{
		Position step1 = position.move(Position::DirectionArray[i], 1);
		if (motherboard->checkIfCordsExist(step1))
		{
			Piece * temp1 = motherboard->getPiece(step1);
			if (temp1 == nullptr)
			{
				if (Position::DirectionArray[i] == SE || Position::DirectionArray[i] == SW)
					return true;
			}
			if (dynamic_cast<WhitePiece*>(temp1))
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

BlackPawn::~BlackPawn()
{
}
