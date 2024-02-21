#include "Pawn.h"
#include <iostream>

/* Get all the possible moves this piece can make from it's position witouth legalization checks */
std::vector<Position> Pawn::getPossibleToPositions() const {
	std::vector<Position> possibleToPositions{};

	int currRow{ Piece::getPosition().row };
	int currColumn{ Piece::getPosition().column };
	int currColor{ (int) Piece::getColor() };

	// Move 1 forward
	possibleToPositions.push_back(Position(currRow - 1 + 2 * currColor, currColumn));
	// Move 2 forward
	possibleToPositions.push_back(Position(currRow - 2 + 4 * currColor, currColumn));
	// Take left
	possibleToPositions.push_back(Position(currRow - 1 + 2 * currColor, currColumn - 1));
	// Take right
	possibleToPositions.push_back(Position(currRow - 1 + 2 * currColor, currColumn + 1));

	return possibleToPositions;
}

/* Test if a movement is legal for a pawn */
bool Pawn::isLegal(Movement move, Movement prevMove, bool isAttacking, bool showInfo) const
{
	if (!isLegalPlacement(move, showInfo))
		return false;

	if (!isLegalAttack(move, prevMove, isAttacking, showInfo))
		return false;

	return true;
}

/* Test if an attempted attack is legal */
bool Pawn::isLegalAttack(Movement move, Movement prevMove, bool isAttacking, bool showInfo) const
{
	/* Calculating necessary variables */
	Position fromPos{ move.from }, toPos{ move.to };
	int deltaColumn = toPos.column - fromPos.column;

	/* Trying to take a piece head on is not legal */
	if (deltaColumn == 0) {
		if (isAttacking) {
			if (showInfo)
				std::cout << "Pawn cannot take here.\n";
			return false;
		}
	}

	/* If you're not attacking anything, yet moving sideways, then it's not legal (except for en-passant) */
	if (deltaColumn == 1 || deltaColumn == -1) {
		if (!isAttacking) {
			if (!isEnPassent(move, prevMove)) {
				if (showInfo)
					std::cout << "Pawn cannot move this way.\n";
				return false;
			}
		}
	}

	return true;
}

/* Test if any given movement to an empty tile is legal */
bool Pawn::isLegalPlacement(Movement move, bool showInfo) const
{
	/* Calculating necessary variables */
	Position fromPos{ move.from }, toPos{ move.to };
	int deltaRow = toPos.row - fromPos.row;
	int deltaColumn = toPos.column - fromPos.column;

	/* If you move > 2 tiles it's illegal */
	if (deltaRow != (-1 + 2 * (int)Piece::getColor())) {

		if (deltaRow != (-2 + 4 * (int)Piece::getColor())) {
			if (showInfo)
				std::cout << "Pawn cannot move this way.\n";
			return false;
		}

		/* If it moves 2 tiles ahead */
		if (Piece::hasMoved() == true) {
			if (showInfo)
				std::cout << "This pawn has already moved, cannot move two tiles ahead.\n";
			return false;
		}
	}
	/* Any diagonal movement is not allowed */
	if (deltaColumn > 1 || deltaColumn < -1) {
		if (showInfo)
			std::cout << "Pawn cannot move this way.\n";
		return false;
	}

	return true;
}

/* Test if a pawn can do an en-passent */
bool Pawn::isEnPassent(Movement move, Movement prevMove) const
{
	/* Calculating necessary variables */
	Position fromPos{ move.from }, toPos{ move.to };
	Position prevFromPos{ prevMove.from }, prevToPos{ prevMove.to };

	int deltaRowPrev = prevToPos.row - prevFromPos.row;
	int deltaColumn = toPos.column - fromPos.column;

	Position attackedSquare{ fromPos.row, fromPos.column + deltaColumn };

	/* If the previously moved piece is not adjacent to the selected pawn */
	if (attackedSquare != prevToPos)
		return false;

	/* If the previusly moved piece didn't move 2 tiles ahead */
	if (deltaRowPrev != -(-2 + 4 * (int)Piece::getColor()))
		return false;

	return true;
}
