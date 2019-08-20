/**
 * @author Jakub Precht
 * @date 2019-07-31
 */

#include "downloader.h"
#include "manager.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDateTime>
#include <QFile>
#include <QDir>
#include <QDebug>

// TODO progress bar: https://www.bogotobogo.com/Qt/Qt5_QNetworkRequest_Http_File_Download.php

Downloader::Downloader(QObject *parent)
    : QObject(parent)
{
    m_network = new QNetworkAccessManager(this); // no need to delete
    connect(m_network, &QNetworkAccessManager::finished, this, &Downloader::replyFinished);
}

void Downloader::clear()
{
    m_pathsForUrls.clear();
}

void Downloader::downloadHeader(const Resource &resource)
{
    m_network->head(QNetworkRequest(QUrl(resource.url)));
}

void Downloader::downloadFile(const Resource &resource)
{
    qInfo() << "Downloading file:" << resource.url;
    m_pathsForUrls[resource.url] = resource.path;
    m_network->get(QNetworkRequest(QUrl(resource.url)));
}

void Downloader::replyFinished(QNetworkReply *reply)
{
    switch (reply->operation()) {
    case QNetworkAccessManager::HeadOperation:
        handleHeadReply(reply);
        break;
    case QNetworkAccessManager::GetOperation:
        hangleGetReply(reply);
        break;
    default:
        qWarning() << "Network reply handler: unsupported operation type.";
    }

    reply->deleteLater();
}

void Downloader::handleHeadReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Network replay error: " << reply->errorString();
        emit headerDownloaded(reply->url().toString(), false, "");
        return;
    }

//    auto typeObj = reply->header(QNetworkRequest::ContentTypeHeader);
//    QString type = typeObj.toString();
//    auto sizeObj = reply->header(QNetworkRequest::ContentLengthHeader);
//    uint64_t size = sizeObj.toULongLong();

    auto timestampObj = reply->header(QNetworkRequest::LastModifiedHeader);
    QString timestamp = timestampObj.toDateTime().toLocalTime().toString("yyyy-MM-dd hh:mm");

    emit headerDownloaded(reply->url().toString(), true, timestamp);
}

void Downloader::hangleGetReply(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Network replay error: " << reply->errorString();
        emit fileDownloaded(reply->url().toString(), false);
        return;
    }

    QString absoluteFilePath = m_pathsForUrls[reply->url().toString()];
    QString absoluteDirPath = QFileInfo(absoluteFilePath).absolutePath();
    QDir dir(absoluteDirPath);
    if (dir.exists() == false)
        dir.mkpath(absoluteDirPath);

    QFile *file = new QFile(absoluteFilePath);

    if (file->open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        file->write(reply->readAll());
        file->flush();
        file->close();
        emit fileDownloaded(reply->url().toString(), true);
    }
    else {
        emit fileDownloaded(reply->url().toString(), false);
    }
    delete file;
}
