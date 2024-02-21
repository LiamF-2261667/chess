#include "Square.h"
#include "Pieces/Piece.h"

void Square::setPiece(Piece* piece) {
	m_piece = piece;

	if (piece != nullptr)
		m_piece->setPosition(m_position);
}

void Square::removePiece() {
	m_piece = nullptr;
}
