#include "Game.h"

#include "Functionality/Position.h"
#include "Player/AI.h"
#include "Pieces/Piece.h"

#include "Pieces/Queen.h"
#include "Pieces/Bishop.h"
#include "Pieces/Rook.h"
#include "Pieces/Knight.h"

#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <QObject>
#include <QTime>

void Game::startGame(bool continueGame, Gamemode gamemode)
{
    // Start randomizer seed
    std::srand(std::time(nullptr));

    // Start the board + graphics
    m_board.initialize();

    if (continueGame) {
        m_initGame.loadGame();
        m_gamemode = m_initGame.getGamemode();
    }

    else {
        m_initGame.newGame();
        m_gamemode = gamemode;
    }

    initializeGamemode();

    if (continueGame)
        (m_initGame.getStartingColor() == Color::WHITE) ? m_currentPlayer = m_playerWhite : m_currentPlayer = m_playerBlack;
    else
        m_currentPlayer = m_playerWhite;

    m_legalizer.setKing(m_board.getKing(Color::WHITE));
    m_legalizer.setKing(m_board.getKing(Color::BLACK));

    // If the first player is an AI, start with an arbitrary gamestate update
    if (m_currentPlayer->isAI()) {
        m_inputstate = Inputstate::ASK_TO;
        updateGamestate(Position(0, 0));
    }
}

/* Setup the players for the corresponding gamemode */
void Game::initializeGamemode() {
	// Setup the gamemmode
	if (m_gamemode == Gamemode::PVAI) {
		m_playerWhite = new Player( Color::WHITE, &m_legalizer);
        m_playerBlack = new AI( Color::BLACK, &m_board, &m_legalizer );
	}
	else if (m_gamemode == Gamemode::AIVP) {
        m_playerWhite = new AI(Color::WHITE, &m_board, &m_legalizer);
		m_playerBlack = new Player(Color::BLACK, &m_legalizer);
	}
	else if (m_gamemode == Gamemode::AIVAI) {
        m_playerWhite = new AI(Color::WHITE, &m_board, &m_legalizer);
        m_playerBlack = new AI(Color::BLACK, &m_board, &m_legalizer);
	}

	else { /* PVP */
		m_playerWhite = new Player(Color::WHITE, &m_legalizer);
		m_playerBlack = new Player(Color::BLACK, &m_legalizer);
	}
}

// deconstructor
Game::~Game() {
	delete m_playerWhite;
    delete m_playerBlack;
}

bool Game::canMove()
{
    for (int row = 0; row < m_board.HEIGHT; ++row) {
        for (int column = 0; column < m_board.WIDTH; ++column) {
            Piece* currPiece = m_board.getPiece(Position(row, column));

			if (currPiece == nullptr)
				continue;

			if (currPiece->getColor() != m_currentPlayer->getColor())
				continue;

			std::vector<Position> legalMoves = m_legalizer.getLegalMoves(Position(row, column), m_currentPlayer->getColor(), true);
			if (legalMoves.size() > 0) {
				if (m_history.getMoveCount() >= 500) /* Band-aid fix for draws */
					return false;
				return true;
			}
		}
	}
	return false;
}

void Game::executeTurn(Movement move)
{
    bool firstExecution = true;

    while (m_currentPlayer->isAI() || firstExecution) {
        if (!takingInput) return;

        firstExecution = false;

        if (m_currentPlayer->isAI()) {
            delay(1);
            move = m_currentPlayer->getMove();
            m_move = move;
        }

        else {
            /* Check whether move is legal */
            if (!m_legalizer.isLegal(move, m_currentPlayer->getColor(), false, true)) {
                m_move = Movement(); /* Clear move if it's not legal */
                return;
            }
        }

        /* Save the current gamestate */
        if (m_gamemode != Gamemode::AIVAI)
            m_initGame.saveGame(m_currentPlayer->getColor(), m_gamemode);

        /* Execute move */
        doMove(move);
        if (m_currentPlayer->isAI()) emit aiMoved(move);

        /* Swap players */
        m_turnSwitchesSinceGamestateUpdate++;
        (m_currentPlayer->getColor() == Color::WHITE) ? m_currentPlayer = m_playerBlack : m_currentPlayer = m_playerWhite;
        emit playerChanged(m_currentPlayer->getColor());

        // If the current player cannot move anymore, test if it's checkmate of a draw.
        if (m_legalizer.isCheck(m_currentPlayer->getColor()) && !canMove()) {
            (m_currentPlayer->getColor() == Color::WHITE) ? m_winner = m_playerBlack : m_winner = m_playerWhite;;
            emit gameFinished(m_winner);
        }
        else if (!canMove()) {
            emit gameFinished(nullptr);
            m_initGame.endGame();
        }
    }
}

