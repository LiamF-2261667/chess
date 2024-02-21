#ifndef HISTORY_H
#define HISTORY_H

#include "Functionality/Movement.h"
#include <vector>

class History
{
public:
	// Methods
    Movement getLastMove() const;
    std::size_t getMoveCount() const { return m_moves.size(); };

	void addMove(Movement move) { m_moves.push_back(move); }

private:
	std::vector<Movement> m_moves{};

	const static char BEGIN_ALPHABET_ASCII_OFFSET{ 'a' };
	const static char END_BOARD_ASCII_OFFSET{ '8' };
};

#endif
