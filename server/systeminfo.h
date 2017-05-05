#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H


#include <iostream>
#include <fstream>
#include <pwd.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <vector>
#include <QProcess>

using namespace std;

class systemInfo
{
private:
    vector<float> readCpuStats();

public:
    systemInfo();
    ~systemInfo();
    int getMemory();
    QString getSwap();
    QString getQStringMemory();
    QString getFrequency();
    QString getCpuLoad(double dt);
public slots:
};

#endif // SYSTEMINFO_H
