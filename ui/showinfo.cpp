#include "showinfo.h"
#include <QDebug>

ShowInfo::ShowInfo(QWidget *parent) : QMainWindow(parent)
{
    tabWidget = new QTabWidget(this);
    tab_info= new QWidget();
    tab_monitor = new QWidget();

    netspeed=new netSpeed();
    systeminfo=new systemInfo();


    cpuUsage_Name=new QLabel(tab_info);
    cpuUsage=new QLabel(tab_info);

    memUsage_Name=new QLabel(tab_info);
    memUsage=new QLabel(tab_info);

    cpuFrequency_Name=new QLabel(tab_info);
    cpuFrequency=new QLabel(tab_info);

    swap_Name=new QLabel(tab_info);
    swap=new QLabel(tab_info);

    net_Name=new QLabel(tab_info);
    netSpeedShow=new QLabel(tab_info);

    process=new QProcess();
    cmd = MEM_SORT;
    //初始化坐标
    coordinateX=0,coordinateY=0;

    timer = new QTimer(this);
    timer->setInterval(1000);
    timer->setSingleShot(false);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout_info()));
    timer->start();

    timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(getInfo()));
    timer2->start(4000);


    tabWidget->setGeometry(QRect(0, 0, 210, 250));
    tabWidget->addTab(tab_info, QString("硬件信息"));
    tabWidget->addTab(tab_monitor, QString("进程信息"));
    tabWidget->setCurrentIndex(0);

    tableWidget=new QTableWidget(tab_monitor);

    init_ui();
    initUiMonitot();
    getInfo();
}

ShowInfo::~ShowInfo()
{

    delete cpuUsage_Name;
    delete memUsage_Name;
    delete  cpuFrequency_Name;
    delete cpuFrequency;
    delete swap_Name;
    delete swap;
    delete net_Name;
    delete cpuUsage;
    delete memUsage;
    delete netSpeedShow;

    delete timer;
    delete netspeed;
    delete systeminfo;
}

void ShowInfo::timeout_info()
{
//    memused=systeminfo->getMemory();
    netspeed->reckonNetSpeed();
    upspeed=netspeed->getNetUpSpeed();
    downspeed=netspeed->getNetDownSpeed();
    update();
}

bool ShowInfo::pidselected(const QString &pid)
{
    QString sel;
    for(int i=0;i<selected.length();i++)
    {
        sel=selected.at(i);
        if(pid==sel) {
            listupdate2freshselected.append(sel);
            return true;
        }
    }
    return false;
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

    QString Sstyle;
    //cpu使用率名称
    cpuUsage_Name->setGeometry(QRect(5, 0*height+5, width, height));
    Sstyle="background-color: rgb(255, 229, 96);";
    setLabelStyle(cpuUsage_Name,Sstyle);
    cpuUsage_Name->setText("cpu使用率");
    //cpu使用率
    cpuUsage->setGeometry(QRect(1*width+5,0*height+5,width,height));
    Sstyle="background-color: rgb(255, 229, 96);";
    setLabelStyle(cpuUsage,Sstyle);
    cpuUsage->setText(systeminfo->getCpuLoad(0.3));

    //cpu频率名称显示
    cpuFrequency_Name->setGeometry(QRect(5, 1*height+5, width, height));
    Sstyle="background-color: rgb(255, 229, 96);";
    setLabelStyle(cpuFrequency_Name,Sstyle);
    cpuFrequency_Name->setText("cpu频率：");
    //cpu频率显示
    cpuFrequency->setGeometry(QRect(1*width+5,1*height+5,width,height));
    Sstyle="background-color: rgb(255, 229, 96);";
    setLabelStyle(cpuFrequency,Sstyle);
    cpuFrequency->setText(systeminfo->getFrequency());

    //内存使用名称
    memUsage_Name->setGeometry(QRect(5, 2*height+5, width, height));
    Sstyle="background-color: rgb(255, 229, 96);";
    setLabelStyle(memUsage_Name,Sstyle);
    memUsage_Name->setText("已内存：");
    //内存使用
    memUsage->setGeometry(QRect(1*width+5,2*height+5,width,height));
    Sstyle="background-color:rgb(85, 85, 0);";
    setLabelStyle(memUsage,Sstyle);
    memUsage->setText(systeminfo->getQStringMemory());

    //swap使用名称
    swap_Name->setGeometry(QRect(5, 3*height+5, width, height));
    Sstyle="background-color: rgb(255, 229, 96);";
    setLabelStyle(swap_Name,Sstyle);
    swap_Name->setText("Swap：");
    //swap使用
    swap->setGeometry(QRect(1*width+5,3*height+5,width,height));
    Sstyle="background-color:rgb(85, 85, 0);";
    setLabelStyle(swap,Sstyle);
    swap->setText(systeminfo->getSwap());

    //网络名称显示
    net_Name->setGeometry(QRect(5, 4*height+5, width, height));
    Sstyle="background-color: rgb(255, 229, 96);";
    setLabelStyle(net_Name,Sstyle);
    net_Name->setText("网络速度：");
    //网络速度显示
    netSpeedShow->setGeometry(QRect(1*width+5,4*height+5,width,height));
    Sstyle="background-color: rgb(255, 229, 96);";
    setLabelStyle(netSpeedShow,Sstyle);
    netSpeedShow->setText(netspeed->getNetUpSpeed()+netspeed->getNetDownSpeed());
}

