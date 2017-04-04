#include "showinfo.h"

ShowInfo::ShowInfo(QWidget *parent) : QMainWindow(parent)
{
    netspeed=new netSpeed();
    systeminfo=new systemInfo();

    cpuTemperature=new QLabel(this);
    cpuTemperature_Name= new QLabel(this);

    cpuUsage_Name=new QLabel(this);
    cpuUsage=new QLabel(this);

    memUsage_Name=new QLabel(this);
    memUsage=new QLabel(this);

    hdd_Name=new QLabel(this);
    hddTemperature=new QLabel(this);

    mainboard_Name=new QLabel(this);
    mainboardTemperature=new QLabel(this);

    acpi_Name=new QLabel(this);
    acpiTemperatture=new QLabel(this);

    fan_Name=new QLabel(this);
    fanRevolution=new QLabel(this);

    net_Name=new QLabel(this);
    netSpeedShow=new QLabel(this);
    //初始化坐标
    coordinateX=0,coordinateY=0;

    timer = new QTimer(this);
    timer->setInterval(1000);
    timer->setSingleShot(false);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->start();

    init_ui();
}

ShowInfo::~ShowInfo()
{
    delete cpuTemperature_Name;
    delete cpuUsage_Name;
    delete memUsage_Name;
    delete hdd_Name;
    delete mainboard_Name;
    delete acpi_Name;
    delete fan_Name;
    delete net_Name;

    delete cpuTemperature;
    delete cpuUsage;
    delete memUsage;
    delete hddTemperature;
    delete mainboardTemperature;
    delete acpiTemperatture;
    delete fanRevolution;
    delete netSpeedShow;

    delete timer;
    delete netspeed;
    delete systeminfo;
}

void ShowInfo::timeout()
{
//    memused=systeminfo->getMemory();
    netspeed->reckonNetSpeed();
    upspeed=netspeed->getNetUpSpeed();
    downspeed=netspeed->getNetDownSpeed();
    update();
}

void ShowInfo::paintEvent(QPaintEvent *)
{
    this->setGeometry(coordinateX,coordinateY,210,250);
    QPainter paint(this);
    //        ===============先画底============
    QLinearGradient linearGradient(0,0,0,32);
    linearGradient.setColorAt(1.0,QColor(120, 175, 178));
    paint.setBrush(QBrush(linearGradient));
    paint.setRenderHint(QPainter::Antialiasing,true);
    paint.setPen(QPen(QColor(210, 210, 15), 1));
    paint.drawRoundedRect(0,0,210,250,15,15);
    paint.save();
    paint.restore();
    init_ui();
}

