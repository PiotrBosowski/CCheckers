#include "Structures.h"
#include <cmath>
using namespace std;

const Direction Position::DirectionArray[5] = { NE, SE, SW, NW, wrong };

Position Position::move(Direction direction, int numberOfSquares)
{
	switch (direction)
	{
	case NE: return Position{ file + numberOfSquares, rank + numberOfSquares };
	case SE: return Position{ file + numberOfSquares, rank - numberOfSquares };
	case SW: return Position{ file - numberOfSquares, rank - numberOfSquares };
	case NW: return Position{ file - numberOfSquares, rank + numberOfSquares };
	default: return Position{ file, rank };
	}
}

Direction Position::getDirection(Position source, Position target)
{
	int fileDifference = target.file - source.file;
	int rankDifference = target.rank - source.rank;
	if (abs(fileDifference) != abs(rankDifference)) return wrong;
	if (fileDifference > 0)
		if (rankDifference > 0)
			return NE;
		else return SE; else
	if (rankDifference > 0)
			return NW;
		else return SW;
}

int Position::getDistance(Position second)
{
	int fileDifference = abs(second.file - file);
	int rankDifference = abs(second.rank - rank);
	if (fileDifference != rankDifference) throw "ruch nie po przekatnej";
	return fileDifference;
}
