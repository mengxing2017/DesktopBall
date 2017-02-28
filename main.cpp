#include "desktopball.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DesktopBall w;
    w.show();

    return a.exec();
}
