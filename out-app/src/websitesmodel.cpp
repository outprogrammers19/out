#include "websitesmodel.h"

#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

#include <exception>

WebsitesModel::WebsitesModel(QObject *parent)
    : QObject(parent)
{ }

void WebsitesModel::addWebsite(const Resource &web)
{
    m_webs << web;
    emit countChanged(m_webs.count());
}

void WebsitesModel::clear()
{
    m_webs.clear();
    emit countChanged(0);
}

int WebsitesModel::count() const
{
    return m_webs.count();
}

const QVector<Resource> &WebsitesModel::getResources() const
{
    return m_webs;
}

QString WebsitesModel::name(int index) const
{
    if(index < 0 || index > count())
        return "";
    return m_webs[index].name;
}

QString WebsitesModel::url(int index) const
{
    if(index < 0 || index > count())
        return "";
    return m_webs[index].url;
}

QString WebsitesModel::icon(int index) const
{
    if(index < 0 || index > count())
        return "";
    return m_webs[index].icon;
}

void WebsitesModel::setCount(int count)
{
    if (m_count == count)
        return;

    m_count = count;
    emit countChanged(m_count);
}
