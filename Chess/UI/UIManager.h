
#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "mainwindow.h"
#include "Board/Board.h"
#include "promotionselectionwidget.h"
#include "endscreenwidget.h"

class Square;
class Piece;
class Game;
class GameLoader;
class Player;

#include <array>
#include <QObject>

class GraphicsBoardScene;
class GraphicsSquareItem;
class GraphicsPieceItem;

class UIManager : public QObject
{
    Q_OBJECT

public slots:
    void IntializeBoard(Board* board);
    void IntializeSquare(Square* square);
    void IntializePiece(Piece* piece);
    void SetPieceOnSquare(Piece* piece, Square* square);
    void RemovePieceFromSquare(Piece* piece, Square* square);
    void HighlightSquare(Position pos, std::vector<Position> legalPositions);
    void UnHighlightMoves();
    void HighlightPrevMove(Movement move);
    void ShowEndScreen(Player* winner);

public:
    UIManager(Game* game, Board* board, GameLoader* gameloader);

private:
    MainWindow m_mainWindow;
    GraphicsBoardScene* m_boardScene;
    std::array<std::array<GraphicsSquareItem*, Board::WIDTH>, Board::HEIGHT> m_squareItems{};
    std::vector<GraphicsPieceItem*> m_pieceItems{};

    Game* m_game{};
    PromotionSelectionWidget m_promotionWidget{nullptr};
    EndScreenWidget m_endScreen{};

    qreal m_squareWidth{};

    GraphicsPieceItem* getPieceItem(Piece* piece) const;
};

#endif // UIMANAGER_H
