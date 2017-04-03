#include "desktopball.h"
#include <QApplication>
//#include "showinfo.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DesktopBall w;
    w.show();
//    ShowInfo showinfo;
//    showinfo.show();
    return a.exec();
}
