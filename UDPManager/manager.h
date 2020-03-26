#ifndef MANAGER_H
#define MANAGER_H


#include <QObject>
#include <QUdpSocket>

#include "userinfo.h"


class Manager: public QObject
{
    Q_OBJECT
public:
    Manager();

private slots:
    void onReceiveData();

private:
    QUdpSocket mUdpSocket;

    void sendData(QByteArray& data,QHostAddress targetAddress,int targetPort);

    QMap<QString, UserInfo> userlist;
};

#endif // MANAGER_H
