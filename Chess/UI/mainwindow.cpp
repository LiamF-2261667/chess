
#include "mainwindow.h"

#include "GraphicsBoardScene.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetBoardScene(GraphicsBoardScene* boardScene) {
    m_boardScene = boardScene;
    ui->graphicsView->setScene(m_boardScene);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MainWindow::SetCurrentPlayer(Color color) {
    if (color == Color::WHITE)
        ui->currentColor->setStyleSheet("QPlainTextEdit { background-color : rgb(235, 235, 235); }");
    else
        ui->currentColor->setStyleSheet("QPlainTextEdit { background-color : rgb(43, 43, 43); }");
}
