#include "GameLoader.h"
#include "Functionality/Position.h"
#include "Functionality/Color.h"
#include "Board/Board.h"

#include "Pieces/Pawn.h"
#include "Pieces/Rook.h"
#include "Pieces/Bishop.h"
#include "Pieces/Knight.h"
#include "Pieces/Queen.h"
#include "Pieces/King.h"

#include <math.h>
#include <iostream>
#include <fstream>
#include <QFile>
#include <QTextStream>
#include <QDir>

// Constructor
GameLoader::GameLoader(Board* board) : m_board{ board } { 
	// Opening the saved board layout file
    std::ifstream file{ m_saveFileLocation.toStdString() };
	if (!file.is_open())
		return;

	// Test if there is a saved game
	std::string buffer{};
	getline(file, buffer);

	m_canContinue = !(buffer.at(0) == '/');
}

/* Create a new piece according to it's symbol */
Piece* GameLoader::loadPiece(char symbol) {
	Position defaultPos{ 0, 0 };

	if (symbol == 'P') return new Pawn(Color::WHITE, defaultPos);
	if (symbol == 'p') return new Pawn(Color::BLACK, defaultPos);

	if (symbol == 'R') return new Rook(Color::WHITE, defaultPos);
	if (symbol == 'r') return new Rook(Color::BLACK, defaultPos);

	if (symbol == 'B') return new Bishop(Color::WHITE, defaultPos);
	if (symbol == 'b') return new Bishop(Color::BLACK, defaultPos);

	if (symbol == 'N') return new Knight(Color::WHITE, defaultPos);
	if (symbol == 'n') return new Knight(Color::BLACK, defaultPos);

	if (symbol == 'Q') return new Queen(Color::WHITE, defaultPos);
	if (symbol == 'q') return new Queen(Color::BLACK, defaultPos);

	if (symbol == 'K') return new King(Color::WHITE, defaultPos);
	if (symbol == 'k') return new King(Color::BLACK, defaultPos);

	return nullptr;
}

/* Read the data formated in a file (assuming it's formatted correctly) */
void GameLoader::readBoard(QFile& file) {
	// Starting read
	std::string readBuffer;
	int boardRow{ 0 };

	// Keep reading until the file ends or all the rows of the board are filled
    while (!file.atEnd() && (boardRow < Board::HEIGHT)) {
        readBuffer = file.readLine();

		// Keep analyzing the line until it ends or the row inside board is full
		int boardColumn{ 0 };
		for (const char symbol : readBuffer) {
			if (boardColumn >= Board::WIDTH)
				continue;

			// Leave an empty space on the board
			if (symbol == '-') {
				boardColumn++;
				continue;
			}

			Piece* newPiece{ loadPiece(symbol) };

			// The symbol is a pieceType
			if (newPiece != nullptr) {
                emit createdPiece(newPiece);

				m_board->createPiece(newPiece, Position(boardRow, boardColumn));
				boardColumn++;
			}
		}

		boardRow++;
	}
	// Finished reading board

    // Read current turn
    readBuffer = file.readLine();
	(readBuffer.at(0) == '0') ? m_startingColor = Color::WHITE : m_startingColor = Color::BLACK;
	(readBuffer.at(2) == '/') ? m_gamemode = Gamemode::NONE : m_gamemode = (Gamemode)(readBuffer.at(2) - '0');
}

/* Save the current board state to the saved_board file */
void GameLoader::saveBoard(QFile& file, Color currentColor, Gamemode gamemode) {
	for (int i = 0; i < Board::HEIGHT; ++i) {
		for (int j = 0; j < Board::WIDTH; ++j) {
			Piece* currPiece = m_board->getPiece(Position(i, j));

			if (currPiece == nullptr)
                QTextStream(&file) << "- ";
			else {
				if (currPiece->getColor() == Color::WHITE)
                    QTextStream(&file) << (char)(currPiece->getChar() + UPPER_OFFSET) << ' ';
				else
                    QTextStream(&file) << currPiece->getChar() << ' ';
			}
		}

        QTextStream(&file) << '\n';
	}
	if (gamemode != Gamemode::NONE)
        QTextStream(&file) << (int)currentColor << ' ' << (int)gamemode << '\n';
	else
        QTextStream(&file) << (int)currentColor << ' ' << '/' << '\n';
}

/* Setup the board for a new game */
void GameLoader::newGame() {
    // Opening the default board layout file
    QFile file{ m_defaultFileLocation };
    QString name = file.fileName();
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    readBoard(file);
}

/* Setup the board to the saved boardstate */
void GameLoader::loadGame() {
    // Opening the saved board layout file
    QFile file{ m_saveFileLocation };
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    readBoard(file);
}

/* Save the current board layout */
void GameLoader::saveGame(Color currentColor, Gamemode gamemode) {
    // Opening the saved board layout file
    QFile file{ m_saveFileLocation };
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    saveBoard(file, currentColor, gamemode);
}

void GameLoader::endGame() {
    // Opening the saved board layout file
    QFile file{ m_saveFileLocation };
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream(&file) << '/';
}
