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

    Document doc = m_docs.at(index.row());
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

void DocumentsModel::addDocument(const Document &document)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_docs << document;
    endInsertRows();
}

void DocumentsModel::clear()
{
    beginRemoveRows(QModelIndex(), rowCount(), rowCount());
    m_docs.clear();
    endRemoveRows();
}

void DocumentsModel::tmp_initialize()
{
    Document doc;
    doc.name = "Prospectus";
    doc.url = "https://www.out.ac.tz/wp-content/uploads/2019/01/PROSPECTUS-2018-2019.pdf";
    doc.path = "PROSPECTUS 2018-2019.pdf";
    doc.timestamp = "2019-07-17 09:44";

    addDocument(doc);
}
