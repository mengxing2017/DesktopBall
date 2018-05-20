#include "ui/desktopball.h"
#include <QApplication>
#include "./ui/showinfo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DesktopBall w;
    w.show();
//    ShowInfo w;
//    w.show();
    return a.exec();
}
