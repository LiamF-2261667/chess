#ifndef GAMELOADER_H
#define GAMELOADER_H

#include "Functionality/Color.h"
#include "Functionality/Gamemode.h"

class Board; /* Forward declaration */
class Piece;
class QFile;

#include <QObject>

class GameLoader : public QObject
{
    Q_OBJECT

public:
	// Constructor
    GameLoader(Board* board = nullptr);

	// Methods
	void newGame();
	void loadGame();
	void saveGame(Color currentColor, Gamemode gamemode);
	void endGame();

	bool canContinue() const { return m_canContinue; }
	Gamemode getGamemode() const { return m_gamemode; }

	Color getStartingColor() const { return m_startingColor; }

signals:
    void createdPiece(Piece* piece);

private:
	Board* m_board{};

    const QString m_defaultFileLocation{ "://BoardSetup/default_board.txt" };
    const QString m_saveFileLocation{ "saved_board.txt" };

	Color m_startingColor{};
    bool m_canContinue{false};
	Gamemode m_gamemode{};
	const static char UPPER_OFFSET{ 'A' - 'a' };

	Piece* loadPiece(char symbol);
    void readBoard(QFile& file);
    void saveBoard(QFile& file, Color currentColor, Gamemode gamemode);
};

#endif
