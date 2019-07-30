/**
 * @file downloader.h
 * @author Jakub Precht
 * @date 2019-07-31
 */

#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QMap>
#include "resource.h"

class QNetworkAccessManager;
class QNetworkReply;
class Manager;

/**
 * @brief The Downloader class downloads online resources via HTTP.
 *
 * The class uses QNetworkAccessManager to establish connection, send requests and receive replays.
 * It can either download just a header and check metadata (like timestamp) or download whole Resource (file/website)
 * and save it at a specified location.
 */
class Downloader : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Default constructor.
     *
     * It creates a QNetworkAccessManager member variable and connects necessarily signals with Downloader's private
     * methods/handlers.
     *
     * @param parent pointer to an instance of QObject; if not null, Downloader will be deleted automatically when
     * parent object is deleted
     */
    explicit Downloader(QObject *parent = nullptr);

    /**
     * @brief Forget all stored paths and urls from previous downloads.
     *
     * During each download request, url and corresponding path will be stored in a QMap, so that when reply comes back
     * from server, the Downloader class knows where to save incoming file. This method clears QMap member variable from all values.
     */
    void clear();

signals:
    /**
     * @brief Emitted when downloadHeader() request is finished.
     * @param url of the Resource
     * @param status of replay, true if successful
     * @param timestamp of the remote Resource at HTTP server
     */
    void headerDownloaded(QString url, bool status, QString timestamp);

    /**
     * @brief Emitted when downloadFile() request is finished.
     * @param url of the Resource
     * @param status of replay, true if successful
     */
    void fileDownloaded(QString url, bool status);

public slots:    
    /**
     * @brief Download only HTTP header with metadata, not the Resource itself.
     *
     * This  function was implemented to make it possible to check files timestamps at the server without downloading them.
     * @note Currently not used.
     *
     * @param resource reference to an instance of Resource to be downloaded
     */
    void downloadHeader(const Resource &resource);

    /**
     * @brief Download file specified by Resource.
     *
     * If successfully downloaded, it will be saved in the location specified by path variable in Resource.
     * @note When replay comes from server it contains only url. Thus, the file will be saved in location specified
     * by the latest request containing that url.
     *
     * @param resource
     */
    void downloadFile(const Resource &resource);

private:
    /**
     * @brief This is a default handler for an incoming reply.
     *
     * It is responsible for checking if request was successful and then calling appropriate private handler depending
     * on the reply type: was it a header or file download. This method should be connected with QNetworkAccessManager::finished() signal.
     *
     * @param reply pointer to QNetworkReply sent by HTTP server as an argument of finished signal, can contain metadata and file itself.
     */
    void replyFinished(QNetworkReply *reply);

    // private methods:

    /**
     * @brief Handle downloadHeader() reply.
     *
     * This function extract timestamp from metadata and emits headerDownloaded() signal.
     *
     * @param reply pointer to QNetworkReply sent by HTTP server
     */
    void handleHeadReply(QNetworkReply *reply);

    /**
     * @brief Handle downloadFile() reply.
     *
     * This function tries to save downloaded file at location specified as path when downloadFile() was called.
     * If directory does not exists, it will be created.
     *
     * @param reply pointer to QNetworkReply sent by HTTP server
     */
    void hangleGetReply(QNetworkReply *reply);

    // private members:

    /**
     * @brief Remembers where to save a specific Resource when network replay for that resource comes back from server.
     *
     * Keys are urls and values are paths from Resource.
     */
    QMap<QString, QString> m_pathsForUrls;

    QNetworkAccessManager *m_network;
};

#endif // DOWNLOADER_H
