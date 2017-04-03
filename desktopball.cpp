#include "desktopball.h"
#include "./ui/showinfo.h"

DesktopBall::DesktopBall(QWidget *parent)
    : QWidget(parent)
{
    QDesktopWidget* desktopWidget = QApplication::desktop();
    setGeometry(desktopWidget->width()-120,desktopWidget->height()-120,100,32);
    setWindowFlags(
                Qt::FramelessWindowHint//去边框
           |Qt::WindowStaysOnTopHint//最ding层显示
            |Qt::Tool//不在任务栏显示
         );//去边框//最ding层显示//不在任务栏显示
    this->setAttribute(Qt::WA_TranslucentBackground, true);

    //网速对象
    netspeed=new netSpeed();
    //内存对象
    systeminfo=new systemInfo();

    tuichu  = new QAction("退出", this);
    moniter = new QAction("系统监视器",this);
    connect(tuichu, SIGNAL(triggered(bool)), qApp, SLOT(quit()));//若触发了退出就退出程序
    connect(moniter,SIGNAL(triggered(bool)),this,SLOT(openmoniter()));

    memused =0;
    upspeed = "↑0K";
    downspeed = "↓0K";

    mousepressed=false;
    oldpos.setX(0);
    oldpos.setY(0);
    oup=0;
    odown=0;
    pro = new QProcess(this);

    timer = new QTimer(this);
    timer->setInterval(1000);
    timer->setSingleShot(false);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->start();
    poscheck();
}

DesktopBall::~DesktopBall()
{
    delete netspeed;
    delete systeminfo;
}
void DesktopBall::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
        //===============先画底============
    QLinearGradient linearGradient(0,0,0,32);
        //创建了一个QLinearGradient对象实例，参数为起点和终点坐标，可作为颜色渐变的方向
        //painter.setPen(Qt::NoPen);
        linearGradient.setColorAt(0.0,Qt::white);
        linearGradient.setColorAt(1.0,QColor(224, 224, 224));
        paint.setBrush(QBrush(linearGradient));
    paint.setRenderHint(QPainter::Antialiasing,true);
    //↓由于使用了反锯齿，四边都要多1像素，需要右下各移动1像素再绘图，确保边缘平滑显示。
    paint.setPen(QPen(QColor(210, 210, 210), 1));
  //  paint.setBrush(QBrush(Qt::white));
    paint.drawRoundedRect(1,1,100,30,10,10);
    paint.save();
    paint.restore();

//===================再画内存底=========================
    QString picture;
    if(memused>=80)//内存大时的颜色！默认红色
   {
        picture = RED;
   }
    else if(memused>=65&&memused<80)//内存占用较多时的颜色！默认橙色
    {
         picture = YELLOW;
    }
    else picture = GREEN;

    int mem = memused * 30 / 100;
    QPixmap pix = QPixmap(picture).copy(0,mem,30,30);
    paint.setBrush(QBrush(Qt::green,pix));
    paint.setPen(QPen(QColor(210, 210, 210), 1));
    paint.drawRoundedRect(1,1,45,30,10,10);
    paint.save();
    paint.restore();
    //==================再写内存数值==============================
    paint.setPen(QPen(QColor(255, 255, 255), 1));
    QFont font;
    font.setPixelSize(16);
    paint.setFont(font);
    paint.drawText(QRectF(1,1,45,30),Qt::AlignCenter,QString().setNum( memused));
    paint.save();
    paint.restore();
//=========================最后网速数值==================
    font.setPixelSize(11);
    paint.setFont(font);
    paint.setPen(QPen(Qt::red, 1));
    paint.drawText(QRectF(44,2,58,14),Qt::AlignLeft|Qt::AlignVCenter,upspeed);

    paint.setPen(QPen(QColor(60, 150, 21), 1));
    paint.drawText(QRectF(44,16,58,14),Qt::AlignLeft|Qt::AlignVCenter,downspeed);
    paint.save();
    paint.restore();

    QWidget::paintEvent(event);
}


void DesktopBall::timeout()
{
    memused=systeminfo->getMemory();
    netspeed->reckonNetSpeed();
    upspeed=netspeed->getNetUpSpeed();
    downspeed=netspeed->getNetDownSpeed();
    update();

}
void DesktopBall::mousePressEvent(QMouseEvent* event)
{
    if(event->button()==Qt::LeftButton )
    {
        oldpos=event->globalPos()-this->pos();
        setCursor(Qt::ClosedHandCursor);
    }
}

void DesktopBall::mouseMoveEvent(QMouseEvent * event){
        move(event->globalPos()-oldpos);//貌似linux要这样
        event->accept();
}

void DesktopBall::mouseReleaseEvent(QMouseEvent * event){
    setCursor(Qt::ArrowCursor);
    event->accept();
}

void DesktopBall::contextMenuEvent(QContextMenuEvent *) //右键菜单项编辑
{
QCursor cur=this->cursor();
QMenu *menu=new QMenu(this);
menu->addAction(moniter);//添加系统监视器
menu->addAction(tuichu); //添加退出
menu->exec(cur.pos()); //关联到光标
}

void DesktopBall::openmoniter()
{
    QProcess process;
    process.startDetached("gnome-system-monitor");

}

void DesktopBall::poscheck()
{
    int x=this->x();
    int y=this->y();
    //        qDebug()<<x<<endl<<y;

    if(this->pos().x()<0) x=0;
    else if(QApplication::desktop()->width()-x<this->width()){
      x=QApplication::desktop()->width()-this->width();
    }

    if(this->pos().y()<0) y=0;
    else if(QApplication::desktop()->height()-y<this->height())
    {
      y=QApplication::desktop()->height()-this->height();
    }
    //        qDebug()<<x<<endl<<y;
    move(x,y);
}
