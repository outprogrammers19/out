#ifndef WEBSITES_MODEL_H
#define WEBSITES_MODEL_H

#include "resource.h"
#include <QObject>

class WebsitesModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)

public:
    explicit WebsitesModel(QObject *parent = nullptr);
    void addWebsite(const Resource &web);
    int count() const;
    const QVector<Resource>& getResources() const;

    void clear();
    QString status() const;

signals:
    void statusChanged(QString status);
    void countChanged(int count);

public slots:
    QString name(int index) const;
    QString url(int index) const;
    QString icon(int index) const;

    void setCount(int count);

private:
    QVector<Resource> m_webs;
    int m_count;
};

#endif // WEBSITES_MODEL_H
