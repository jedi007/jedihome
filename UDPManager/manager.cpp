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
    QHostAddress commingAddr;//ip
    quint16 commingPort;//端口号

    while(mUdpSocket.hasPendingDatagrams()) //是否有数据包等待读取
    {
        receivedata.resize(mUdpSocket.pendingDatagramSize());
        mUdpSocket.readDatagram(receivedata.data(), receivedata.size(), &commingAddr,&commingPort);
    }

    qDebug()<<"commingAddr: "<<commingAddr.toString()<<endl;
    qDebug()<<"all receivedata: "<<receivedata.toHex()<<endl;
    qDebug()<<"receive str : "<<QString(receivedata)<<endl;

    QByteArray sep = QString("####DATA####").toLocal8Bit();
    JsonData rData;
    JsonManager jsonm;
    int index = receivedata.indexOf( sep );
    if(index < 0)
    {
        rData = jsonm.readJson(receivedata);
    }else if (index >= 0)
    {
        QList<QByteArray> qbyteList;
        qbyteList.append(receivedata.mid(0,index) );
        qbyteList.append( receivedata.right( receivedata.size()-qbyteList.at(0).size()-sep.size()) );
        qDebug()<<"qbyteList.at(0): "<<qbyteList.at(0)<<endl;
        qDebug()<<"qbyteList.at(1): "<<qbyteList.at(1)<<endl;
        rData = jsonm.readJson(qbyteList.at(0));
        rData.data = qbyteList[1];
    }


    qDebug()<<"rData.data: "<<rData.data<<endl;

    qDebug()<<"rData.telphone: "<<rData.telphone<<endl;
    qDebug()<<"rData.targetTelephone: "<<rData.targetTelephone<<endl;
    qDebug()<<"rData.m_action: "<<rData.m_action<<endl;

    UserInfo user(commingAddr,commingPort,rData.ID,rData.telphone);
    userlist[user.telephone] = user;
    qDebug()<<"userlist: "<<userlist[user.telephone].telephone<<endl;

    switch (rData.m_action) {
        case JsonData::Active:
            break;
        case JsonData::SendDataWithConfirm:
            {
                if(rData.targetTelephone != "")
                {
                    if( userlist.contains(rData.targetTelephone))
                    {
                        QDateTime now = QDateTime::currentDateTime();
                        qDebug()<<"now: "<<now.toString("yyyy-MM-dd HH:mm:ss");
                        const UserInfo& tUInfo = userlist[rData.targetTelephone];
                        if( tUInfo.lastActiveTime.secsTo(now) < 100000)
                        {
                            QByteArray data = QString("send success\n").toLocal8Bit();
                            sendData(data,commingAddr,commingPort);

                            qDebug()<<"commingAddr: "<<commingAddr.toString()<<endl;
                            qDebug()<<"commingPort: "<<commingPort<<endl;

                            qDebug()<<"tUInfo.address: "<<tUInfo.address.toString()<<endl;
                            qDebug()<<"tUInfo.port: "<<tUInfo.port<<endl;
                            sendData(rData.data,tUInfo.address,tUInfo.port);
                        } else {
                            QByteArray data = QString("targetTelephone is too long unactive").toLocal8Bit();
                            sendData(data,commingAddr,commingPort);
                        }
                    } else {
                        QByteArray data = QString("no user telephone is %1").arg(rData.targetTelephone).toLocal8Bit();
                        sendData(data,commingAddr,commingPort);
                    }
                }
                else{
                    qDebug()<<"targetTelphone is null"<<endl;
                }
            }
            break;
        case JsonData::SendDataWithoutConfirm:
            {
                if(rData.targetTelephone != "")
                {
                    if( userlist.contains(rData.targetTelephone))
                    {
                        const UserInfo& tUInfo = userlist[rData.targetTelephone];
                        sendData(rData.data,tUInfo.address,tUInfo.port);
                    }
                }
                else if(rData.targetIP != 0 && rData.targetPort != 0)
                {
                    sendData(rData.data,QHostAddress(rData.targetIP),rData.targetPort);
                }
            }
            break;
    }
}

void Manager::sendData(QByteArray &data, QHostAddress targetAddress, int targetPort)
{
    //targetPort = 8008;
    qDebug()<<"senddata: "<<data<<endl;
    mUdpSocket.writeDatagram(data, targetAddress,targetPort);
    mUdpSocket.waitForBytesWritten(10);
    mUdpSocket.flush();
}
