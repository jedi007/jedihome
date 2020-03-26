#ifndef JSONMANAGER_H
#define JSONMANAGER_H


#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>


class JsonData
{
public:
    enum Action{Active};
    
    JsonData();
    
    QString ID;
    QString telphone;
    Action m_action;
    
    QByteArray data;
    
    QString targetID;
    QString targetTelephone;
    QString targetIP;
    qint64 targetPort;
    
    
};

class JsonManager
{
public:
    JsonManager();


    void saveJson();
    JsonData readJson(const QByteArray& byteArray);
};


#endif // JSONMANAGER_H
