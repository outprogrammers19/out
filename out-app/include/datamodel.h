#ifndef DATA_MODEL_H
#define DATA_MODEL_H

#include <QObject>

class DataModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)

public:
    explicit DataModel(QObject *parent = nullptr);
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

#ifdef Q_OS_WIN
    const QString webIconsDirName = "website-icons\\";
#else
    const QString webIconsDirName = "website-icons/";
#endif

    int m_count = 0;
    QStringList m_names;
    QStringList m_urls;
    QStringList m_icons;
    QString m_status;

    bool storeWebsitesDetails(QJsonObject &root);
    void validateIconFiles();
};

#endif // DATA_MODEL_H
