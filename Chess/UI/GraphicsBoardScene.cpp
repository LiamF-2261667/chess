
#include "GraphicsBoardScene.h"
#include "Board/Board.h"

GraphicsBoardScene::GraphicsBoardScene(Board* board, QObject* parent)
    : QGraphicsScene(parent),
    m_board{ board }
{

}

