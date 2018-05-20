#include "systeminfo.h"

systemInfo::systemInfo()
{

}

systemInfo::~systemInfo()
{

}
int systemInfo::getMemory()
{
    ifstream stream;
    string str;
    stream.open("/proc/meminfo");
    stream >> str; stream >> str;

    int totalMemory = atoi(str.c_str());
    int freeMemory = 0;
    for (int i = 0 ; i < 3 ; i++)
    {
        stream >> str; stream >> str;
        freeMemory += atoi(str.c_str());
    }
    stream.close();
    int usedMemory = totalMemory - freeMemory;
    int usageRAM = (usedMemory * 100) / totalMemory;
    return usageRAM;
}

QString systemInfo::getSwap()
{
    ifstream stream;
    string str;
    stream.open("/proc/swaps");
    for(int i=0;i<9;i++)
    {
        stream >> str;
    }
    int useSwap = atoi(str.c_str());
    stream.close();
    QString e="";
    const int kb = 1024;
    int gb = useSwap / kb / kb;
    int mb = (useSwap - gb * kb * kb) / kb;
    int qkb = (useSwap-gb*kb*kb-mb*kb);
    if (gb > 0)
    {
       e = QString::number(gb) + QString(" Gb ") + QString::number(mb)+ QString(" Mb ");
    }
    else if(mb>0)
    {
       e = QString::number(mb) + QString(" Mb ")+QString::number(qkb)+ QString(" kb ");
    }
    else
    {
        e=QString::number(qkb)+ QString(" kb ");
    }
    return e;
}

QString systemInfo::getQStringMemory()
{
    ifstream stream;
    string str;
    stream.open("/proc/meminfo");
    stream >> str; stream >> str;

    int totalMemory = atoi(str.c_str());
    int freeMemory = 0;
    for (int i = 0 ; i < 3 ; i++)
    {
        stream >> str; stream >> str;
        freeMemory += atoi(str.c_str());
    }

    int usedMemory = totalMemory - freeMemory;
    QString e="";
    const int kb = 1024;
    int gb = usedMemory / kb / kb;
    int mb = (usedMemory - gb * kb * kb) / kb;
    if (gb > 0)
    {
       e = QString::number(gb) + QString(" Gb ") + QString::number(mb)+ QString(" Mb ");
    }
    else
    {
       e = QString::number(mb) + QString(" Mb ");
    }
    stream.close();
    return e;
}

QString systemInfo::getFrequency()
{
    ifstream stream;
    string str;
    stream.open("/proc/cpuinfo");
    for(int i = 0; i < 16;i++)
        stream >> str;
    getline(stream,str);
    for(int i = 0; i< 10; i++)
        stream >> str;
    stream.close();
    QString e=QString::fromStdString(str) + " MHz";
    return e;
}

QString systemInfo::getCpuLoad(double dt)
{
    vector<float> stats1 = readCpuStats();
    QProcess::execute("sleep",QStringList() << QString::number(dt));
    vector<float> stats2 = readCpuStats();

    int size1 = stats1.size();
    int size2 = stats2.size();

    if (!size1 || !size2 || size1 != size2) return "2%";
    for (int i = 0; i < size1; ++i)
        stats2[i] -= stats1[i];

    int sum = 1;

    for (int i = 0; i < size1; ++i)
        sum += stats2[i];

    int load = 100 - (stats2[size2 - 1] * 100 / sum);
    return QString::number(load)+"%";
}

vector<float> systemInfo::readCpuStats()
{
    vector<float> ret;
    int val;
    string tmp;
    ifstream stat_file("/proc/stat");

    stat_file >> tmp;
    for (int i = 0; i < 4; ++i)
    {
        stat_file >> val;
        ret.push_back(val);
    }

    stat_file.close();
    return ret;
}

