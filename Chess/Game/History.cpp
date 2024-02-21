#include "History.h"
#include <iostream>
#include <string>

/**
* Get the last move from the history 
* Returns: Movement((0,0), (0,0)) if no history
*/
Movement History::getLastMove() const {
	if (m_moves.size() > 0)
		return m_moves[m_moves.size() - 1];

	return Movement();
}
