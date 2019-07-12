#include "datamodel.h"

#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include <exception>

DataModel::DataModel(QObject *parent)
    : QObject(parent)
{ }

bool DataModel::readWebsitesList(const QString &filename)
{
    clear();

    QFileInfo fileStatus(filename);
    if (!fileStatus.exists() || !fileStatus.isFile()) {
        qCritical().noquote() << "File not exists '" + filename + "'.";
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

    QJsonObject root = document.object();
    if (!storeWebsitesDetails(root)) {
        qCritical() << "File '" + filename + "' is a correct JSON document but has incorrect tags or values";
        return false;
    }
    return true;
}

bool DataModel::storeWebsitesDetails(QJsonObject &root)
{
    QJsonArray websites = root.value("websites").toArray();

    for (QJsonValue webVal : websites) {
        if (!webVal.isObject())
            return false;
        QJsonObject webObj = webVal.toObject();

        QJsonValue nameVal = webObj.value("name");
        QJsonValue urlVal = webObj.value("url");
        QJsonValue iconVal = webObj.value("icon");
        if (!nameVal.isString() || !urlVal.isString() || !iconVal.isString())
            return false;

        m_names.push_back(nameVal.toString());
        m_urls.push_back(urlVal.toString());
        m_icons.push_back(webIconsDirName + iconVal.toString());
    }

    assert (m_names.count() == m_urls.count());
    assert (m_names.count() == m_icons.count());
    m_count = m_names.count();

    validateIconFiles();
    return true;
}

void DataModel::validateIconFiles()
{
    for (QString &filename : m_icons) {
        QFileInfo fileStatus(filename);
        if (!fileStatus.exists() || !fileStatus.isFile())
            filename = "";
        else
            filename = "file:" + filename;
    }
}

void DataModel::clear()
{
    m_count = 0;
    m_names.clear();
    m_urls.clear();
    m_icons.clear();
}

QString DataModel::status() const
{
    return m_status;
}

int DataModel::count() const
{
    return m_count;
}

QString DataModel::name(int index) const
{
    if(index < 0 || index > m_count)
        return "";
    return m_names[index];
}

QString DataModel::url(int index) const
{
    if(index < 0 || index > m_count)
        return "";
    return m_urls[index];
}

QString DataModel::icon(int index) const
{
    if(index < 0 || index > m_count)
        return "";
    return m_icons[index];
}

bool DataModel::openUrl(int index) const
{
    auto web_url = url(index);
    if (web_url.isNull() || web_url.isEmpty())
        return false;
    return QDesktopServices::openUrl(QUrl(url(index), QUrl::TolerantMode));
}

void DataModel::setStatus(QString status)
{
    if (m_status == status)
        return;

    m_status = status;
    emit statusChanged(m_status);
}
