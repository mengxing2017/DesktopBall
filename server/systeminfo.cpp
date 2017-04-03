#include "systeminfo.h"

systemInfo::systemInfo()
{

}

systemInfo::~systemInfo()
{

}
void systemInfo::getInfo()
{
    string str;
    ifstream ver("/proc/version");
    ver>>str;ver>>str;ver>>str;
//    kernel->setText("Kernel: " + QString::fromStdString(str));

    ifstream stream("/proc/sys/kernel/hostname");
    getline(stream,str);
//    hostname->setText("Hostname: " + QString::fromStdString(str));

    uid_t uid = geteuid();
    passwd *pw = getpwuid(uid);
//    user->setText("Username: " + QString::fromStdString(pw->pw_name));

    struct sysinfo o;
    sysinfo(&o);
    long up = o.uptime;
    const int th = 60;
    int hour = up/th/th;
    int min = (up - hour*th*th) / th;
    int sec =  ((up - hour*th*th) - min*th);

    QString e = QString::number(hour) +  QString(" h. ") + QString::number(min) + QString(" m. ")
                + QString::number(sec) + QString(" s.");
//    uptime->setText("Uptime: " + e);
    stream.close();

    stream.open("/proc/cpuinfo");
    for(int i = 0; i < 16;i++)
        stream >> str;

    getline(stream,str);
//    proc->setText("Processor: " + QString::fromStdString(str));
    for(int i = 0; i< 10; i++)
        stream >> str;

//    freq->setText("Frequency: " + QString::fromStdString(str) + " MHz");

//    cpubar->setValue(getCpuLoad(0.3));
    stream.close();


}




QString systemInfo::totalMemory()
{
    ifstream stream("/proc/meminfo");

    stream.close();
}

int systemInfo::getCpuLoad(double dt)//
{
    vector<float> stats1 = readCpuStats();
    QProcess::execute("sleep",QStringList() << QString::number(dt));
    vector<float> stats2 = readCpuStats();

    int size1 = stats1.size();
    int size2 = stats2.size();

    if (!size1 || !size2 || size1 != size2) return 2;
    for (int i = 0; i < size1; ++i)
        stats2[i] -= stats1[i];

    int sum = 1;

    for (int i = 0; i < size1; ++i)
        sum += stats2[i];

    int load = 100 - (stats2[size2 - 1] * 100 / sum);
    return load;
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

    int usedMemory = totalMemory - freeMemory;
    int usageRAM = (usedMemory * 100) / totalMemory;
    return usageRAM;
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
