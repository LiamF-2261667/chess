#include "endscreenwidget.h"
#include "ui_endscreenwidget.h"

EndScreenWidget::EndScreenWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EndScreenWidget)
{
    ui->setupUi(this);
}

EndScreenWidget::~EndScreenWidget()
{
    delete ui;
}

void EndScreenWidget::showWinner(QString winnerName) {
    show();
    ui->label->setText(winnerName.append(" wins!"));
}

void EndScreenWidget::showDraw() {
    show();
    ui->label->setText("Draw!");
}
