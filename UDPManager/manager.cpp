#include "manager.h"
#include <QDebug>
#include <QHostAddress>

#include "./modules/jsonmanager.h"

Manager::Manager()
{
    mUdpSocket.bind(8009);
    connect(&mUdpSocket,SIGNAL(readyRead()),SLOT(onReceiveData()));

    userlist.clear();
}

void Manager::onReceiveData()
{
    QByteArray receivedata;
    QHostAddress targetaddr;//ip
    quint16 targetport;//端口号

    while(mUdpSocket.hasPendingDatagrams()) //是否有数据包等待读取
    {
        receivedata.resize(mUdpSocket.pendingDatagramSize());
        mUdpSocket.readDatagram(receivedata.data(), receivedata.size(), &targetaddr,&targetport);
    }



    qDebug()<<"all receivedata: "<<receivedata.toHex()<<endl;
    qDebug()<<"receive str : "<<QString(receivedata)<<endl;

    QList<QByteArray> qbyteList =  receivedata.split( '####DATA####' );

    JsonManager jsonm;
    JsonData rData = jsonm.readJson(qbyteList.at(0));
    qDebug()<<"rData.telphone: "<<rData.telphone<<endl;


    UserInfo user(targetaddr,targetport);



    if(receivedata.startsWith( QString("Test").toLocal8Bit() ))
    {
        qDebug()<<"its startwith Test"<<endl;
    }

    qDebug()<<"targetaddr: "<<targetaddr.toString()<<"     targetport: "<<targetport<<endl;

    QByteArray data = QString("jedi ubuntu receive your message").toLocal8Bit();

    sendData(data,targetaddr,targetport);
}

void Manager::sendData(QByteArray &data, QHostAddress targetAddress, int targetPort)
{
    //targetPort = 8008;
    mUdpSocket.writeDatagram(data, targetAddress,targetPort);
}
