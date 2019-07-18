#include "include/documentsmodel.h"
#include <QDebug>

DocumentsModel::DocumentsModel(QObject *parent) : QAbstractListModel(parent)
{
    //    tmp_initialize();
}

QHash<int, QByteArray> DocumentsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(NAME, "name");
    roles.insert(URL, "url");
    roles.insert(PATH, "path");
    roles.insert(TIMESTAMP, "timestamp");
    return roles;
}

int DocumentsModel::rowCount(const QModelIndex &) const
{
    return m_docs.count();
}

QVariant DocumentsModel::data(const QModelIndex &index, int role) const
{
    QVariant result = QVariant();

    if (index.isValid() == false || index.row() >= m_docs.count())
        return  result;

    Resource doc = m_docs.at(index.row());
    switch (role) {
    case NAME:
        result = doc.name;
        break;
    case URL:
        result = doc.url;
        break;
    case PATH:
        result = doc.path;
        break;
    case TIMESTAMP:
        result = doc.timestamp;
        break;
    }

    return result;
}

void DocumentsModel::addDocument(const Resource &document)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_docs << document;
    endInsertRows();
}

void DocumentsModel::clear()
{
    if (rowCount() == 0)
        return;

    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    m_docs.clear();
    endRemoveRows();
}

const QVector<Resource> &DocumentsModel::getResources() const
{
    return m_docs;
}
