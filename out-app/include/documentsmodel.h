#ifndef DOCUMENTSMODEL_H
#define DOCUMENTSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "resource.h"

class DocumentsModel : public QAbstractListModel
{
    Q_OBJECT

    enum DataRoles {
        NAME = Qt::UserRole,
        URL,
        PATH,
        TIMESTAMP
    };

public:

    explicit DocumentsModel(QObject *parent = nullptr);

    /** this is single column model, so rowCount equals to all elements count */
    int rowCount(const QModelIndex & = QModelIndex()) const override;

    /** serves docs to qml view */
    QVariant data(const QModelIndex &index, int role) const override;

    /** defines names of attributes used in view's delegate */
    QHash<int, QByteArray> roleNames() const override;

    void addDocument(const Resource &document);

    void clear();

    const QVector<Resource>& getResources() const;

signals:

public slots:

private:
    QVector<Resource> m_docs;
};

#endif // DOCUMENTSMODEL_H
