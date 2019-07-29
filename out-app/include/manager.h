#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QDir>
#include <QStandardPaths>

class DocumentsModel;
class WebsitesModel;
class Downloader;
#include "websitesmodel.h"

class Manager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isUpdating READ isUpdating NOTIFY isUpdatingChanged)
    Q_PROPERTY(bool rescaled READ rescaled WRITE setRescaled NOTIFY rescaledChanged)
    Q_PROPERTY(QString statusMsg READ statusMsg WRITE setStatusMsg NOTIFY statusMsgChanged)

    enum UpdateState {
        Idle, DownloadConfigs, DownloadFiles
    };

public:
    explicit Manager(QObject *parent = nullptr);
    bool initialize();

    QString statusMsg() const;
    bool isUpdating() const;
    DocumentsModel* getDocumentsModel() const;
    WebsitesModel* getWebsitesModel() const;
    bool rescaled() const;

signals:
    void statusMsgChanged(QString statusMsg);
    void isUpdatingChanged(bool isUpdating);
    void rescaledChanged(bool rescaled);
    void updateFinished(bool status);

public slots:
    bool openUrl(const QString &url) const;
    void setStatusMsg(QString statusMsg);
    QString filenameFromPath(const QString &path) const;
    void update();
    void fileDownloaded(QString url, bool status);
    void setRescaled(bool rescaled);

private:
    bool readAppConfig();
    void copyInitialResourcesIfNecessarily();
    bool readWebsitesConfig(const QString &websJsonPath, WebsitesModel *websModel);
    bool readDocumentsConfig(const QString &docsJsonPath, DocumentsModel *docsModel);

    bool readJsonFile(const QString &filename, QJsonObject &root);
    bool extractWebsFromJson(const QJsonObject &root, WebsitesModel *websModel);
    bool extractDocsFromJson(const QJsonObject &root, DocumentsModel *docsModel);
    void validateFilePath(QString &icon);

    bool isUpdateNeeded();
    void downloadConfigs();
    void downloadFiles();

    void setIsUpdating(bool isUpdating);
    void finishUpdate(bool success);
    void deployUpdate();

    void copyDirsAndFiles(const QString &srcDirPath, const QString &destDirPath) const;

    QString m_statusMsg;

    bool m_isUpdating = false;
    int m_totalRequests = 0;
    int m_waitingRequestsCounter = 0;
    int m_successfullRequestCounter = 0;

    WebsitesModel *m_websModel = nullptr;
    DocumentsModel *m_docsModel = nullptr;
    Downloader *m_downloader = nullptr;

//    QString m_serverUrl = "http://localhost/out/";
    QString m_appConfigFileName = "config.ini";
    QString m_serverUrl = "";

    // TODO move to config?
    QString m_dataDirPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QString m_resourcesDirName = "resources";
    QString m_updatesDirName = "updates";
    QString m_resourcesFullPath = m_dataDirPath + "/" + m_resourcesDirName + "/";
    QString m_updatesFullPath = m_dataDirPath + "/"+ m_updatesDirName + "/";
    QString m_websJsonName = "websites-list.json";
    QString m_docsJsonName = "documents-list.json";
    QString m_webIconsDirName = "websites-icons";

    UpdateState m_currentState = Idle;
    bool m_rescaled = false;
};

#endif // MANAGER_H
