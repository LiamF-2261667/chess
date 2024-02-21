
#include "GraphicsPieceItem.h"

#include "Pieces/Piece.h"
#include "Functionality/Color.h"
#include <iostream>

GraphicsPieceItem::GraphicsPieceItem(Piece* piece, qreal squareWidth, QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent),
    m_piece{ piece }
{
    // The texure has to be formatted as: color_t.png (t being the type symbol)
    QString textureName{ TEXTURE_LOCATION };
    textureName += piece->getColor() == Color::WHITE ? "white_" : "black_";
    textureName += piece->getChar();
    textureName += ".png";

    // Get the texture in the right scale
    QPixmap texture{ textureName };
    setScale(TEXTURE_SCALE);
    setPixmap(texture);

    // Center the texture on the square
    setPos((squareWidth - pixmap().width() * TEXTURE_SCALE)/2, (squareWidth - pixmap().height() * TEXTURE_SCALE)/2);
}
