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
public:
    systemInfo();
    ~systemInfo();
//    void getInfo();
    int getCpuLoad(double dt);
    int getMemory();
    vector<float> readCpuStats();
    QString totalMemory();
public slots:
    void getInfo();
};

#endif // SYSTEMINFO_H
