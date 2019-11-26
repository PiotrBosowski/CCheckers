#pragma once

enum Color{ white = 0, black = 1};
enum Direction { NE, SE, SW, NW, wrong };

struct Position //repzezentuje pojedynczy punkt na szachownicy
{
	Position(int file_, int rank_) : file{ file_ }, rank{ rank_ }{}; //prosty konstruktor
	Position move(Direction direction, int numberOfSquares = 1);
	static Direction getDirection(Position source, Position target);
	int getDistance(Position second);
	int file; //kolumna, rosnie od lewej do prawej
	int rank; //rzad, rosnie od dolu do gory
	static const Direction DirectionArray[5];
};