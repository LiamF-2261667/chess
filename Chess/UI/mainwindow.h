
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>

#include "Functionality/Color.h"

class GraphicsBoardScene;
class QGraphicsView;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    // Constructor
    MainWindow(QWidget *parent = nullptr);

    // Destructor
    ~MainWindow();

    // Setters
    void SetBoardScene(GraphicsBoardScene* boardScene);

    // Getters
    QGraphicsView* GetQGraphicsView() const { return ui->graphicsView; }

public slots:
    void SetCurrentPlayer(Color color);

private:
    Ui::MainWindow *ui;
    GraphicsBoardScene* m_boardScene{};
};

#endif // MAINWINDOW_H
