#include "promotionselectionwidget.h"
#include "ui_promotionselectionwidget.h"

#include "Functionality/Type.h"
#include "Game/Game.h"


PromotionSelectionWidget::PromotionSelectionWidget(Game* game, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PromotionSelectionWidget),
    m_game{game}
{
    ui->setupUi(this);
}

PromotionSelectionWidget::~PromotionSelectionWidget()
{
    delete ui;
}

void PromotionSelectionWidget::GetPromotion()
{
    show();
}

void PromotionSelectionWidget::on_queen_clicked()
{
    m_game->doPromote(Type::QUEEN, Movement());
    ui->queen->setChecked(false);
    hide();
}


void PromotionSelectionWidget::on_rook_clicked()
{
    m_game->doPromote(Type::ROOK, Movement());
    ui->rook->setChecked(false);
    hide();
}


void PromotionSelectionWidget::on_bishop_clicked()
{
    m_game->doPromote(Type::BISHOP, Movement());
    ui->bishop->setChecked(false);
    hide();
}


void PromotionSelectionWidget::on_knight_clicked()
{
    m_game->doPromote(Type::KNIGHT, Movement());
    ui->knight->setChecked(false);
    hide();
}

