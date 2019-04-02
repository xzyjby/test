#ifndef PORTINITIALIZATION_H
#define PORTINITIALIZATION_H


#include <qDebug>
#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <vector>

#include "ReadAndCheckData.h"
#include "LoopStart.h"

using namespace std ;

namespace Ui {
class PortInitialization;
}

class PortInitialization : public QWidget
{
    Q_OBJECT

public:
    explicit PortInitialization(QWidget *parent = 0);
    ~PortInitialization();

private slots:


    void on_OpenPort_clicked();

    void on_ClosePort_clicked();

    void on_ClearMessage_clicked();

    void on_setVoltage_clicked();



    void on_Power_Set_stateChanged(int arg1);

private:
    Ui::PortInitialization *ui;
signals:
    void newSP();//serialport -->sp
  //  void sendPicData(vector<int>num_temp);
public slots:
    void getSerialPort(QSerialPort* serialport);


public:
    QSerialPort* serialport;

    ReadAndCheckData* racd_w ;

public:
   void Initialization(QSerialPort* serialport);
  // void getPortData();
   void updatePort();
   void sort_SendMessage();
   void showReData(QByteArray buf1);//接收消息并在文本框显示出来
public:
   int i  = 0;
   int TotalDataNumReturn = 0 ;
   QByteArray allData;
   QByteArray buf1 ;
   vector<int>P_getNum;
private:
   bool powerReadOrWrite = false ;

public slots:
   void sort_SendMessage(QString strTemp);
};

#endif // PORTINITIALIZATION_H
