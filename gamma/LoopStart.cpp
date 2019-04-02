#include "LoopStart.h"


LoopStart::LoopStart()
{


}

void LoopStart::Loop_Start()
{
    isStop = false;
}

void LoopStart::closeThread()
{
    isStop = true ;
}


void LoopStart::run()
{
    while (1)
    {
        QString str = "F5 FA 01 80 00 04 00 00 40 00 00 F0";
        emit sendShow(str);
        qDebug()<< "循环通讯已经打开";

        msleep(1000);
        if(isStop)
        {
            qDebug()<< "循环通讯已经关闭";
            break;

        }
    }

}
