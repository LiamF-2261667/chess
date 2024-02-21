
#include "graphicssquareitem.h"
#include "Board/Square.h"
#include "qbrush.h"
#include "qpen.h"

#include "Game/Game.h"

GraphicsSquareItem::GraphicsSquareItem(Square* square, qreal width, Game* game, QGraphicsItem* parent)
    : QGraphicsRectItem(0, 0, width, width, parent),
    m_square{ square },
    m_game{ game }
{
    Position pos = square->getPosition();

    setPos(pos.column * width, pos.row * width);
    setPen(QColor(OPAQUE_COLOR));

    if ((pos.column + pos.row) % 2 == 0)
        m_color = LIGHT_FIELD_COLOR;
    else
        m_color = DARK_FIELD_COLOR;

    setBrush(m_color);
}

void GraphicsSquareItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_game->updateGamestate(m_square->getPosition());
}

void GraphicsSquareItem::setHighlighted(bool shouldHighlight, bool isSelected) {
    if (shouldHighlight) {
        if (isSelected)
            setBrush(HIGHLIGHT_COLOR);

        else {
            if (m_color == DARK_FIELD_COLOR)
                setBrush(DARK_POSSIBLE_MOVE_COLOR);
            else
                setBrush(LIGHT_POSSIBLE_MOVE_COLOR);
        }
    }

    else
        setBrush(m_color);
}
