#ifndef AI_H
#define AI_H

#include "Player.h"
#include "Game/Legalization.h"
#include "Functionality/Color.h"
#include "Functionality/Type.h"
#include "Functionality/Movement.h"

#include <vector>

class AI : public Player
{
public:
	// Constructor
    AI(Color color, const Board* board, Legalization* legalizer) : Player(color, legalizer, true), m_board{ board } { }

	// Methods
    Movement getMove() override;
    Type getPromote() override;

private:
	const Board* m_board{};
};

#endif
