
#include <QApplication>
#include "MainMenuWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainMenuWindow launcher{};
    launcher.show();

    return a.exec();
}
