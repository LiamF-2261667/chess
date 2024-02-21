#include "Queen.h"
#include "Board/Board.h"
#include <math.h>
#include <iostream>

/* Get all the possible moves this piece can make from it's position witouth legalization checks */
std::vector<Position> Queen::getPossibleToPositions() const {
	std::vector<Position> possibleToPositions{};

	int currRow{ Piece::getPosition().row };
	int currColumn{ Piece::getPosition().column };

	for (int index = 0; index < Board::WIDTH; ++index) {
		possibleToPositions.push_back(Position(currRow - (index - currColumn), index));
		possibleToPositions.push_back(Position(currRow - (currColumn - index), index));
	}

	for (int column = 0; column < Board::WIDTH; ++column) {
		possibleToPositions.push_back(Position(currRow, column));
	}

	for (int row = 0; row < Board::HEIGHT; ++row) {
		possibleToPositions.push_back(Position(row, currColumn));
	}

	return possibleToPositions;
}

bool Queen::isLegal(Movement move, Movement prevMove, bool isAttacking, bool showInfo) const
{
	/* Calculating necessary variables */
	Position fromPos{ move.from }, toPos{ move.to };
	int deltaRow = toPos.row - fromPos.row;
	int deltaColumn = toPos.column - fromPos.column;

	/* Accept moves that are purely horizontal or vertical */
	if ((deltaRow == 0 && deltaColumn != 0) || (deltaRow != 0 && deltaColumn == 0))
		return true;

	/* Allow perfect diagonal movement */
	if (abs(deltaRow) == abs(deltaColumn))
		return true;

	if (showInfo)
		std::cout << "Queen cannot move this way.\n";
	return false;
}
