#ifndef LOOPSTART_H
#define LOOPSTART_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMainWindow>
#include <QThread>
#include <qDebug>


class LoopStart: public QThread
{
    Q_OBJECT
    public:
        LoopStart();
        void Loop_Start();
        void closeThread();
    signals:
        void sendShow(QString str);
    protected:
        virtual void run();
    private:
        volatile bool isStop;
};

#endif // LOOPSTART_H
