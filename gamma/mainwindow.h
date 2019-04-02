#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <vector>
#include <qDebug>
#include <QMainWindow>





#include "PortInitialization.h"
#include "ui_PortInitialization.h"
#include "qcustomplot.h"
#include "ReadAndCheckData.h"
#include "LoopStart.h"


using namespace std ;



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

public:
    QSerialPort* serialport ;
    PortInitialization* PI ;
    ReadAndCheckData* racd_w;

public:

    void setConnect();//设置父子窗口间的通讯
    void initCustomPlot();//绘制画板
    void dealDrawLine();
    void dealDrawBarChart();
    void plainChar();
    void plainCharLoop();
public slots:

    void newSerialPort();
signals:
    void sendSerailPort(QSerialPort* serialport);
public:
    vector<int>M_getNum;
    LoopStart* M_LoopStart;
    QByteArray buf1;

public slots:
//    void onXRangeChanged(QCPRange range);//控制显示界面的x轴,使得x轴负半轴不显示
//    void onYRangeChanged(QCPRange range);//控制显示界面的y轴,使得y轴负半轴不显示
   // void getLoopMessage(QString strTemp);//获取每次循环串口通讯写入的回馈消息
    void plainCharLoop1();
   // void getPicData(vector<int>num_PicData);
public:
    void Process_LoopStart();
    void Process_LoopEnd();
    void MGetloopdata();

private slots:

    //void mousePress(QMouseEvent* mevent);

   // void mouseMove(QMouseEvent *mevent);

   // void mouseRelease(QMouseEvent *mevent);

    void m_mouseWheel(QWheelEvent *event);
private :
    QRubberBand *rubberBand;
    QPoint rubberOrigin;
    private :
    double yMaxData = 50000;



};

#endif // MAINWINDOW_H
