#include "userinfo.h"


UserInfo::UserInfo(QHostAddress paddress, quint16 pport,QString pID,QString ptelephone)
    :address(paddress),port(pport),ID(pID),telephone(ptelephone)
{

}
