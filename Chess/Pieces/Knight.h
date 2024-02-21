#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece
{
public:
	// Constructor
	Knight(Color color, Position position) : Piece(color, position) { }

	// Methods
	char getChar() const override { return 'n'; };
	bool canJump() const override { return true; };
	std::vector<Position> getPossibleToPositions() const override;
	bool isLegal(Movement move, Movement prevMove, bool isAttacking, bool showInfo) const override;
};

#endif
