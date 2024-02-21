#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece
{
public:
	// Constructor
	Queen(Color color, Position position) : Piece(color, position) { }

	// Methods
	char getChar() const override { return 'q'; };
	bool canJump() const override { return false; };
	std::vector<Position> getPossibleToPositions() const override;
	bool isLegal(Movement move, Movement prevMove, bool isAttacking, bool showInfo) const override;
};

#endif
