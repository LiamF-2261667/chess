#ifndef LEGALIZATION_H
#define LEGALIZATION_H

#include "Functionality/Position.h"
#include "Functionality/Color.h"
#include "Functionality/Movement.h"

#include <vector>

class Board;
class Player;
class Piece;
class History;

class Legalization
{
public:
	// Constructor
	Legalization(Board* board, const History* history) : m_board{ board }, m_history{ history } { }

	// Setters
	void setKing(const Piece* king);

	// Methods
    bool hasPiece(Position pos);
    bool isOwnPiece(Position pos, Color currColor);
	bool isCheck(Color color) const;
	bool isLegal(Movement move, Color currColor, bool showInfo, bool needToLookForCheck = true) const; // Check if a given move is legal
	std::vector<Position> getLegalMoves(Position fromPos, Color currColor, bool needToLookForCheck = false) const;

	bool isCastle(Movement move) const;
	bool isEnPassant(Movement move) const;
	bool isPromotion(Movement move) const;

private:
	bool isLegalFromPosition(Movement move, Color currColor, bool showInfo) const;
	bool isLegalToPosition(Movement move, Color currColor, bool showInfo) const;

	bool canTakeEnemyKing(const Piece* piece) const;
	bool isInbounds(Position pos) const;
    bool isPieceInWay(Movement move) const; // Check if there is a piece in way of movement

	bool isLegalCastle(Movement move, Color currColor) const;

	Piece* simulateMove(Movement move) const;
	void undoSimulatedMove(Movement move, Piece* pieceToReset) const;

	Board* m_board;
	const History* m_history;

	const Piece* m_whiteKing{};
	const Piece* m_blackKing{};
};

#endif
