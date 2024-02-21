#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece
{
public:
	// Constructor
	Bishop(Color color, Position position) : Piece(color, position) { }

	// Methods
	char getChar() const override { return 'b'; };
	bool canJump() const override { return false; };
	std::vector<Position> getPossibleToPositions() const override;
	bool isLegal(Movement move, Movement prevMove, bool isAttacking, bool showInfo) const override;
	
};

#endif
