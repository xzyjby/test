#include "mainwindow.h"
#include "ui_mainwindow.h"





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


//    rubberBand = new QRubberBand(QRubberBand::Rectangle, ui->showPic);
    serialport = new QSerialPort ;
    PI = new PortInitialization ;
    M_LoopStart = new LoopStart;
    racd_w = new ReadAndCheckData ;
    setConnect();
    plainChar();
    //QObject::connect(serialport, &QSerialPort::readyRead, PI, &PortInitialization::showReData);

}

MainWindow::~MainWindow()
{
    delete ui;
}




//void MainWindow:: onXRangeChanged(QCPRange range)
//{
//    ui->showPic->xAxis->setRange(range.bounded(0,4096));
//}
//void MainWindow:: onYRangeChanged(QCPRange range)
//{
//    ui->showPic->yAxis->setRange(range.bounded(0,50000));
//}

void MainWindow::plainCharLoop1()
{
    dealDrawBarChart();
    dealDrawLine();
}

void MainWindow::Process_LoopStart()
{
    QObject::connect(serialport, &QSerialPort::readyRead, this, &MainWindow::MGetloopdata);

    M_LoopStart->Loop_Start();
    M_LoopStart->start();

}

void MainWindow::Process_LoopEnd()
{
    M_LoopStart->closeThread();
    M_LoopStart->quit();
    M_LoopStart->wait();

}

void MainWindow::MGetloopdata()
{
    QByteArray buf ;

    buf = serialport->readAll();
    buf1 += buf;
    int TotalDataNumReturn = 0 ;
    TotalDataNumReturn = buf1.length();
    if(TotalDataNumReturn == 16392)//串口通讯返回的数据消息用getNum接收到,为主窗口成像使用
    {
        M_getNum.clear();
        M_getNum = racd_w-> getDatatoCheck(buf1);
        buf1.clear();
        plainCharLoop();
    }
    else {

       PI->showReData(buf1);
    }

}

void MainWindow::m_mouseWheel(QWheelEvent *event)
{
    int zoomSize = (event->delta())/60;//设定为滚轮放大缩小倍数为2倍

    if(event->delta()>0)//滚轮向上放大 zoomsize每滚动一次数值为120
    {
        yMaxData = yMaxData*zoomSize;
        ui->showPic->yAxis->setRange(0,yMaxData);
        ui->showPic->replot();
    }
    if(event->delta()<0)//滚轮向下缩小 zoomsize每滚动一次数值为-120
    {
        yMaxData = yMaxData/(-1*zoomSize);
        ui->showPic->yAxis->setRange(0,yMaxData);
        ui->showPic->replot();
    }
}





void MainWindow::newSerialPort()
{

    qDebug()<<"新串口添加完毕";
    emit sendSerailPort(serialport);
}

void MainWindow::setConnect()//设置父子窗口间的通讯
{
    connect(ui->Port_set,&QAction::triggered,[=](){
        PI->show();
    });
    connect(ui->B_LoopStart,&QAction::triggered,[=](){
        Process_LoopStart();
    });//工具栏开始采集

    connect(ui->B_LoopEnd,&QAction::triggered,[=](){
        Process_LoopEnd();
    });//工具栏停止采集

    connect(PI,SIGNAL(newSP()),this,SLOT(newSerialPort()));
    //  connect(PI,SIGNAL(sendPicData(vector<int>)),this,SLOT(getPicData(vector<int>)));
    connect(this,SIGNAL(sendSerailPort(QSerialPort*)),PI,SLOT(getSerialPort(QSerialPort *)));

    connect(M_LoopStart,SIGNAL(sendShow(QString)),PI,SLOT(sort_SendMessage(QString)));

    //connect(racd_w,SIGNAL(callShowPic()),ui,SLOT(plainCharLoop1()));
}

void MainWindow::initCustomPlot()
{
    ui->showPic->resize(1050,500);
    ui->showPic->xAxis->setVisible(true);
    ui->showPic->yAxis->setVisible(true);
    /// 设置顶边线和右边线显示但不显示刻度值
    ui->showPic->xAxis2->setVisible(false);
    ui->showPic->xAxis2->setTickLabels(false);
    ui->showPic->yAxis2->setVisible(false);
    ui->showPic->yAxis2->setTickLabels(false);
    ui->showPic->xAxis2->setTicks(false);
    ui->showPic->yAxis2->setTicks(false);
    ui->showPic->xAxis->setRange(0,4096);
    ui->showPic->yAxis->setRange(0,50000);
    /// 设置顶边线和右边线随x、y变化而变化
    //connect(ui->showPic->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->showPic->xAxis2, SLOT(setRange(QCPRange)));
    //connect(ui->showPic->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->showPic->yAxis2, SLOT(setRange(QCPRange)));
   // ui->showPic-> axisRect()->setRangeDrag(Qt::Vertical);

    /// 设置拖拽、放大缩小功能
  // ui->showPic->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom );

   connect(ui->showPic, SIGNAL(mouseWheel(QWheelEvent *)), this, SLOT(m_mouseWheel(QWheelEvent *)));
   //connect(ui->showPic, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

  // connect(ui->showPic, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(mouseWheel(QMouseEvent*)));



//    connect(ui->showPic->xAxis,SIGNAL(rangeChanged(QCPRange)), this,SLOT(onXRangeChanged(QCPRange)));//控制坐标轴负轴显示
//    connect(ui->showPic->yAxis,SIGNAL(rangeChanged(QCPRange)), this,SLOT(onYRangeChanged(QCPRange)));
}

void MainWindow::dealDrawLine()
{
    ui->showPic->setBackground(QBrush(QColor(Qt::gray)));
    QPen drawPen;
    drawPen.setColor(Qt::blue);
    drawPen.setWidth(1);
    QVector<double> xLineVector, yLineVector;
    xLineVector.clear();
    yLineVector.clear();
    for(int i = 0 ;i <M_getNum.size() ;i++)
    {
        yLineVector.push_back(M_getNum[i]);
        xLineVector.push_back(i);
    }
    QCPGraph * curGraph = ui->showPic->addGraph();
    curGraph->setPen(drawPen);
    curGraph->setLineStyle(QCPGraph::lsLine);
    curGraph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    curGraph->setData(xLineVector, yLineVector);
    ui->showPic->replot();
    ui->statusBar->showMessage("绘制完毕");

}

void MainWindow::dealDrawBarChart()
{
    int plottableCount = ui->showPic->plottableCount();
    if (plottableCount != 0)//如果之前画板有数据直接清空重画
    {
        ui->showPic->clearPlottables();
    }

    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(100, 100, 100));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->showPic->setBackground(QBrush(gradient));

    QVector<double> xBarVector, yBarVector;

    xBarVector.clear();
    yBarVector.clear();
    for(int i = 0 ;i <M_getNum.size() ;i++)
    {
        yBarVector.push_back(M_getNum[i]);
        xBarVector.push_back(i);
    }


    QCPBars *rectBar = new QCPBars(ui->showPic->xAxis, ui->showPic->yAxis);
    rectBar->setAntialiased(false);
    rectBar->setStackingGap(1);
    rectBar->setPen(QPen(QColor(0, 168, 140).lighter(130)));
    rectBar->setBrush(QColor(0, 168, 140));
    rectBar->setData(xBarVector, yBarVector);
    ui->showPic->replot();
    qDebug()<<this->serialport->portName();


}

void MainWindow::plainChar()
{
    initCustomPlot();
    dealDrawBarChart();
    dealDrawLine();
}

void MainWindow::plainCharLoop()
{
    dealDrawBarChart();
    dealDrawLine();
    M_getNum.clear();
}



