#ifndef PIECE_H
#define PIECE_H

#include "Functionality/Position.h"
#include "Functionality/Movement.h"
#include "Functionality/Color.h"
#include <vector>

class Piece
{
public:
	// Constructor
	Piece(Color color, Position position) : m_color{ color }, m_position{ position } { }

	// Getters
	Position getPosition() const { return m_position; }
	Color getColor() const { return m_color; }
	bool hasMoved() const { return m_hasMoved; }
	
	// Setters
	void setPosition(Position position) { m_position = position; }
	void setMoved() { m_hasMoved = true; }

	// Methods
	virtual char getChar() const = 0;
	virtual bool canJump() const = 0;
	virtual std::vector<Position> getPossibleToPositions() const = 0;
	virtual bool isLegal(Movement move, Movement prevMove, bool isAttacking, bool showInfo) const = 0;

private:
	Color m_color{};
	Position m_position{};
	bool m_hasMoved{ false };
};

#endif
