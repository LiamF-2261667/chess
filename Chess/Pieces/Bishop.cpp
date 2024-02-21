#include "Bishop.h"
#include "Board/Board.h"
#include <math.h>

/* Get all the possible moves this piece can make from it's position witouth legalization checks */
std::vector<Position> Bishop::getPossibleToPositions() const {
	std::vector<Position> possibleToPositions{};

	int currRow{ Piece::getPosition().row };
	int currColumn{ Piece::getPosition().column };

	for (int index = 0; index < Board::WIDTH; ++index) {
		possibleToPositions.push_back(Position(currRow - (index - currColumn), index));
		possibleToPositions.push_back(Position(currRow - (currColumn - index), index));
	}

	return possibleToPositions;
}

bool Bishop::isLegal(Movement move, Movement prevMove, bool isAttacking, bool showInfo) const
{
	/* Calculating necessary variables */
	Position fromPos{ move.from }, toPos{ move.to };
	int deltaRow = toPos.row - fromPos.row;
	int deltaColumn = toPos.column - fromPos.column;

	/* Only allow perfect diagonal movement */
	if (abs(deltaRow) == abs(deltaColumn))
		return true;

	return false;
}
