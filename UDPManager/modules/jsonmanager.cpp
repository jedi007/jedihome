#include "jsonmanager.h"

/*
{
    "Company": "Digia",
    "From": 1991,
    "Name": "Qt",
    "Page": {
        "Developers": "https://www.qt.io/developers/",
        "Download": "https://www.qt.io/download/",
        "Home": "https://www.qt.io/"
    },
    "Version": [
        4.8,
        5.2,
        5.7
    ]
}
*/

JsonManager jsontest;//仅用于开发调试

JsonManager::JsonManager()
{

}

void JsonManager::saveJson()
{
    // 构建 Json 数组 - Version
    QJsonArray versionArray;
    versionArray.append(4.8);
    versionArray.append(5.2);
    versionArray.append(5.7);

    // 构建 Json 对象 - Page
    QJsonObject pageObject;
    pageObject.insert("Home", "https://www.qt.io/");
    pageObject.insert("Download", "https://www.qt.io/download/");
    pageObject.insert("Developers", "https://www.qt.io/developers/");

    // 构建 Json 对象
    QJsonObject json;
    json.insert("Name", "Qt");
    json.insert("Company", "Digia");
    json.insert("From", 1991);
    json.insert("Version", QJsonValue(versionArray));
    json.insert("Page", QJsonValue(pageObject));

    // 构建 Json 文档
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    QString strJson(byteArray);

    qDebug() << strJson;

    QFile file("test.json");
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(byteArray);
        file.close();
    }
}


JsonData JsonManager::readJson(const QByteArray& byteArray)
{
    QJsonParseError jsonError;
    JsonData jData;
    QJsonDocument doucment = QJsonDocument::fromJson(byteArray, &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
        qDebug()<<"success read json"<<endl;
        if (doucment.isObject()) {  // JSON 文档为对象
            QJsonObject object = doucment.object();  // 转化为对象
            if (object.contains("telephone")) {
                QJsonValue value = object.value("telephone");
                if (value.isString()) {
                    jData.telphone = value.toString();
                }
            }
            if (object.contains("ID")) {
                QJsonValue value = object.value("ID");
                if (value.isString()) {
                    jData.ID = value.toString();
                }
            }
            if (object.contains("action")) {
                QJsonValue value = object.value("action");
                if (value.isDouble()) {
                    int action = value.toInt();
                    qDebug()<<"receive action is "<<action<<endl;
                    switch (action) {
                        case 0:
                            jData.m_action = JsonData::Active;
                            break;
                        case 1:
                            jData.m_action = JsonData::SendDataWithConfirm;
                            break;
                        case 2:
                            jData.m_action = JsonData::SendDataWithoutConfirm;
                            break;
                        default:
                            jData.m_action = JsonData::Active;
                    }
                }
            }
            if (object.contains("targetID")) {
                QJsonValue value = object.value("targetID");
                if (value.isString()) {
                    jData.targetID = value.toString();
                }
            }
            if (object.contains("targetIP")) {
                QJsonValue value = object.value("targetIP");
                if (value.isString()) {
                    jData.targetIP = value.toString();
                }
            }
            if (object.contains("targetPort")) {
                QJsonValue value = object.value("ID");
                if (value.isDouble()) {
                    jData.targetPort = value.toInt();
                }
            }
            if (object.contains("targetTelephone")) {
                QJsonValue value = object.value("targetTelephone");
                if (value.isString()) {
                    jData.targetTelephone = value.toString();
                }
            }
        }
    }
    else{
        qDebug()<<"its not json"<<endl;
    }

    return jData;
}

JsonData::JsonData()
{
    targetPort = 0;
    m_action = Active;
}
