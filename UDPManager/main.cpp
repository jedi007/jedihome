#include <QCoreApplication>

#include <QDebug>
#include "manager.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug()<<"hello"<<endl;

    Manager* udpManager = new Manager();


    return a.exec();
}
