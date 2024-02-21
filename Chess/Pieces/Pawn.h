#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Board;

class Pawn : public Piece
{
public:
	// Constructor
	Pawn(Color color, Position position) : Piece(color, position) { }

	// Methods
	char getChar() const override { return 'p'; };
	bool canJump() const override { return false;  };
	std::vector<Position> getPossibleToPositions() const override;
	bool isLegal(Movement move, Movement prevMove, bool isAttacking, bool showInfo) const override;

private:
	bool isLegalAttack(Movement move, Movement prevMove, bool isAttacking, bool showInfo) const;
	bool isLegalPlacement(Movement move, bool showInfo) const;
	bool isEnPassent(Movement move, Movement prevMove) const;
};

#endif
