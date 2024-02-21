#include "gamemodeselectionwidget.h"
#include "ui_gamemodeselectionwidget.h"

GamemodeSelectionWidget::GamemodeSelectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GamemodeSelectionWidget)
{
    ui->setupUi(this);
}

GamemodeSelectionWidget::~GamemodeSelectionWidget()
{
    delete ui;
}

Gamemode GamemodeSelectionWidget::getGamemode() const {
    if (ui->white_ai->isChecked()) {
        if (ui->black_ai->isChecked())
            return Gamemode::AIVAI;
        else
            return Gamemode::AIVP;
    } else {
        if (ui->black_ai->isChecked())
            return Gamemode::PVAI;
        else
            return Gamemode::PVP;
    }
}
