#ifndef GAME_H
#define GAME_H

#include "Board/Board.h"
#include "Player/Player.h"
#include "Legalization.h"
#include "History.h"
#include "GameLoader.h"
#include "Functionality/Gamemode.h"

#include "UI/UIManager.h"

#include <vector>
#include <QObject>

class Game : public QObject
{
    Q_OBJECT

public:
	~Game(); // Deconstructor
	
    void startGame(bool continueGame, Gamemode gamemode); // Setup game
    void updateInputstate();
    void updateGamestate(Position pos);

    void doPromote(Type pieceType, Movement move);

signals:
    void selectedSquare(Position pos, std::vector<Position> legalPositions);
    void executedMove(Movement move);
    void aiMoved(Movement move);
    void playerChanged(Color currColor);
    void requestPromotion();
    void gameFinished(Player* winner);

private:
	History m_history{};
    Board m_board{ &m_history };
    GameLoader m_initGame{ &m_board };
    Legalization m_legalizer{ &m_board, &m_history };

    UIManager m_uimanager{ this, &m_board, &m_initGame };

	Player* m_playerWhite{};
	Player* m_playerBlack{};

	Player* m_currentPlayer{};
	Player* m_winner{};

	Gamemode m_gamemode{ Gamemode::NONE };

    bool takingInput{ true };
    enum class Inputstate{ ASK_FROM, ASK_TO };
    Inputstate m_inputstate{ Inputstate::ASK_FROM };

    Movement m_move{};
    int m_turnSwitchesSinceGamestateUpdate{};

    void initializeGamemode();
    bool canMove(); // Check if the current player can move

    void delay(qreal time);

    void executeTurn(Movement move);
	void doMove(Movement move);
	void doEnPassant(Movement move);
    void doCastle(Movement move);
};

#endif
