#include "manager.h"
#include "websitesmodel.h"
#include "documentsmodel.h"
#include "downloader.h"

#include <QCoreApplication>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>
#include <QThread>
#include <QSettings>


Manager::Manager(QObject *parent) : QObject(parent)
{
    m_websModel = new WebsitesModel(this);
    m_docsModel = new DocumentsModel(this);
    m_downloader = new Downloader(this);
    m_downloader->setManager(this);

    connect(m_downloader, &Downloader::fileDownloaded, this, &Manager::fileDownloaded);
}

// ------------------- READ CONFIGS ------------------

bool Manager::initialize()
{
    copyInitialResourcesIfNecessarily();

    bool isSuccess = true;
    isSuccess |= readAppConfig();
    isSuccess |= readWebsitesConfig(m_resourcesFullPath + m_websJsonName, m_websModel);
    isSuccess |= readDocumentsConfig(m_resourcesFullPath + m_docsJsonName, m_docsModel);
    return isSuccess;
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

bool Manager::readWebsitesConfig(const QString &websJsonPath, WebsitesModel *websModel)
{
    websModel->clear();
    QJsonObject root;

    if (readJsonFile(websJsonPath, root) == false)
        return false;

    if (extractWebsFromJson(root, websModel) == false) {
        qCritical() << "File '" + websJsonPath + "' is a correct JSON document but has incorrect tags or values";
        websModel->clear();
        return false;
    }
    return true;
}

bool Manager::extractWebsFromJson(const QJsonObject &root, WebsitesModel *websModel)
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

        Resource web;
        web.name = nameVal.toString();
        web.url = urlVal.toString();
        if (isUpdating()) {
            web.icon = iconVal.toString();
        } else{
            web.icon = m_resourcesFullPath + iconVal.toString();
            validateFilePath(web.icon);
        }

        websModel->addWebsite(web);
    }

    return true;
}

void Manager::validateFilePath(QString &filePath)
{
    QFileInfo fileStatus(filePath);
    if (fileStatus.exists() == false || fileStatus.isFile() == false) {
        qWarning().noquote().nospace()
                // << __FILE__ << ":" << __LINE__ << ":  "
                << "File not found '" << filePath << "'.";
        filePath = "";
    }
    else {
        filePath = "file:" + filePath;
    }
}

bool Manager::readDocumentsConfig(const QString &docsJsonPath, DocumentsModel *docsModel)
{
    docsModel->clear();
    QJsonObject root;

    if (readJsonFile(docsJsonPath, root) == false)
        return false;

    if (extractDocsFromJson(root, docsModel) == false) {
        qCritical() << "File '" + docsJsonPath + "' is a correct JSON document but has incorrect tags or values";
        docsModel->clear();
        return false;
    }
    return true;
}

bool Manager::extractDocsFromJson(const QJsonObject &root, DocumentsModel *docsModel)
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
                || pathVal.isString() == false)
            return false;

        Resource doc;
        doc.name = nameVal.toString();
        doc.url = urlVal.toString();
        doc.timestamp = timestampVal.toString();
        if (isUpdating()) {
            doc.path = m_updatesFullPath + pathVal.toString();
        } else {
            doc.path = m_resourcesFullPath + pathVal.toString();
            validateFilePath(doc.path);
        }
        docsModel->addDocument(doc);
    }

    return true;
}


void Manager::copyInitialResourcesIfNecessarily()
{
    copyDirsAndFiles(QCoreApplication::applicationDirPath() + "/" + m_resourcesDirName + "/",
            m_resourcesFullPath);
}

void Manager::copyDirsAndFiles(const QString &srcDirPath, const QString &destDirPath) const
{
    QDir srcDir(srcDirPath);
    QDir destDir(destDirPath);

    if (srcDir.exists() == false || srcDir.isReadable() == false)
        return;

    if (destDir.exists() == false)
        destDir.mkpath(destDirPath);

    QFileInfoList files = srcDir.entryInfoList();
    for (auto &srcFile : files) {
        if (srcFile.isReadable() == false
                || srcFile.isSymLink() == true
                || srcFile.fileName() == "."
                || srcFile.fileName() == ".." )
            continue;

        if (srcFile.isDir()) {
            copyDirsAndFiles(srcFile.filePath() + "/", destDirPath + srcFile.fileName() + "/");
            continue;
        }

        if (srcFile.isFile() == false)
            continue;

        QFileInfo destFile(destDirPath + srcFile.fileName());
        if (destFile.exists())
            continue;

        QFile::copy(srcFile.filePath(), destFile.filePath());
    }
}

