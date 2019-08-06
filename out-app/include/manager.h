/**
 * @file manager.h
 * @author Jakub Precht
 * @date 2019-08-06
 */

#ifndef MANAGER_H
#define MANAGER_H

#include "websitesmodel.h"
class DocumentsModel;
class Downloader;
class QSettings;

#include <QObject>
#include <QDir>
#include <QStandardPaths>

/**
 * @brief The Manager class is responsible for responding to user actions.
 *
 * Most of the application logic connecting GUI with other resources is written here.
 */
class Manager : public QObject
{
    Q_OBJECT

    /**
     * @brief This property tells if an update is being currently carried out
     */
    Q_PROPERTY(bool isUpdating READ isUpdating NOTIFY isUpdatingChanged)

    /**
     * @brief This property is used by QML items to tell each other that they should rescale the content
     */
    Q_PROPERTY(bool rescaled READ rescaled WRITE setRescaled NOTIFY rescaledChanged)

    /**
     * @brief This property is used to display message at the bottom of the application window.
     */
    Q_PROPERTY(QString statusMsg READ statusMsg WRITE setStatusMsg NOTIFY statusMsgChanged)

    /**
     * @brief This property determines the scale factor for GUI. Sizes of all elements in GUI are determined based on this value.
     */
    Q_PROPERTY(double guiScaleFactor READ guiScaleFactor WRITE setGuiScaleFactor NOTIFY guiScaleFactorChanged)

    /**
     * @brief The UpdateState enum defines 3 states that an update can be in.
     *
     * <b>Idle</b> when no update is being carried out, <b>DownloadConfigs</b> when manager is currently downloading configuration files
     * (such as websites-list.json and documents-list.json) and <b>DownloadFiles</b> when manager processed configs and now is
     * downloading new or updating resources.
     */
    enum UpdateState {
        Idle, DownloadConfigs, DownloadFiles
    };

public:
    /**
     * @brief Default constructor.
     * @param parent pointer to an instance of QObject; if not null, this class will be deleted automatically when
     * pointed parent object is deleted
     *
     * It constructs instances of WebsitesModel, DocumentsModel and Downloader.
     * It connects Downloader::fileDownloaded() signal with a private handler fileDownloaded().
     */
    explicit Manager(QObject *parent = nullptr);

    /**
     * @brief Loads settings and configuration
     * @return true if successfully initialized
     *
     * Calls readAppConfig(), readWebsitesConfig() and readDocumentsConfig().
     *
     * All configurations and resources are stored in <b>resources</b> directory in user's default data folder.
     * During the first run of the application these files are copied from application install location (so that application can also work
     * without internet connection) and then are replaced during updates.
     *
     * Linux's typical location of data folder is <em>/home/USER_NAME/.local/share/OUT/</em> and for Windows' is <em>C:/Users/USER_NAME/AppData/Local/OUT/</em>.
     */
    bool initialize();

    /**
     * @brief Getter method for statusMsg property
     * @return QString to be displayed at the bottom on application window
     */
    QString statusMsg() const;

    /**
     * @brief Getter method for isUpdating property
     * @return true if update is being currently carried out
     */
    bool isUpdating() const;

    /**
     * @return pointer to DocumentsModel used by Manager
     */
    DocumentsModel* getDocumentsModel() const;

    /**
     * @return pointer to DocumentsModel used by Manager
     */
    WebsitesModel* getWebsitesModel() const;

    /**
     * @brief Getter method for statusMsg property
     * @return true if application should rescale GUI items
     */
    bool rescaled() const;

    /**
     * @brief getter method for guiScaleFactor property
     * @return current scale factor
     */
    double guiScaleFactor() const;

signals:
    /**
     * @brief changed signal for statusMsg property
     * @param statusMsg new status message
     */
    void statusMsgChanged(QString statusMsg);

    /**
     * @brief changed signal for isUpdating property
     * @param isUpdating true if update has just started, false if update has just finished
     */
    void isUpdatingChanged(bool isUpdating);

    /**
     * @brief changed signal for rescaled property
     * @param rescaled true if rescaled, false if already applied rescaling
     */
    void rescaledChanged(bool rescaled);

    /**
     * @brief signal emitted at the end of update
     * @param status true if update succeeded, otherwise false
     */
    void updateFinished(bool status);

    /**
     * @brief changed signal for guiScaleFactor property
     * @param guiScaleFactor new value of the scale factor
     */
    void guiScaleFactorChanged(double guiScaleFactor);

public slots:
    /**
     * @brief Open resource described by url with system's default application.
     * @param url Path to the resource. It can be an online link or a path to local file.
     * @return true if succeed
     *
     * For websites links this should be default web-browser, but local files should be open
     * by correct application, like PDF file should be opened by default PDF reader.
     */
    bool openUrl(const QString &url) const;

    /**
     * @brief setter method for statusMsg property
     */
    void setStatusMsg(QString statusMsg);

    /**
     * @brief Get file name from a full file path.
     * @param path to a file (can be absolute or relative).
     * @return Name of the file as a QString.
     */
    QString filenameFromPath(const QString &path) const;

