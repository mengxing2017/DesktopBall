#ifndef NETSPEED_H
#define NETSPEED_H

#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>
#include <QProcess>
#include <QRegularExpression>
#include <QAction>
#include <QTimer>
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>
#include <QMenu>
using namespace std;

class netSpeed
{
private:
    qint64 oup,odown;
    QString upspeed = "";
    QString downspeed="";

     QProcess *pro;
public:
    netSpeed();
    ~netSpeed();
    QString getNetUpSpeed();
    QString getNetDownSpeed();
    void reckonNetSpeed();
};

#endif // NETSPEED_H
