#ifndef SHOWINFO_H
#define SHOWINFO_H

#define CPU_SORT "ps ax -o \"%u %p %C\" -o pmem -o \"%c %a\" --sort=-%cpu|head -16"//包含头
#define MEM_SORT "ps ax -o \"%u %p %C\" -o pmem -o \"%c %a\" --sort=-pmem|head -16"//包含头

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QApplication>
#include <QStyle>
#include <QPalette>
#include <QColor>
#include <QLatin1String>
#include <QPainter>
#include <QLinearGradient>
#include <QString>
#include <QPixmap>
#include <QFont>
#include <QPen>
#include <QBrush>
#include <QTimer>

#include <QVariant>
#include <QAction>
#include <QHeaderView>
#include <QTabWidget>
#include <QWidget>

#include <QHBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QSpacerItem>
#include <QTableWidget>
#include <QProcess>
#include <QDir>


#include "./server/systeminfo.h"
#include "./server/netspeed.h"

class ShowInfo : public QMainWindow
{
    Q_OBJECT
private:
    QLabel *cpuUsage_Name;
    QLabel *memUsage_Name;
    QLabel *cpuFrequency_Name;
    QLabel *net_Name;
    QLabel *swap_Name;
    QLabel *swap;
    QLabel *cpuFrequency;
    QLabel *cpuUsage;
    QLabel *memUsage;
    QLabel *netSpeedShow;

    QTabWidget *tabWidget;
    QWidget *tab_info;
    QWidget *tab_monitor;

    int coordinateX,coordinateY;
    int memused;
    QString upspeed;
    QString downspeed;

    QTimer *timer;
    QTimer *timer2;
    netSpeed *netspeed;
    systemInfo *systeminfo;

    QTableWidget *tableWidget;
    QProcess *process;

    QString cmd;
    QStringList selectedpid;
    QString pressed;
    QStringList selected;
    QStringList listupdate2freshselected;
    bool pidselected(const QString&);
    void paintEvent(QPaintEvent *);

public:
    explicit ShowInfo(QWidget *parent = 0);
    ~ShowInfo();


    void init_ui();
    void initUiMonitot();
    void setLabelStyle(QLabel *qlabel, QString Sstyle);
    void setParameter(int x, int y);

signals:

public slots:
    void timeout_info();
    void getInfo();
};

#endif // SHOWINFO_H
