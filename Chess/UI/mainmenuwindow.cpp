#include "mainmenuwindow.h"
#include "ui_mainmenuwindow.h"

#include "Game/Game.h"
#include "Game/GameLoader.h"
#include <iostream>

MainMenuWindow::MainMenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenuWindow)
{
    ui->setupUi(this);

    GameLoader gameloader{};
    if (gameloader.canContinue())
        this->ui->pushButton_2->setEnabled(true);
    else
        this->ui->pushButton_2->setEnabled(false);
}

MainMenuWindow::~MainMenuWindow()
{
    delete game;
    delete ui;
}

/* Start game button */
void MainMenuWindow::on_pushButton_clicked()
{
    hide();
    game = new Game;
    game->startGame(false, this->ui->GamemodeSelection->getGamemode());
}

/* Load game button */
void MainMenuWindow::on_pushButton_2_clicked()
{
    hide();
    game = new Game;
    game->startGame(false, Gamemode::PVP);
}

