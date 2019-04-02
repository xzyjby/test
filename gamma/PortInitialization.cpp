#include "PortInitialization.h"
#include "ui_PortInitialization.h"

PortInitialization::PortInitialization(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PortInitialization)
{
    ui->setupUi(this);

    updatePort();



}

PortInitialization::~PortInitialization()
{
    delete ui;

}



void PortInitialization::on_OpenPort_clicked()
{
    emit newSP();//发送给主窗口创建一个串口通讯的指针

}

void PortInitialization::on_ClosePort_clicked()
{
//    serialport->clear();
//    serialport->close();


}

void PortInitialization::on_ClearMessage_clicked()
{

    ui->return_data->setText("已经清空");

}

void PortInitialization::sort_SendMessage(QString strTemp)
{

    QString str = "F5 FA 01 80 00 04 00 00 40 00 00 F0";//测试使用
    QByteArray str1 = QByteArray::fromHex(str.toLatin1().data());
    serialport->write(str1);


}



void PortInitialization::getSerialPort(QSerialPort* serialport)//获取串口指针,并且给串口赋值
{
    this->serialport = serialport;
    qDebug()<< "获取到新串口地址";
    Initialization(this->serialport);//给串口赋值
    qDebug()<<this->serialport->portName();
}

void PortInitialization::Initialization(QSerialPort *serialport)//
{
    serialport->setPortName(ui->PortNum->currentText());

    if(serialport->open(QIODevice::ReadWrite))
    {
        serialport->setBaudRate(ui->BaudRate->currentText().toInt());

        switch(8)//ui->DataBit->currentIndex())                   //设置数据位数X
        {
        case 8:
            serialport->setDataBits(QSerialPort::Data8);

            break;

        default: break;
        }
        switch(0)//ui->CheckNum->currentIndex())                   //设置奇偶校验X
        {
        case 0:
            serialport->setParity(QSerialPort::NoParity);

            break;
        default: break;
        }
        switch(2)//ui->StopNum->currentIndex()*2)                     //设置停止位X
        {
        case 2:
            serialport->setStopBits(QSerialPort::OneStop);

            break;
        case 3:
            serialport->setStopBits(QSerialPort::OneAndHalfStop);

            break;
        case 4:
            serialport->setStopBits(QSerialPort::TwoStop);

            break;
        default: break;
        }
        serialport->setFlowControl(QSerialPort::NoFlowControl);     //设置流控制
        qDebug()<<"串口初始化参数设置完成";

    }
}

//void PortInitialization::getPortData(QString str)
//{
//    QByteArray buf ;
//    buf.clear();
//    buf = serialport->readAll();
//    buf1 += buf;

//        TotalDataNumReturn = buf1.length();
//        if(TotalDataNumReturn == 16392)//串口通讯返回的数据消息用getNum接收到,为主窗口成像使用
//        {
//            P_getNum = racd_w-> getDatatoCheck(buf1);
//        }



//}

void PortInitialization::updatePort()
{
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())

    {
        QSerialPort serial;
        serial.setPort(info);   //设置串口

        if(serial.open(QIODevice::ReadWrite))
        {
            ui->PortNum->addItem(serial.portName());//显示串口name
            serial.close();
        }

    }
}

void PortInitialization::showReData(QByteArray buf1)//str = 失败消息
{


    QByteArray tempbuf = buf1;

    QString str1 = QObject::tr(tempbuf.toHex());
     if(str1 !=  NULL)
     {
         ui->return_data->setText(str1);

     }
     else
     {
         ui->return_data->setText("串口通讯失败");
     }



}

void PortInitialization::on_setVoltage_clicked()
{
    if(powerReadOrWrite)
    {
        QString str = "F5 FA 00 40 00 04 00 00 02 00 00 F0";//测试使用
        QByteArray str1 = QByteArray::fromHex(str.toLatin1().data());
        serialport->write(str1);
        qDebug()<<this->serialport->portName();
        ui->return_data->setText("电压修改成功");
    }
    else
    {
        ui->return_data->setText("电压开关未打开,修改失败");
    }





}



void PortInitialization::on_Power_Set_stateChanged(int arg1)
{

    qDebug()<< arg1;
    if(ui->Power_Set->isChecked())
    {
        powerReadOrWrite = true;
        ui->Power_Set->setText( "开");

    }
    else
    {
        powerReadOrWrite = false;
        ui->Power_Set->setText("关");
    }
}