void ShowInfo::init_ui()
{
    //设置窗口大小
    this->setGeometry(coordinateX,coordinateY,210,250);
    //    this->resize(210,250);
    this->setWindowFlags(
                Qt::FramelessWindowHint//去边框
                |Qt::WindowStaysOnTopHint//最ding层显示
                |Qt::Tool//不在任务栏显示
                );//去边框//最ding层显示//不在任务栏显示
    this->setStyleSheet("border-radius:50px;width:200px;height:400px;");
    update();
    //宽高参数
    int height=30;
    int width=100;
    //cpu名称显示
    //            cpuTemperatureName->setObjectName(QStringLiteral("cpuTemperatureName"));
    cpuTemperature_Name->setGeometry(QRect(0*width+5, 0*height+5, width, height));
    QString Sstyle="background-color: rgb(255, 229, 96);";
    setLabelStyle(cpuTemperature_Name,Sstyle);
    cpuTemperature_Name->setText("cpu温度");
    //cpu温度显示
    cpuTemperature->setGeometry(QRect(1*width+5,0*height+5,width,height));
    Sstyle="background-color: rgb(50, 120, 127);";
    setLabelStyle(cpuTemperature,Sstyle);
    cpuTemperature->setText("30℃");

    //cpu使用率名称
    cpuUsage_Name->setGeometry(QRect(5, 1*height+5, width, height));
    Sstyle="background-color: rgb(255, 229, 96);";
    setLabelStyle(cpuUsage_Name,Sstyle);
    cpuUsage_Name->setText("cpu使用率");
    //cpu使用率
    cpuUsage->setGeometry(QRect(1*width+5,1*height+5,width,height));
    Sstyle="background-color: rgb(255, 229, 96);";
    setLabelStyle(cpuUsage,Sstyle);
    cpuUsage->setText(systeminfo->getCpuLoad(0.3));

    //内存使用名称
    memUsage_Name->setGeometry(QRect(5, 2*height+5, width, height));
    Sstyle="background-color: rgb(255, 229, 96);";
    setLabelStyle(memUsage_Name,Sstyle);
    memUsage_Name->setText("已内存");
    //内存使用
    memUsage->setGeometry(QRect(1*width+5,2*height+5,width,height));
    Sstyle="background-color:rgb(85, 85, 0);";
    setLabelStyle(memUsage,Sstyle);
    memUsage->setText(systeminfo->getQStringMemory());

    //硬盘名称显示
    hdd_Name->setGeometry(QRect(5, 3*height+5, width, height));
    Sstyle="background-color:rgb(85, 25, 0);";
    setLabelStyle(hdd_Name,Sstyle);
    hdd_Name->setText("硬盘温度：");
    //硬盘温度显示
    hddTemperature->setGeometry(QRect(1*width+5,3*height+5,width,height));
    Sstyle="background-color:rgb(85, 125, 0);";
    setLabelStyle(hddTemperature,Sstyle);
    hddTemperature->setText("30℃");

    //主板名称显示
    mainboard_Name->setGeometry(QRect(5, 4*height+5, width, height));
    Sstyle="background-color:rgb(85, 90, 0);";
    setLabelStyle(mainboard_Name,Sstyle);
    mainboard_Name->setText("主板温度：");
    //主板温度显示
    mainboardTemperature->setGeometry(QRect(1*width+5,4*height+5,width,height));
    Sstyle="background-color:rgb(105, 225, 0);";
    setLabelStyle(mainboardTemperature,Sstyle);
    mainboardTemperature->setText("30℃");

    //acpi名称显示
    acpi_Name->setGeometry(QRect(5, 5*height+5, width, height));
    Sstyle="background-color: rgb(255, 229, 96);";
    setLabelStyle(acpi_Name,Sstyle);
    acpi_Name->setText("acpi温度：");
    //acpi温度显示
    acpiTemperatture->setGeometry(QRect(1*width+5,5*height+5,width,height));
    Sstyle="background-color: rgb(255, 109, 96);";
    setLabelStyle(acpiTemperatture,Sstyle);
    acpiTemperatture->setText("30℃");
    /*
    //风扇名称显示
    fan_Name->setGeometry(QRect(5, 6*height+5, width, height));
    Sstyle="background-color: rgb(255, 229, 96);";
    setLabelStyle(fan_Name,Sstyle);
    fan_Name->setText("风扇转数：");
    //风扇转数显示
    fanRevolution->setGeometry(QRect(1*width+5,6*height+5,width,height));
    Sstyle="background-color: rgb(255, 229, 96);";
    setLabelStyle(fanRevolution,Sstyle);
    fanRevolution->setText("2000转");
    */
    //cpu频率名称显示
    fan_Name->setGeometry(QRect(5, 6*height+5, width, height));
    Sstyle="background-color: rgb(255, 229, 96);";
    setLabelStyle(fan_Name,Sstyle);
    fan_Name->setText("cpu频率：");
    //cpu频率显示
    fanRevolution->setGeometry(QRect(1*width+5,6*height+5,width,height));
    Sstyle="background-color: rgb(255, 229, 96);";
    setLabelStyle(fanRevolution,Sstyle);
    fanRevolution->setText(systeminfo->getFrequency());

    //网络名称显示
    net_Name->setGeometry(QRect(5, 7*height+5, width, height));
    Sstyle="background-color: rgb(255, 229, 96);";
    setLabelStyle(net_Name,Sstyle);
    net_Name->setText("网络速度：");
    //网络速度显示
    netSpeedShow->setGeometry(QRect(1*width+5,7*height+5,width,height));
    Sstyle="background-color: rgb(255, 229, 96);";
    setLabelStyle(netSpeedShow,Sstyle);
    netSpeedShow->setText(netspeed->getNetUpSpeed()+netspeed->getNetDownSpeed());

}

void ShowInfo::setLabelStyle(QLabel *qlabel,QString Sstyle)
{

    qlabel->setStyleSheet(
                Sstyle+
                "border-radius:10px;"
                "border-style: outset;"
                "border-width:2px;"
                "border-top-color: rgb(0, 170, 255);"
                "border-bottom-color: rgb(0, 170, 255);");
}

void ShowInfo::setParameter(int x, int y)
{
    coordinateX=x;
    coordinateY=y;
}


