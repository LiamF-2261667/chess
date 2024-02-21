#include "Legalization.h"
#include "Functionality/Color.h"
#include "Pieces/Piece.h"
#include "Board/Board.h"

#include <iostream>

// Setters
void Legalization::setKing(const Piece* king) {
	if (king->getColor() == Color::WHITE)
		m_whiteKing = king;
	else
		m_blackKing = king;
}

// Methods

bool Legalization::hasPiece(Position pos) {
    return m_board->getPiece(pos) != nullptr;
}

bool Legalization::isOwnPiece(Position pos, Color currColor) {
    if (!hasPiece(pos)) return false;

    return m_board->getPiece(pos)->getColor() == currColor;
}

bool Legalization::isLegalFromPosition(Movement move, Color currColor, bool showInfo) const
{
	Piece* selectedPiece = m_board->getPiece(move.from);

	// If there isn't a piece on the selected square
	if (selectedPiece == nullptr) {
		if (showInfo)
			std::cout << "There isn't a piece on the selected square!\n";
		return false;
	}

	// If the selected piece isn't of the players color
	if (selectedPiece->getColor() != currColor) {
		if (showInfo)
			std::cout << "This pawn belongs to the other player!\n";
		return false;
	}

	return true;
}

bool Legalization::isLegalToPosition(Movement move, Color currColor, bool showInfo) const
{
	bool isAttacking{ false };

	// Get square information
	Piece* selectedPiece = m_board->getPiece(move.from);
	Piece* targetPiece = m_board->getPiece(move.to);

	// If the player is taking its own piece
	if (targetPiece != nullptr) {
		if (targetPiece->getColor() == currColor) {
			if (showInfo)
				std::cout << "You cannot take your own pawns!\n";
			return false;
		}
		isAttacking = true;
	}

	// If player is trying to move through a blocked path
    if (!selectedPiece->canJump() && isPieceInWay(move)) {
		if (showInfo)
			std::cout << "There is a piece in the way!\n";
		return false;
	}

	// If the piece-specific legality is illegal
	if (!selectedPiece->isLegal(move, m_history->getLastMove(), isAttacking, showInfo)) {

		/* If not a legal move (standard), check whether the king is trying to castle */
        if (isCastle(move)) {
            if (isLegalCastle(move, currColor)) {
                return true;
            }
		}

		return false;
	}

	return true;
}

/* Test if a piece can take the enemy king */
bool Legalization::canTakeEnemyKing(const Piece* piece) const {
	Color color{ piece->getColor() };
	Color enemyColor{ (Color)(1 - (int)color) };

	// Get the enemy king position
	const Piece* enemyKing{ m_whiteKing };
	if (enemyKing->getColor() != enemyColor)
		enemyKing = m_blackKing;

	Position enemyKingPos{ enemyKing->getPosition() };

	// Test if the piece has a legal move ending in the enemy king position
	for (const auto& toPos : getLegalMoves(piece->getPosition(), color)) {
		if (toPos == enemyKingPos)
			return true;
	}

	return false;
}

/* Is a player being checked by the other player */
bool Legalization::isCheck(Color color) const {

	// Go over every square
	for (int row = 0; row < m_board->HEIGHT; ++row) {
		for (int column = 0; column < m_board->WIDTH; ++column) {
			// Get the possible piece
			Piece* currPiece = m_board->getPiece(Position(row, column));

			// If there isn't a piece on this position, it cannot check a king
			if (currPiece == nullptr)
				continue;

			// If the piece is of its own color, it cannot check its own king
			if (currPiece->getColor() == color)
				continue;

			// Check if the enemy can take the king
			if (canTakeEnemyKing(currPiece))
				return true;
		}
	}

	return false;
}

Piece* Legalization::simulateMove(Movement move) const {
	Piece* pieceToMove{ m_board->getPiece(move.from) };
	Piece* pieceToReplace{ m_board->getPiece(move.to) };

	m_board->setPiece(nullptr, move.from);
	m_board->setPiece(pieceToMove, move.to);

	return pieceToReplace;
}

void Legalization::undoSimulatedMove(Movement move, Piece* pieceToReset) const {
	Piece* pieceToMove{ m_board->getPiece(move.to) };

	m_board->setPiece(pieceToMove, move.from);
	m_board->setPiece(pieceToReset, move.to);
}

/* Is a move legal according to the chess ruleset */
bool Legalization::isLegal(Movement move, Color currColor, bool showInfo, bool needToLookForCheck) const {
	// Test if the move is inbounds
	if (!isInbounds(move.from) || !isInbounds(move.to)) {
		if (showInfo)
			std::cout << "A position isn't on the board!\n";
		return false;
	}

	// If the selected piece to move is legal
	if (!isLegalFromPosition(move, currColor, showInfo)) {
		return false;
	}

	// If the selected square to move to is legal 
	if (!isLegalToPosition(move, currColor, showInfo)) {
		return false;
	}

	// Simulate the move to check if you'd be put to check
	if (needToLookForCheck) {
		Piece* pieceToReset = simulateMove(move);
		bool check{ isCheck(currColor) };
		undoSimulatedMove(move, pieceToReset);

		if (check) {
			if (showInfo)
				std::cout << "This move results in a check!\n";
			return false;
		}
	}

	return true;
}

