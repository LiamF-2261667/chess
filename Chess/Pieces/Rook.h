#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"


class Rook : public Piece
{
public:
	// Constructor
	Rook(Color color, Position position) : Piece(color, position) { }

	// Methods
	char getChar() const override { return 'r'; };
	bool canJump() const override { return false; };
	std::vector<Position> getPossibleToPositions() const override;
	bool isLegal(Movement move, Movement prevMove, bool isAttacking, bool showInfo) const override;
};

#endif
