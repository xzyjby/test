#ifndef READANDCHECKDATA_H
#define READANDCHECKDATA_H

#include <QByteArray>
#include <qDebug>
#include <vector>


using namespace std ;



class ReadAndCheckData
{

public:
    ReadAndCheckData(){}

public:


   vector<int> getDatatoCheck(QByteArray temp);
   int  bytesToInt(QByteArray bytes);
   std::vector<int>Temp_Vnum;
public:
signals:


};

#endif // READANDCHECKDATA_H
