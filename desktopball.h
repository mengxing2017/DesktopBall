#ifndef DESKTOPBALL_H
#define DESKTOPBALL_H

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

#define RED  ":img/red.png"
#define YELLOW  ":img/yellow.png"
#define GREEN  ":img/green.png"

#include "./ui/showinfo.h"
#include "./server/netspeed.h"
#include "./server/systeminfo.h"

class DesktopBall : public QWidget
{
    Q_OBJECT

public:
    DesktopBall(QWidget *parent = 0);
    ~DesktopBall();
private:
    void paintEvent(QPaintEvent *);
    int memused;
    QString upspeed;
    QString downspeed;
    ShowInfo *w;

    netSpeed *netspeed;
    systemInfo *systeminfo;

private slots:
    void timeout();
    void openmoniter();
private:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void contextMenuEvent(QContextMenuEvent *);

//    void getnetspeed();//可独立使用，加返回值即可
//    void getmemused();//同上
    void poscheck();

    QProcess *pro;
    QTimer *timer;
    QRegularExpression reg;
    qint64 oup,odown;
    QPoint oldpos;
    bool mousepressed;
//    QSystemTrayIcon *trayIcon;//托盘图标
    QAction *tuichu;
    QAction *moniter;
};

#endif // DESKTOPBALL_H