    /**
     * @brief Update application configuration and resources.
     *
     * This operation will first check for new 'documents-list.json' and 'websites-list.json'.
     * If there aren't any changes compared to current application state, then the update will
     * finish after this step.
     *
     * If there are new changes (for example new website link or a new document to download) then
     * all files are downloaded and stored in <b>updates</b> folder next to <b>resources</b> folder
     * created by initialize() function.
     *
     * Finally, <b>resource</b> directory is deleted and <b>updates</b> directory is renamed to <b>resources</b>.
     *
     * After update finishes, a updateFinished(bool) signal is emitted.
     */
    void update();

    /**
     * @brief Handler of Downloader::fileDownloaded() signals.
     *
     * This method counts if all requests have been finished and then performs further actions
     * depending on the processed requests type. It can either: change state from DownloadConfigs to DownloadFiles (and call Downloader
     * class to download all new files) or it can call methods to propagate changes and finish update.
     *
     * @param url of the file just downloaded
     * @param status of network replay - was the download successful?
     */
    void fileDownloaded(QString url, bool status);

    /**
     * @brief setter method for rescaled property
     * @param rescaled true if was rescaled
     */
    void setRescaled(bool rescaled);

    /**
     * @brief Setter method for guiScaleFactor property
     * @param guiScaleFactor new factor
     */
    void setGuiScaleFactor(double guiScaleFactor);

private:
    // private methods:

    /**
     * @brief Read configuration from file specified by 'm_appConfigFileName' variable.
     * @return true if successfully read config
     */
    bool readAppConfig();

    /**
     * @brief This method is called upon app startup and copies default resources to data directory if there aren't any already.
     */
    void copyInitialResourcesIfNecessarily();

    /**
     * @brief Read JSON describing websites links displayed in app.
     * @param websJsonPath path to JSON file
     * @param websModel pointer to instance of WebsitesModel to which the read data should be written
     * @return true upon success
     */
    bool readWebsitesConfig(const QString &websJsonPath, WebsitesModel *websModel);

    /**
     * @brief  Read JSON describing documents displayed in app.
     * @param docsJsonPath path to JSON file
     * @param docsModel pointer to instance of DocumentsModel to which the read data should be written
     * @return true upon success
     */
    bool readDocumentsConfig(const QString &docsJsonPath, DocumentsModel *docsModel);

    /**
     * @brief Open JSON file, parse and return the root object in JSON hierarchy
     * @param filename path to JSON file
     * @param root reference to root object, after successful read to this object will be assigned the root element of JSON hierarchy.
     * @return true upon success
     */
    bool readJsonFile(const QString &filename, QJsonObject &root);

    /**
     * @brief Goes down the the JSON hierarchy and extracts data about websites links.
     * @param root is the root object in JSON hierarchy
     * @param websModel pointer to WebsitesModel where the extracted data should be written.
     * @return
     */
    bool extractWebsFromJson(const QJsonObject &root, WebsitesModel *websModel);

    /**
     * @brief Goes down the the JSON hierarchy and extracts data about documents.
     * @param root is the root object in JSON hierarchy
     * @param docsModel pointer to DocumentsModel where the extracted data should be written.
     * @return
     */
    bool extractDocsFromJson(const QJsonObject &root, DocumentsModel *docsModel);

    /**
     * @brief Validate path, if file don't exists assign empty string
     * @param path is a reference to path that is supposed to be validated
     */
    void validateFilePath(QString &path);

    /**
     * @brief Download configuration files from server.
     */
    void downloadConfigs();

    /**
     * @brief Download files from server which are listed in downloaded configs.
     */
    void downloadFiles();

    /**
     * @brief Setter method for isUpdating property
     */
    void setIsUpdating(bool isUpdating);

    /**
     * @brief Called at the end of update. Will emit updateFinished signal.
     * @param success true if update was successful
     */
    void finishUpdate(bool success);

    /**
     * @brief This method saves new files in data directory.
     *
     * It first deletes current <b>resources</b> folder and then renames <b>updates</b> folder to <b>resources</b>
     */
    void deployUpdate();

    /**
     * @brief Copy recursively source folder to destination folder.
     * @param srcDirPath folder from which it will copy
     * @param destDirPath folder into which it will copy
     */
    void copyDirsAndFiles(const QString &srcDirPath, const QString &destDirPath) const;

    // private members:

    QString m_statusMsg;

    bool m_isUpdating = false;
    int m_totalRequests = 0;
    int m_waitingRequestsCounter = 0;
    int m_successfullRequestCounter = 0;

    WebsitesModel *m_websModel = nullptr;
    DocumentsModel *m_docsModel = nullptr;
    Downloader *m_downloader = nullptr;

    QString m_serverUrl = "";
    QString m_dataDirPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    QString m_appConfigFileName = "config.ini";
    QString m_appConfigFullPath = m_dataDirPath + "/" + m_appConfigFileName;

    QString m_resourcesDirName = "resources";
    QString m_updatesDirName = "updates";
    QString m_resourcesFullPath = m_dataDirPath + "/" + m_resourcesDirName + "/";
    QString m_updatesFullPath = m_dataDirPath + "/"+ m_updatesDirName + "/";
    QString m_websJsonName = "websites-list.json";
    QString m_docsJsonName = "documents-list.json";
    QString m_webIconsDirName = "websites-icons";

    UpdateState m_currentState = Idle;
    bool m_rescaled = false;

    QSettings *m_settings = nullptr;
    double m_guiScaleFactor = 1.0;
};

#endif // MANAGER_H
