#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <vector>
#include "Functionality/Position.h"
#include "Functionality/Movement.h"
#include "Square.h"
#include "Game/History.h"
#include "Functionality/Color.h"

#include <QObject>

class UIManager;
class Piece;

class Board : public QObject
{
    Q_OBJECT

public:
	// Dimensions of the board
	const static int WIDTH{ 8 }, HEIGHT{ 8 };

	// Constructor
    Board(History* history) : m_history{ history } { }
	~Board();

	// Getters
	Piece* getPiece(Position position) const;
	bool isEmpty(Position position) const;

	// Methods
    void initialize();

	void setPiece(Piece* piece, Position toPosition);
	void removePiece(Position position);
    void movePiece(Movement move);
    void promotePiece(Piece* piece, Piece* newPiece);

	void createPiece(Piece* piece, Position startPosition);

	Piece* getRandomPiece(Color color) const;

	Piece* getKing(Color color) const;

signals:
    void createdBoard(Board* board);
    void createdSquare(Square* square);
    void setPieceOnSquare(Piece* piece, Square* square);
    void removePieceFromSquare(Piece* piece, Square* square);

private:
	std::array<std::array<Square, WIDTH>, HEIGHT> m_board{};
	std::vector<Piece*> m_allPieces{};
	History* m_history{};

	const static char UPPER_OFFSET{ 'A' - 'a' };
};

#endif
