#include "AI.h"
#include "Board/Board.h"
#include "Pieces/Piece.h"

// Methods

/* Get a Movement this is legal from the AI */
Movement AI::getMove() {
	// A list of al legal toPositions
	std::vector<Position> legalMoves{};

	Position fromPos{};
	int randMoveNr{};

	// Keep looking for a new move until there is atleast 1 legal move from the selected position
	while (legalMoves.size() == 0) {
		// Get random fromPosition
		Piece* selectedPawn = m_board->getRandomPiece(Player::getColor());
		fromPos = selectedPawn->getPosition();

		// Get all possible moves from the fromPosition
        legalMoves = m_legalizer->getLegalMoves(fromPos, Player::getColor(), true);
        std::size_t maxMoveCount = legalMoves.size();
		if (maxMoveCount != 0)
			randMoveNr = std::rand() % maxMoveCount;
	}

	// Return a random legal move
	return Movement(fromPos, legalMoves.at(randMoveNr));
}

/* Get a random promotion for a pawn */
Type AI::getPromote()
{
    std::vector<Type> pieces{ Type::QUEEN, Type::ROOK, Type::BISHOP, Type::KNIGHT };

    /* Choose a random piece */
    std::size_t maxPieces = pieces.size();
    int randIndex = std::rand() % maxPieces;

    return pieces[randIndex];
}
