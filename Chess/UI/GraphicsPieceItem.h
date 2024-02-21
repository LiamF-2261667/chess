
#ifndef GRAPHICSPIECEITEM_H
#define GRAPHICSPIECEITEM_H


#include <QGraphicsPixmapItem>
class Piece;


class GraphicsPieceItem : public QGraphicsPixmapItem
{
public:
    GraphicsPieceItem(Piece* piece, qreal squareWidth, QGraphicsItem* parent = nullptr);
    Piece* getPiece() const { return m_piece; }

private:
    const QString TEXTURE_LOCATION{ "://Images/" };
    const qreal TEXTURE_SCALE{ 0.5 };

    Piece* m_piece{};
};

#endif // GRAPHICSPIECEITEM_H
