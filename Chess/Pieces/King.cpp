#include "King.h"
#include <iostream>
#include <math.h>

/* Get all the possible moves this piece can make from it's position witouth legalization checks */
std::vector<Position> King::getPossibleToPositions() const {
	std::vector<Position> possibleToPositions{};

	int currRow{ Piece::getPosition().row };
	int currColumn{ Piece::getPosition().column };

	std::vector<int> directions{ 1, -1, 0 };

	// Calculate all the 1 step positions
	for (int i : directions) {
		for (int j : directions) {
			if (i != 0 || j != 0)
				possibleToPositions.push_back(Position(currRow + i, currColumn + j));
		}
	}
	/* Possible castle moves */
	possibleToPositions.push_back(Position(currRow, currColumn - 2));
	possibleToPositions.push_back(Position(currRow, currColumn + 2));

	return possibleToPositions;
}

/* Test if a movement is legal for a King */
bool King::isLegal(Movement move, Movement prevMove, bool isAttacking, bool showInfo) const
{
	/* Calculating necessary variables */
	Position fromPos{ move.from }, toPos{ move.to };
	int deltaRow = abs(toPos.row - fromPos.row);
	int deltaColumn = abs(toPos.column - fromPos.column);

	/* Only accept moves 1 in every direction */
	if (deltaRow <= 1 && deltaColumn <= 1)
		return true;

	if (showInfo)
		std::cout << "King cannot move this way.\n";
	return false;
}
