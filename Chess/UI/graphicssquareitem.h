
#ifndef GRAPHICSSQUAREITEM_H
#define GRAPHICSSQUAREITEM_H


#include <QGraphicsRectItem>

class QMouseEvent;

class Square;
class Game;

class GraphicsSquareItem : public QGraphicsRectItem
{
public:
    GraphicsSquareItem(Square* square, qreal width, Game* game, QGraphicsItem* parent = nullptr);

    using QGraphicsRectItem::mousePressEvent;
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

    void setHighlighted(bool shouldHighlight = true, bool isSelected = false);

private:
    const QColor
        DARK_FIELD_COLOR{ 166, 110, 73 },
        LIGHT_FIELD_COLOR{ 232, 205, 172 },
        OPAQUE_COLOR{0, 0, 0, 0},
        DARK_POSSIBLE_MOVE_COLOR{ 217, 56, 30 },
        LIGHT_POSSIBLE_MOVE_COLOR{ 252, 83, 56 },
        HIGHLIGHT_COLOR{ 235, 220, 110 };

    QColor m_color;

    Square* m_square{};
    Game* m_game{};
};

#endif // GRAPHICSSQUAREITEM_H
