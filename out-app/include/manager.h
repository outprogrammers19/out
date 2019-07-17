#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>

class DocumentsModel;
//class WebsitesModel;
#include "websitesmodel.h"

class Manager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString statusMsg READ statusMsg WRITE setStatusMsg NOTIFY statusMsgChanged)

public:
    explicit Manager(QObject *parent = nullptr);

    bool readAppConfig(const QString &filePath);
    bool readWebsitesConfig(WebsitesModel &websModel);
    bool readDocumentsConfig(DocumentsModel &docsModel);
    QString statusMsg() const;

signals:

    void statusMsgChanged(QString statusMsg);

public slots:
    bool openUrl(const QString &url) const;
    void setStatusMsg(QString statusMsg);
    QString filenameFromPath(const QString &path) const;

private:

    bool readJsonFile(const QString &filename, QJsonObject &root);
    bool extractWebsFromJson(const QJsonObject &root, WebsitesModel &websModel);
    bool extractDocsFromJson(const QJsonObject &root, DocumentsModel &docsModel);
    void validateFilePath(QString &icon);

    QString m_statusMsg;

    // TODO remove:
    QString m_websJsonPath = "config/websites-list.json";
    QString m_docsJsonPath = "config/documents-list.json";
    // NOTE: no need for that?
    //#ifdef Q_OS_WIN
    //    const QString websIconsDir = "websites-icons\\";
    //#else
    const QString websIconsDirName = "websites-icons/";
    const QString docsDirName = "/documents/";
    //#endif
};

#endif // MANAGER_H
