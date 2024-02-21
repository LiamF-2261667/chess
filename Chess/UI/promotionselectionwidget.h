#ifndef PROMOTIONSELECTIONWIDGET_H
#define PROMOTIONSELECTIONWIDGET_H

#include <QWidget>
#include <array>

class QGraphicsSceneMouseEvent;
class Game;

namespace Ui {
class PromotionSelectionWidget;
}

class PromotionSelectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PromotionSelectionWidget(Game* game, QWidget *parent = nullptr);
    ~PromotionSelectionWidget();

public slots:
    void GetPromotion();

private slots:
    void on_queen_clicked();
    void on_rook_clicked();
    void on_bishop_clicked();
    void on_knight_clicked();

private:
    Ui::PromotionSelectionWidget *ui;

    Game* m_game{};

};

#endif // PROMOTIONSELECTIONWIDGET_H
