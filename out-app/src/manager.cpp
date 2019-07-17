#include "include/manager.h"
#include "websitesmodel.h"
#include "documentsmodel.h"

#include <QCoreApplication>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>


Manager::Manager(QObject *parent) : QObject(parent)
{ }

bool Manager::readAppConfig(const QString &filePath)
{
    return true;
}

bool Manager::readJsonFile(const QString &filename, QJsonObject &root)
{
    QFileInfo fileStatus(filename);
    if (!fileStatus.exists() || !fileStatus.isFile()) {
        qCritical().noquote() << "File not found '" + filename + "'.";
        return false; // TODO error
    }

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical().noquote() << "Failed to open file '" + filename + "'.";
        return false; // TODO error
    }

    QString content = file.readAll();
    file.close();
    QJsonDocument document = QJsonDocument::fromJson(content.toUtf8());

    if (document.isNull()) {
        qCritical().noquote() << "File '" + filename + "' is not a correct JSON document.";
        return false; // TODO error
    }

    root = document.object();
    return true;
}

bool Manager::readWebsitesConfig(WebsitesModel &websModel)
{
    websModel.clear();
    QJsonObject root;

    if (readJsonFile(m_websJsonPath, root) == false)
        return false;

    if (extractWebsFromJson(root, websModel) == false) {
        qCritical() << "File '" + m_websJsonPath + "' is a correct JSON document but has incorrect tags or values";
        websModel.clear();
        return false;
    }
    return true;
}

bool Manager::extractWebsFromJson(const QJsonObject &root, WebsitesModel &websModel)
{
    QJsonArray websites = root.value("websites").toArray();

    for (QJsonValue webVal : websites) {
        if (!webVal.isObject())
            return false;
        QJsonObject webObj = webVal.toObject();

        QJsonValue nameVal = webObj.value("name");
        QJsonValue urlVal = webObj.value("url");
        QJsonValue iconVal = webObj.value("icon");
        if (nameVal.isString() == false
                || urlVal.isString() == false
                || iconVal.isString() == false)
            return false;

        WebsitesModel::Website web;
        web.name = nameVal.toString();
        web.url = urlVal.toString();
        web.icon = websIconsDirName + iconVal.toString();
        validateFilePath(web.icon);

        websModel.addWebsite(web);
    }

    return true;
}

void Manager::validateFilePath(QString &filePath)
{
    QFileInfo fileStatus(filePath);
    if (fileStatus.exists() == false || fileStatus.isFile() == false) {
        qWarning().noquote().nospace()
                // << __FILE__ << ":" << __LINE__ << ":  "
                << "Failed to open file '" << filePath << "'.";
        filePath = "";
    }
    else {
        filePath = "file:" + filePath;
    }
}

bool Manager::readDocumentsConfig(DocumentsModel &docsModel)
{
    docsModel.clear();
    QJsonObject root;

    if (readJsonFile(m_docsJsonPath, root) == false)
        return false;

    if (extractDocsFromJson(root, docsModel) == false) {
        qCritical() << "File '" + m_docsJsonPath + "' is a correct JSON document but has incorrect tags or values";
        docsModel.clear();
        return false;
    }
    return true;
}

bool Manager::extractDocsFromJson(const QJsonObject &root, DocumentsModel &docsModel)
{
    QJsonArray documents = root.value("documents").toArray();

    for (QJsonValue docVal : documents) {
        if (!docVal.isObject())
            return false;
        QJsonObject docObj = docVal.toObject();

        QJsonValue nameVal = docObj.value("name");
        QJsonValue urlVal = docObj.value("url");
        QJsonValue pathVal = docObj.value("path");
        QJsonValue timestampVal = docObj.value("timestamp");

        if (nameVal.isString() ==false
                || urlVal.isString() == false
                || pathVal.isString() == false
                || timestampVal.isString() == false)
            return false;

        DocumentsModel::Document doc;
        doc.name = nameVal.toString();
        doc.url = urlVal.toString();
        doc.path = QCoreApplication::applicationDirPath() + docsDirName + pathVal.toString(); // TODO doc.path
        doc.timestamp = timestampVal.toString(); // TODO doc.timestamp
        validateFilePath(doc.path);

        qInfo() << doc.path;
        docsModel.addDocument(doc);
    }

    return true;
}

bool Manager::openUrl(const QString &url) const
{
    return QDesktopServices::openUrl(QUrl(url, QUrl::TolerantMode));
}

QString Manager::statusMsg() const
{
    return m_statusMsg;
}

void Manager::setStatusMsg(QString statusMsg)
{
    if (m_statusMsg == statusMsg)
        return;

    m_statusMsg = statusMsg;
    emit statusMsgChanged(m_statusMsg);
}

QString Manager::filenameFromPath(const QString &path) const
{
    return QFileInfo(path).fileName();
}
