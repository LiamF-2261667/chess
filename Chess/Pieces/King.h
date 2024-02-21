#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece
{
public:
	// Constructor
	King(Color color, Position position) : Piece(color, position) { }

	// Methods
	char getChar() const override { return 'k'; };
	bool canJump() const override { return false; };
	std::vector<Position> getPossibleToPositions() const override;
	bool isLegal(Movement move, Movement prevMove, bool isAttacking, bool showInfo) const override;
};

#endif
