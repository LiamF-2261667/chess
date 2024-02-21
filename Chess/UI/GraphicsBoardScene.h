
#ifndef GRAPHICSBOARDSCENE_H
#define GRAPHICSBOARDSCENE_H


#include <QGraphicsScene>

class Board;

class GraphicsBoardScene : public QGraphicsScene
{
public:
    GraphicsBoardScene(Board* board, QObject* parent = nullptr);

private:
    Board* m_board{};
};

#endif // GRAPHICSBOARDSCENE_H