void ShowInfo::initUiMonitot()
{
    if (tableWidget->columnCount() < 1)
        tableWidget->setColumnCount(1);
    tableWidget->setObjectName(QStringLiteral("tableWidget"));
    tableWidget->setFrameShape(QFrame::NoFrame);
    tableWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
    tableWidget->setAutoScroll(false);
    tableWidget->setAutoScrollMargin(0);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    tableWidget->setShowGrid(false);
    tableWidget->setGridStyle(Qt::NoPen);
    tableWidget->setSortingEnabled(false);
    tableWidget->setWordWrap(false);
    tableWidget->setCornerButtonEnabled(false);
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(1);
    tableWidget->horizontalHeader()->setVisible(false);
    tableWidget->horizontalHeader()->setDefaultSectionSize(50);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->verticalHeader()->setDefaultSectionSize(25);
    tableWidget->verticalHeader()->setMinimumSectionSize(20);
    tableWidget->horizontalHeader()->setVisible(true);
    tableWidget->verticalHeader()->setVisible(false);

    tableWidget->setColumnCount(3);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setColumnWidth(0,100);
    tableWidget->setColumnWidth(1,50);
    tableWidget->setColumnWidth(2,60);
    tableWidget->setFrameShape(QFrame::NoFrame);
    tableWidget->setFixedSize(210,250);
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

void ShowInfo::getInfo()
{
    timer->stop();
    listupdate2freshselected.clear();
    QRegularExpression reg;
    QStringList list;
    QTableWidgetItem *item;
    process->start("/bin/bash");
    tableWidget->clear();
    QStringList header;
    header<<tr("进程")<<tr("CPU%")<<tr("内存%");
    tableWidget->setHorizontalHeaderLabels(header);
    if(process->waitForStarted(3000))
    {
        process->write(cmd.toLatin1());
        process->closeWriteChannel();
        process->waitForFinished(3000);
        QString result = process->readAllStandardOutput();
        reg.setPattern(" +");
        result = result.replace(reg," ");
        //qDebug()<<result.split("\n");
        list = result.split("\n");

        list.removeFirst();//去除表头
        list.removeLast();//去除最后换行
//        qDebug()<<list.length();
        tableWidget->setRowCount(list.length());
        for(int i=0;i<list.length();i++)
        {

            QString line,pid;
            line = list.at(i);
            QStringList one = line.split(" ");
            pid = one.at(1);
//            qDebug()<<one;
            bool root=false;
            for(int j=0;j<tableWidget->columnCount();j++)
            {

                item = new QTableWidgetItem;
                if(j==0)
                {
                    item->setWhatsThis(pid);
                    line = one.at(4);
                    if((QString(one.at(0))=="root"))    {
                        root = true;

                        line ="[Root] "+line;
                    }
//                    qDebug()<<line;
                    item->setText(line);
                    line = one.mid(5).join(" ");
                    item->setToolTip(line);

                }
                else if(j==1)
                {
                    item->setTextAlignment(Qt::AlignHCenter	);
                    item->setText(one.at(2));
                }
                else if(j==2)
                {
                    line = one.at(3);
                    item->setTextAlignment(Qt::AlignHCenter	);
                    item->setText(line);
                }
//                 qDebug()<<i<<j<<item->data(0);
                tableWidget->setItem(i,j,item);
            }
        }
        //listupdate2freshselected 是刷新后的选择，selected应清空再赋值
        //主要是防止cpu和内存切换后，已选择的进程不在列表中了，误删看不见但在selected的进程
        listupdate2freshselected.clear();

    }
    timer->start();
//    qDebug()<<"test";
}

