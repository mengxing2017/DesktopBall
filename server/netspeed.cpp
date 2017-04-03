#include "netspeed.h"

netSpeed::netSpeed()
{
   pro=new QProcess();
}

netSpeed::~netSpeed()
{

}

void netSpeed::reckonNetSpeed()
{
    QRegularExpressionMatchIterator matchs;
    QString result,tmp;
    qint64 up=0,down=0,t=0;
    upspeed = "";
    downspeed="";
    QRegularExpression reg;
    pro->start("ip -s link");
    if(pro->waitForStarted(2000))
    {
        if(pro->waitForFinished(1000))
        {
            result=pro->readAllStandardOutput();
            //  qDebug()<<result;
            if(!result.isEmpty())
            {
                result.remove(QRegularExpression("link/(?!loopback|ether)[\\S\\s]+?collsns[\\S\\s]+?(\\d+ +){6}"));
                reg.setPattern("collsns[\\s\\S]+?\\d+");
                matchs=reg.globalMatch(result);
                while(matchs.hasNext())
                {
                    tmp=matchs.next().captured(0);
                    tmp.remove(QRegularExpression("[\\s\\S]+ "));
                    t=tmp.toInt();
                    up+=t;
                }
                // qDebug()<<"got up-data"<<up<<"oup"<<oup;
                // QString text;

                t=up-oup;
                t=t/1024;
                if(t>999)
                {
                    t=t*100/1024;
                    float f=t*1.0/100;
                    upspeed="↑"+QString().setNum(f)+"M";

                }
                else if(t>0) upspeed+="↑"+QString().setNum(t)+"K";
                else upspeed="↑"+QString().setNum(up-oup)+"B";

                if(oup == 0) upspeed ="↑0B";//没有基数，网速不正确，设为0B。
                oup=up;

                reg.setPattern("mcast[\\s\\S]+?\\d+");
                matchs=reg.globalMatch(result);
                while(matchs.hasNext())
                {
                    tmp=matchs.next().captured(0);
                    tmp.remove(QRegularExpression("[\\s\\S]+ "));
                    t=tmp.toLongLong();
                    down+=t;
                    // qDebug()<<"got down"<<tmp;
                }
                // qDebug()<<"got down-data"<<down<<"odown"<<odown;
                t=down-odown;
                t=t/1024;
                if(t>999)
                {
                    t=t*100/1024;
                    float f=t*1.0/100;
                    downspeed="↓"+QString().setNum(f)+"M";

                }
                else if(t>0) downspeed="↓"+QString().setNum(t)+"K";
                else downspeed="↓"+QString().setNum(down-odown)+"B";

                // if(odown!=0) ui->down->setText(text);
                if(odown == 0) downspeed ="↓0B";//没有基数，网速不正确，设为0B。

                odown=down;
            }
        }
    }
}

QString netSpeed::getNetUpSpeed()
{  
    return upspeed;
}
QString netSpeed::getNetDownSpeed()
{
    return downspeed;
}
