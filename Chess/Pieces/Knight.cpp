#include "Knight.h"
#include <iostream>
#include <math.h>

/* Get all the possible moves this piece can make from it's position witouth legalization checks */
std::vector<Position> Knight::getPossibleToPositions() const {
	std::vector<Position> possibleToPositions{};

	int currRow{ Piece::getPosition().row };
	int currColumn{ Piece::getPosition().column };

	std::vector<int> directions{ 1, -1 };

	// Calculate all the L-shapes
	for (int i : directions) {
		for (int j : directions) {
			possibleToPositions.push_back(Position(currRow + 2 * i, currColumn + 1 * j));
			possibleToPositions.push_back(Position(currRow + 1 * i, currColumn + 2 * j));
		}
	}

	return possibleToPositions;
}

/* Test if a movement is legal for a Knight */
bool Knight::isLegal(Movement move, Movement prevMove, bool isAttacking, bool showInfo) const
{
	/* Calculating necessary variables */
	Position fromPos{ move.from }, toPos{ move.to };
	int deltaRow = abs(toPos.row - fromPos.row);
	int deltaColumn = abs(toPos.column - fromPos.column);

	/* Only accept moves that are in an L-shape */
	if ((deltaRow == 1 && deltaColumn == 2) || (deltaRow == 2 && deltaColumn == 1))
		return true;

	if (showInfo)
		std::cout << "Rook cannot move this way.\n";
	return false;
}