bool Legalization::isPieceInWay(Movement move) const
{
	/* Calculating necessary variables */
	Position fromPos{ move.from }, toPos{ move.to };
	Position currentPos{ fromPos };

	int deltaRow{ toPos.row - fromPos.row };
	int deltaColumn{ toPos.column - fromPos.column };

	/* Base case: There can't be a pawn in the way if there isn't even a gap between positions */
	if ((deltaRow > -2 && deltaRow < 2) && (deltaColumn > -2 && deltaColumn < 2))
		return false;

	/* Check every tile */
	while (currentPos != toPos) {

		/* Check if there's a piece in the way */
		if (currentPos != fromPos && m_board->getPiece(currentPos) != nullptr) {
			return true;
		}
		/* Get next position in order */
		if (deltaRow != 0 && currentPos.row != toPos.row) {
			currentPos.row += 1 * ((deltaRow < 0) ? -1 : +1);
		}
		if (deltaColumn != 0 && currentPos.column != toPos.column) {
			currentPos.column += 1 * ((deltaColumn < 0) ? -1 : +1);
		}
	}

	return false;
}

bool Legalization::isCastle(Movement move) const
{
	int deltaColumn = move.to.column - move.from.column;
	int deltaRow = move.to.row - move.from.row;

	if (tolower(m_board->getPiece(move.from)->getChar()) != 'k')
		return false;

	if (abs(deltaColumn) != 2)
		return false;

	if (deltaRow != 0)
		return false;

	return true;
}

bool Legalization::isLegalCastle(Movement move, Color currColor) const
{
	int deltaColumn = move.to.column - move.from.column;
	Piece* king = m_board->getKing(currColor);
	Piece* rook = m_board->getPiece(Position(7 - 7 * (int)currColor, (deltaColumn < 0) ? 0 : 7));

	/* There isn't a piece on the position */
	if (king == nullptr || rook == nullptr)
		return false;

	/* Cannot castle if either the king or rook has moved */
	if (king->hasMoved() || rook->hasMoved())
		return false;

	/* Cannot castle if there's a piece between king and rook */
    if (isPieceInWay(Movement(move.from, rook->getPosition())))
		return false;

	/* Simulate if there will be a check that the king is moving through */
	Position simTo{ move.from.row, (deltaColumn < 0) ? move.from.column - 1 : move.from.column + 1 };

	Piece* pieceToReset = simulateMove(Movement(move.from, simTo));
	bool check{ isCheck(currColor) };
	undoSimulatedMove(Movement(move.from, simTo), pieceToReset);

    // Cannot castle if it'd put you in check
	if (check)
		return false;

    // Cannot castle when being checked
    if (isCheck(currColor)) return false;

	return true;
}

/* Test if a position is on the board */
bool Legalization::isInbounds(Position pos) const {
	if (pos.row >= 0 && pos.row < m_board->WIDTH)
		if (pos.column >= 0 && pos.column < m_board->HEIGHT)
			return true;

	return false;
}

/* Get all the legal moves form a starting position */
std::vector<Position> Legalization::getLegalMoves(Position fromPos, Color currColor, bool needToLookForCheck) const {
	// Get the player en selection information
	Piece* selectedPiece = m_board->getPiece(fromPos);

	// If there isn't a piece on the given position, there is no valid move
	if (selectedPiece == nullptr)
		return std::vector<Position>();

	// If the selected piece isn't of the players color, there is no valid move
	if (selectedPiece->getColor() != currColor)
		return std::vector<Position>();

	// Initialize variables
	std::vector<Position> possibleMoves = selectedPiece->getPossibleToPositions();
	std::vector<Position> legalMoves;

	// Check if the move is legal
	for (const auto& toPos : possibleMoves) {
		if (isLegal(Movement(fromPos, toPos), currColor, false, needToLookForCheck))
			legalMoves.push_back(toPos);
	}

	return legalMoves;
}

/* Check whether the chosen move is en-passant */
bool Legalization::isEnPassant(Movement move) const
{
	Piece* fromPiece = m_board->getPiece(Position(move.from.row, move.from.column));
	Piece* toPiece = m_board->getPiece(Position(move.to.row, move.to.column));

	int deltaColumn{ move.to.column - move.from.column };

	if (tolower(fromPiece->getChar()) == 'p' && deltaColumn != 0 && toPiece == nullptr) {
		return true;
	}
	return false;
}

/* Check whether a pawn is allowed to promote */
bool Legalization::isPromotion(Movement move) const
{
	Piece* selectedPiece = m_board->getPiece(Position(move.to.row, move.to.column));
	Color color{ selectedPiece->getColor() };

	/* Check whether the moved piece is a pawn */
	if (tolower(selectedPiece->getChar()) != 'p')
		return false;

	/* Check whether the pawn reached the final row */
	if (move.to.row != (int)color * (Board::HEIGHT - 1))
		return false;

	return true;
}
