#ifndef PLAYER_H
#define PLAYER_H

#include "Functionality/Color.h"
#include "Functionality/Movement.h"
#include "Functionality/Type.h"

#include <vector>
#include <string>

class Legalization;

class Player
{
public:
	// Constructors
    Player(const Color color, Legalization* legalizer, bool isAI = false) : m_legalizer{ legalizer }, m_color{ color }, m_isAI{ isAI } { }

	// Getters
	Color getColor() const { return m_color; }
    bool isAI() const { return m_isAI; }

    // Methods
    virtual Movement getMove() { return Movement(Position(-1, -1), Position(-1, -1)); }
    virtual Type getPromote() { return Type::QUEEN; }

protected:
	Legalization* m_legalizer{};

private:
	Color m_color{};
    bool m_isAI{};
};

#endif 
