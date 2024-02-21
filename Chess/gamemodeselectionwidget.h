#ifndef GAMEMODESELECTIONWIDGET_H
#define GAMEMODESELECTIONWIDGET_H

#include <QWidget>
#include "Functionality/Gamemode.h"

namespace Ui {
class GamemodeSelectionWidget;
}

class GamemodeSelectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GamemodeSelectionWidget(QWidget *parent = nullptr);
    ~GamemodeSelectionWidget();

    Gamemode getGamemode() const;

private:
    Ui::GamemodeSelectionWidget *ui;
};

#endif // GAMEMODESELECTIONWIDGET_H
