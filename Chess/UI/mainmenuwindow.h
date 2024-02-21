#ifndef MAINMENUWINDOW_H
#define MAINMENUWINDOW_H

#include <QMainWindow>

class Game;

namespace Ui {
class MainMenuWindow;
}

class MainMenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenuWindow(QWidget *parent = nullptr);
    ~MainMenuWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::MainMenuWindow *ui;
    Game* game;
};

#endif // MAINMENUWINDOW_H
