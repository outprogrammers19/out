#ifndef WEBSITES_MODEL_H
#define WEBSITES_MODEL_H

#include <QObject>

class WebsitesModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)

public:
    explicit WebsitesModel(QObject *parent = nullptr);
    bool readWebsitesList(const QString &filename);
    void clear();

    QString status() const;

signals:
    void statusChanged(QString status);

public slots:
    int count() const;
    QString name(int index) const;
    QString url(int index) const;
    QString icon(int index) const;
    bool openUrl(int index) const;
    void setStatus(QString status);

private:

// NOTE: no need for that?
//#ifdef Q_OS_WIN
//    const QString websIconsDir = "websites-icons\\";
//#else
    const QString websIconsDir = "websites-icons/";
//#endif

    // TODO move websIconsDir to config

    int m_count = 0;
    QStringList m_names;
    QStringList m_urls;
    QStringList m_icons;
    QString m_status;

    bool storeWebsitesDetails(QJsonObject &root);
    void validateIconFiles();
};

#endif // WEBSITES_MODEL_H
