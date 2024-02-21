#include "Board.h"
#include "Functionality/Color.h"
#include "Pieces/Piece.h"
#include <iostream>
#include <string>

Board::~Board()
{
	for (int i = 0; i < m_allPieces.size(); ++i)
		delete m_allPieces[i];
}

// Getters

Piece* Board::getPiece(Position position) const {
	return m_board[position.row][position.column].getPiece();
}

bool Board::isEmpty(Position position) const { 
	return m_board[position.row][position.column].getPiece() != nullptr; 
}

// Methods

/* Initialize all the important data of a board */
void Board::initialize() {
    emit createdBoard(this);

    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < HEIGHT; ++j) {
            m_board[i][j].setPosition(Position(i, j));
            emit createdSquare(&m_board[i][j]);
        }
    }
}

/* Set the position of a piece */
void Board::setPiece(Piece* piece, Position toPosition) {
	Square& square = m_board[toPosition.row][toPosition.column];

	square.setPiece(piece);
}

/* Remove a Piece from a position */
void Board::removePiece(Position position) {
	Square& square = m_board[position.row][position.column];

	if (square.getPiece() == nullptr)
		return;

	// Remove piece from the list of all pieces
	for (int i = 0; i < m_allPieces.size(); ++i) {
		if (m_allPieces[i]->getPosition() == position) {
			delete m_allPieces[i];
			m_allPieces.erase(m_allPieces.begin() + i);
		}
	}

	square.removePiece();
}

/* Move a Piece from its current position to another */
void Board::movePiece(Movement move) {
    Square& fromSquare = m_board[move.from.row][move.from.column];
    Square& toSquare = m_board[move.to.row][move.to.column];

	// If the square is empty, nothing has to be moved
	if (fromSquare.getPiece() == nullptr)
		return;

	// Remove the piece if there is one
    emit removePieceFromSquare(toSquare.getPiece(), &toSquare);
	removePiece(move.to);

    // Move the Piece
    emit setPieceOnSquare(fromSquare.getPiece(), &toSquare);
    fromSquare.getPiece()->setMoved();
	setPiece(fromSquare.getPiece(), move.to);

    // Remove the Piece at the from position
	fromSquare.removePiece();
}

/* Get the Piece from a board position */
Piece* Board::getRandomPiece(Color color) const {
	std::vector<Piece*> pieces{};

	for (Piece* piece : m_allPieces) {
		if (piece->getColor() == color)
			pieces.push_back(piece);
	}

	int randPieceNr = std::rand() % pieces.size();
	return pieces[randPieceNr];
}

/* Create a piece on the board */
void Board::createPiece(Piece* piece, Position startPosition) {
	Square& square = m_board[startPosition.row][startPosition.column];
 
	m_allPieces.push_back(piece);
	square.setPiece(m_allPieces[m_allPieces.size() - 1]);

    emit setPieceOnSquare(piece, &square);
}

/* Get the Piece* of the king with a given color */
Piece* Board::getKing(Color color) const {
	// Go over all pieces
	for (int i = 0; i < m_allPieces.size(); ++i) {

		// If the piece is a king of the current color
		if (m_allPieces[i]->getColor() == color) {
			if (tolower(m_allPieces[i]->getChar()) == 'k') {
				return m_allPieces[i];
			}
		}
	}

	return nullptr;
}

void Board::promotePiece(Piece* oldPiece, Piece* newPiece)
{
    Position pos = oldPiece->getPosition();
    Square* square = &m_board[pos.row][pos.column];

    emit removePieceFromSquare(oldPiece, square);

    removePiece(pos);
    createPiece(newPiece, pos);

    emit setPieceOnSquare(newPiece, square);
}