bool Manager::readAppConfig()
{
    auto val = QSettings(m_resourcesFullPath + m_appConfigFileName, QSettings::IniFormat)
            .value("serverUrl");

    // TODO store settings

    if (val.isNull())
        return false;

    m_serverUrl = val.toString();
    return true;
}

// ------------------- UPDATE ------------------

void Manager::update()
{
    if (isUpdating() == true || isUpdateNeeded() == false)
        return;

    setIsUpdating(true);

    QDir dir(m_updatesFullPath);
    dir.removeRecursively();

    m_downloader->clear();
    downloadConfigs();
}

bool Manager::isUpdateNeeded() {
    // TODO
    return true;
}

void Manager::downloadConfigs()
{
    QVector<Resource> toGetList;
    toGetList.push_back({ });
    toGetList.back().url = m_serverUrl + m_websJsonName;
    toGetList.back().path = m_updatesFullPath + m_websJsonName;
    toGetList.push_back({ });
    toGetList.back().url = m_serverUrl + m_docsJsonName;
    toGetList.back().path =  m_updatesFullPath + m_docsJsonName;

    m_currentState = DownloadConfigs;
    m_successfullRequestCounter = 0;
    m_totalRequests = toGetList.size();
    m_waitingRequestsCounter = toGetList.size();
    for (auto &r : toGetList)
        m_downloader->downloadFile(r);
}

void Manager::downloadFiles()
{
    QThread::sleep(1); // TODO remove

    WebsitesModel tmpWebsModel;
    DocumentsModel tmpDocsModel;

    bool isSuccess = true;
    isSuccess |= readWebsitesConfig(m_updatesFullPath + m_websJsonName, &tmpWebsModel);
    isSuccess |= readDocumentsConfig(m_updatesFullPath + m_docsJsonName, &tmpDocsModel);
    if (isSuccess == false) {
        qInfo() << __FILE__ << __LINE__ << "Update failed. Cannot read jsons.";
        return;
    }

    QVector<Resource> toGetList;
    toGetList.reserve(tmpWebsModel.count() + tmpDocsModel.rowCount());
    for (auto &r : tmpWebsModel.getResources()) {
        toGetList.push_back({ });
        toGetList.back().url = m_serverUrl + r.icon;
        toGetList.back().path = m_updatesFullPath + r.icon;
    }
    toGetList << tmpDocsModel.getResources();

    if (toGetList.count() == 0)
        return;

    m_currentState = DownloadFiles;
    m_successfullRequestCounter = 0;
    m_totalRequests = toGetList.size();
    m_waitingRequestsCounter = toGetList.size();
    for (auto &r : toGetList)
        //        qInfo() << r.url << r.path;
        m_downloader->downloadFile(r);
}

void Manager::fileDownloaded(QString url, bool status)
{
    m_waitingRequestsCounter--;
    m_successfullRequestCounter += status;

    if (status == false) {
        qWarning() << "Failed to download resource: " + url;
    }

    if (m_waitingRequestsCounter != 0)
        return;

    if (m_successfullRequestCounter != m_totalRequests) {
        return finishUpdate(false);
    }

    switch (m_currentState) {

    case DownloadConfigs:
        return downloadFiles();

    case DownloadFiles:
        deployUpdate();
        finishUpdate(true);
        initialize();
        return;

    default:
        qWarning() << __FILE__ << __LINE__ << "Illegal state. Sth went wrong.";
        return finishUpdate(false);
    }
}

void Manager::finishUpdate(bool success)
{
    m_currentState= Idle;
    setIsUpdating(false);
    if (success == false)
        qWarning() << "Update failed.";
}

void Manager::deployUpdate()
{
    QDir oldDir(m_resourcesFullPath);
    oldDir.removeRecursively();

    QDir dataDir(m_dataDirPath);
    dataDir.rename(m_updatesFullPath, m_resourcesFullPath);
}

// ------------------- OTHER ------------------

bool Manager::openUrl(const QString &url) const
{
    return QDesktopServices::openUrl(QUrl(url, QUrl::TolerantMode));
}

QString Manager::statusMsg() const
{
    return m_statusMsg;
}

void Manager::setIsUpdating(bool isUpdating)
{
    if (m_isUpdating == isUpdating)
        return;

    m_isUpdating = isUpdating;
    emit isUpdatingChanged(m_isUpdating);
}


bool Manager::isUpdating() const
{
    return m_isUpdating;
}

DocumentsModel *Manager::getDocumentsModel() const
{
    return m_docsModel;
}

WebsitesModel *Manager::getWebsitesModel() const
{
    return m_websModel;
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