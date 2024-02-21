#ifndef SQUARE_H
#define SQUARE_H

#include "Functionality/Position.h"

class Piece;

class Square
{
public:
	// Setters
    void setPosition(Position position) { m_position = position; }

    // Getters
    Position getPosition() const { return m_position; }

	// Methods
	void setPiece(Piece* piece);
	void removePiece();

	Piece* getPiece() const { return m_piece; }

private:
	Piece* m_piece{};

	Position m_position{};
};

#endif
