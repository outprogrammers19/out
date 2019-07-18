#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QSharedPointer>
#include <QMap>
#include "resource.h"

class QNetworkAccessManager;
class QNetworkReply;
class Manager;

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = nullptr);
    void setManager(const Manager *manager);
    void clear();

signals:
    void headerDownloaded(QString url, bool status, QString timestamp);
    void fileDownloaded(QString url, bool status);

public slots:    
    void downloadHeader(const Resource &resource);
    void downloadFile(const Resource &resource);
    void replyFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_network;
    const Manager *m_manager;

    QMap<QString, QString> m_pathsForUrls;

    void handleHeadReply(QNetworkReply *reply);
    void hangleGetReply(QNetworkReply *reply);
};

#endif // DOWNLOADER_H
