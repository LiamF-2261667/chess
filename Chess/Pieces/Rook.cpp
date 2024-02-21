#include "Rook.h"
#include "Board/Board.h"
#include <iostream>

/* Get all the possible moves this piece can make from it's position witouth legalization checks */
std::vector<Position> Rook::getPossibleToPositions() const {
	std::vector<Position> possibleToPositions{};

	int currRow{ Piece::getPosition().row };
	int currColumn{ Piece::getPosition().column };

	for (int column = 0; column < Board::WIDTH; ++column) {
		possibleToPositions.push_back(Position(currRow, column));
	}
	
	for (int row = 0; row < Board::HEIGHT; ++row) {
		possibleToPositions.push_back(Position(row, currColumn));
	}

	return possibleToPositions;
}

bool Rook::isLegal(Movement move, Movement prevMove, bool isAttacking, bool showInfo) const
{
	/* Calculating necessary variables */
	Position fromPos{ move.from }, toPos{ move.to };
	int deltaRow = toPos.row - fromPos.row;
	int deltaColumn = toPos.column - fromPos.column;

	/* Only accept moves that are purely horizontal or vertical */
	if ((deltaRow == 0 && deltaColumn != 0) || (deltaRow != 0 && deltaColumn == 0))
		return true;

	if (showInfo)
		std::cout << "Rook cannot move this way.\n";
	return false;
}
