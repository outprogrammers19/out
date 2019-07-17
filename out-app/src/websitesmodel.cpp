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

void WebsitesModel::addWebsite(const WebsitesModel::Website &web)
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
