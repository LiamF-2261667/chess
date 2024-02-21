#ifndef ENDSCREENWIDGET_H
#define ENDSCREENWIDGET_H

#include <QWidget>
#include <QString>

namespace Ui {
class EndScreenWidget;
}

class EndScreenWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EndScreenWidget(QWidget *parent = nullptr);
    ~EndScreenWidget();

    void showWinner(QString winnerName);
    void showDraw();

private:
    Ui::EndScreenWidget *ui;
};

#endif // ENDSCREENWIDGET_H
