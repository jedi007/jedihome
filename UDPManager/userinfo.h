#ifndef USERINFO_H
#define USERINFO_H

#include <QHostAddress>
#include <QDateTime>

class UserInfo
{
public:
    UserInfo(QHostAddress paddress,quint16 pport);

    QHostAddress address;
    quint16 port;
    QDateTime lastActiveTime;
};

#endif // USERINFO_H
