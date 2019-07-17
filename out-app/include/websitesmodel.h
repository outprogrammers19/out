#ifndef WEBSITES_MODEL_H
#define WEBSITES_MODEL_H

#include <QObject>

class WebsitesModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    struct Website {
        QString name;
        QString url;
        QString icon;
    };

    explicit WebsitesModel(QObject *parent = nullptr);
    void addWebsite(const Website &web);
    int count() const;

    void clear();
    QString status() const;

signals:
    void statusChanged(QString status);
    void countChanged(int count);

public slots:
    QString name(int index) const;
    QString url(int index) const;
    QString icon(int index) const;

private:
    QVector<Website> m_webs;
};

#endif // WEBSITES_MODEL_H
