#ifndef USERINFO_H
#define USERINFO_H

#include <QHostAddress>
#include <QDateTime>

class UserInfo
{

public:
    UserInfo(){}
    UserInfo(QHostAddress paddress,quint16 pport,QString pID,QString ptelephone);
    // 重载=号使得 obj = "Hello" 能够成立
    UserInfo & operator= (const UserInfo& s)
    {
        ID = s.ID;
        telephone = s.telephone;
        address = s.address;
        port = s.port;
        lastActiveTime = s.lastActiveTime;

        // 返回该对象
        return *this;
    }

    QString ID;
    QString telephone;
    QHostAddress address;
    quint16 port;
    QDateTime lastActiveTime;
};

#endif // USERINFO_H
