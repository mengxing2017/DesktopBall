#ifndef SHOWINFO_H
#define SHOWINFO_H

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

#include "./server/systeminfo.h"
#include "./server/netspeed.h"

class ShowInfo : public QMainWindow
{
    Q_OBJECT
private:
    QLabel *cpuTemperature_Name;
    QLabel *cpuUsage_Name;
    QLabel *memUsage_Name;
    QLabel *hdd_Name;
    QLabel *mainboard_Name;
    QLabel *acpi_Name;
    QLabel *fan_Name;
    QLabel *net_Name;

    QLabel *cpuTemperature;
    QLabel *cpuUsage;
    QLabel *memUsage;
    QLabel *hddTemperature;
    QLabel *mainboardTemperature;
    QLabel *acpiTemperatture;
    QLabel *fanRevolution;
    QLabel *netSpeedShow;

    int coordinateX,coordinateY;
    int memused;
    QString upspeed;
    QString downspeed;

    QTimer *timer;
    netSpeed *netspeed;
    systemInfo *systeminfo;

    void paintEvent(QPaintEvent *);

public:
    explicit ShowInfo(QWidget *parent = 0);
    ~ShowInfo();


    void init_ui();
    void setLabelStyle(QLabel *qlabel, QString Sstyle);
    void setParameter(int x, int y);
signals:

public slots:
    void timeout();
};

#endif // SHOWINFO_H