void Game::doMove(Movement move)
{
    /* Edge case: Execute en-passant */
    if (m_legalizer.isEnPassant(move)) {
        doEnPassant(move);
    }
    /* Edge case: Execute castle */
    else if (m_legalizer.isCastle(move)) {
        doCastle(move);
    }
    /* Execute normal move */
    else {
        m_board.movePiece(move);
    }

    /* Promote if necessary */
    if (m_legalizer.isPromotion(move)) {
        if (m_currentPlayer->isAI())
            doPromote(m_currentPlayer->getPromote(), move);
        else {
            emit requestPromotion();
            takingInput = false;
        }
    }

    /* Record move in history */
    m_history.addMove(move);
}

/* Execute en-passant */
void Game::doEnPassant(Movement move)
{
	Position attackedPos{ move.from.row, move.to.column };

    m_board.removePiece(attackedPos);
    m_board.movePiece(move);
}

void Game::doCastle(Movement move)
{
	int deltaColumn = move.to.column - move.from.column;
	Position rookTile{ move.from.row, (deltaColumn < 0) ? 0 : Board::WIDTH - 1 };
	Position toRookTile{ move.from.row, (deltaColumn < 0) ? move.from.column - 1 : move.from.column + 1 };

    m_board.movePiece(Movement(rookTile, toRookTile));
    m_board.movePiece(move);
}

/* Promote a pawn */
void Game::doPromote(Type pieceType, Movement move)
{
    Piece* piece;
    piece = m_board.getPiece(Position(m_move.to.row, m_move.to.column));

	Color color{ piece->getColor() };
    Piece* promotedPiece{};

	/* Promote piece */
	if (pieceType == Type::QUEEN) {
        promotedPiece = new Queen(color, m_move.to);
	}
	else if (pieceType == Type::ROOK) {
        promotedPiece = new Rook(color, m_move.to);
	}
	else if (pieceType == Type::BISHOP) {
        promotedPiece = new Bishop(color, m_move.to);
	}
	else if (pieceType == Type::KNIGHT) {
        promotedPiece = new Knight(color, m_move.to);
	}

    m_board.promotePiece(piece, promotedPiece);

    takingInput = true;
    if (m_currentPlayer->isAI())
        executeTurn(move);
}

/* Updates the current state of the game after clicking */
void Game::updateGamestate(Position pos)
{
    if (!takingInput) return;

    m_turnSwitchesSinceGamestateUpdate = 0;

    // Update for a player
    if (m_inputstate == Inputstate::ASK_FROM) {
        if (!m_legalizer.hasPiece(pos)) return;

        std::vector<Position> legalPositions{ m_legalizer.getLegalMoves(pos, m_currentPlayer->getColor(), true) };

        // Only if the selected square has legal moves, then should a square be selected
        if (legalPositions.size() > 0) {
            emit selectedSquare(pos, legalPositions);
            m_move.from = pos;
        }

        // Don't update otherwise
        else return;

    } else {
        m_move.to = pos;
        emit executedMove(m_move);

        executeTurn(m_move);
    }

    updateInputstate();

    if (m_turnSwitchesSinceGamestateUpdate == 0)
        // If the move was from your color to your color, select the move.to position instead of canceling the move
        if (m_inputstate == Inputstate::ASK_FROM && m_legalizer.isOwnPiece(pos, m_currentPlayer->getColor())) {
            updateGamestate(pos);
        }
}

void Game::updateInputstate()
{
    if (m_inputstate == Inputstate::ASK_TO) {
        m_inputstate = Inputstate::ASK_FROM;
    }
    else
        m_inputstate = Inputstate::ASK_TO;

}

void Game::delay(qreal time)
{
    QTime delayTime= QTime::currentTime().addSecs(time);
    while (QTime::currentTime() < delayTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
