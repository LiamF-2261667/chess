
#include "UIManager.h"

#include "Board/Square.h"
#include "Pieces/Piece.h"
#include "Game/GameLoader.h"

#include "mainwindow.h"
#include "GraphicsBoardScene.h"
#include "GraphicsSquareItem.h"
#include "GraphicsPieceItem.h"
#include "promotionselectionwidget.h"
#include "endscreenwidget.h"
#include "Game/Game.h"

#include <iostream>


UIManager::UIManager(Game* game, Board* board, GameLoader* gameloader)
    : m_game{game}, m_promotionWidget{game}
{
    m_mainWindow.show();

    QObject::connect(board, &Board::createdBoard, this, &UIManager::IntializeBoard);

    QObject::connect(gameloader, &GameLoader::createdPiece, this, &UIManager::IntializePiece);

    QObject::connect(game, &Game::selectedSquare, this, &UIManager::HighlightSquare);
    QObject::connect(game, &Game::executedMove, this, &UIManager::UnHighlightMoves);
    QObject::connect(game, &Game::aiMoved, this, &UIManager::UnHighlightMoves);
    QObject::connect(game, &Game::executedMove, this, &UIManager::HighlightPrevMove);
    QObject::connect(game, &Game::aiMoved, this, &UIManager::HighlightPrevMove);
    QObject::connect(game, &Game::playerChanged, &m_mainWindow, &MainWindow::SetCurrentPlayer);
    QObject::connect(game, &Game::requestPromotion, &m_promotionWidget,
                     &PromotionSelectionWidget::GetPromotion);
    QObject::connect(game, &Game::gameFinished, this, &UIManager::ShowEndScreen);
}

void UIManager::IntializeBoard(Board* board) {
    m_boardScene = new GraphicsBoardScene{ board };
    m_mainWindow.SetBoardScene(m_boardScene);

    QObject::connect(board, &Board::createdSquare, this, &UIManager::IntializeSquare);
    QObject::connect(board, &Board::setPieceOnSquare, this, &UIManager::SetPieceOnSquare);
    QObject::connect(board, &Board::removePieceFromSquare, this, &UIManager::RemovePieceFromSquare);
}

void UIManager::IntializeSquare(Square* square) {
    Position pos{ square->getPosition() };
    m_squareWidth =  m_mainWindow.GetQGraphicsView()->width() / Board::WIDTH;

    m_squareItems[pos.row][pos.column] = new GraphicsSquareItem{square, m_squareWidth, m_game};

    if (m_boardScene == nullptr) {
        std::cerr << "Cannot intialize square before initializing board.\n";
    } else {
        m_boardScene->addItem(m_squareItems[pos.row][pos.column]);
    }
}

void UIManager::IntializePiece(Piece* piece) {
    m_pieceItems.push_back(new GraphicsPieceItem{piece, m_squareWidth});
}

void UIManager::SetPieceOnSquare(Piece* piece, Square* square) {
    GraphicsPieceItem* currPieceItem{ getPieceItem(piece) };
    GraphicsSquareItem* toSquareItem{ m_squareItems[square->getPosition().row][square->getPosition().column] };

    if (currPieceItem != nullptr)
        currPieceItem->setParentItem(toSquareItem);
    else {
        IntializePiece(piece);
        currPieceItem = getPieceItem(piece);
        currPieceItem->setParentItem(toSquareItem);
    }
}

void UIManager::RemovePieceFromSquare(Piece* piece, Square* square) {
    if (piece == nullptr) return;

    GraphicsPieceItem* currPieceItem{ getPieceItem(piece) };

    if (currPieceItem != nullptr) {
        currPieceItem->setParentItem(nullptr);
        delete currPieceItem;
    }
}

GraphicsPieceItem* UIManager::getPieceItem(Piece* piece) const {
    for (int i = 0; i < m_pieceItems.size(); ++i) {
        if (m_pieceItems[i] == nullptr) continue;

        if (m_pieceItems[i]->getPiece() == piece)
            return m_pieceItems[i];
    }

    return nullptr;
}

void UIManager::HighlightSquare(Position pos, std::vector<Position> legalPositions) {
    m_squareItems[pos.row][pos.column]->setHighlighted(true, true);

    for (Position& currPos : legalPositions) {
        m_squareItems[currPos.row][currPos.column]->setHighlighted();
    }
}

void UIManager::UnHighlightMoves(){
    for (int i = 0; i < m_squareItems.size(); ++i) {
        for (int j = 0; j < m_squareItems[i].size(); ++j) {
            m_squareItems[i][j]->setHighlighted(false);
        }
    }
}

void UIManager::HighlightPrevMove(Movement move) {
    if (move.from == move.to)
        return;

    m_squareItems[move.from.row][move.from.column]->setHighlighted(true, true);
    m_squareItems[move.to.row][move.to.column]->setHighlighted(true, true);
}

void UIManager::ShowEndScreen(Player* winner) {

    if (winner == nullptr)
        m_endScreen.showDraw();
    else {
        if (winner->getColor() == Color::WHITE)
            m_endScreen.showWinner("White");
        else
            m_endScreen.showWinner("Black");
    }

    m_mainWindow.show();
}
