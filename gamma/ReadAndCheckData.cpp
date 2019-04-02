#include "ReadAndCheckData.h"



vector<int> ReadAndCheckData::getDatatoCheck(QByteArray temp)
{
    QByteArray getNumTemp = temp;


        QString tempStr =  QObject::tr(getNumTemp.mid(0,4).toHex());
        if(tempStr == "f5fa0180")
        {
            Temp_Vnum.clear();
            for(int i = 0; i< 4096 ; i++)
            {
                QByteArray oneNum = getNumTemp.mid(6+4*i,4);
                Temp_Vnum.push_back(bytesToInt(oneNum));
            }
        }
    return Temp_Vnum;

}

int ReadAndCheckData::bytesToInt(QByteArray bytes)
{
    int addr = bytes[3] & 0x000000FF;
    addr |= ((bytes[2] << 8) & 0x0000FF00);
    addr |= ((bytes[1] << 16) & 0x00FF0000);
    addr |= ((bytes[0] << 24) & 0xFF000000);
    return addr;
}

