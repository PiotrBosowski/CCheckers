#pragma once
#include "Structures.h"

class Gameboard;

enum MovePattern { N = 1, E = 1, S = -1, W = -1 };

class Piece //bierka, po niej dziedziczy pionek i krolowa
{
public:
	Piece(Gameboard * motherboard_, Position startingPosition); //konstruktor
	virtual bool canMove() = 0; //funkcja wirtualna, sprawdza, czy dany pionek moze sie ruszyc
	virtual bool makeStepIfPossible(Position targetPosition) = 0;
	virtual bool canBeMoved(Color playerColor) = 0;
	void reposition(Position newPosition);
	virtual void printPiece() = 0;
	virtual ~Piece(); //destruktor
	void die();
	void resurrect();

protected:
	Gameboard * motherboard; //wskaznik na szachownice, na ktorej ustawiony jest pionek
	Position position;
	bool isAlive = true;
};

