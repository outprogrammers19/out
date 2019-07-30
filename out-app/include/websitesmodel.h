/**
 * @file websitesmodel.h
 * @author Jakub Precht
 * @date 2019-07-31
 */

#ifndef WEBSITES_MODEL_H
#define WEBSITES_MODEL_H

#include "resource.h"
#include <QObject>

/**
 * @brief The WebsitesModel is a container responsible for serving data to GUI written in QML.
 *
 * In particular, it can answer how many elements are currently stored, send signals when something changes and
 * provide details for each of stored websites: name, icon name and url.
 */
class WebsitesModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    /**
     * @brief Default constructor. Doesn't do anything special.
     * @param parent pointer to an instance of QObject; if not null, this class will be deleted automatically when
     * pointed parent object is deleted
     */
    explicit WebsitesModel(QObject *parent = nullptr);

    /**
     * @brief Add new website Resource.
     *
     * The Resource should contain: <b>name</b> used as description in GUI, <b>url</b> to the website, <b>path</b> to icon to be displayed in GUI.
     *
     * @param web reference to Resource describing website.
     */
    void addWebsite(const Resource &web);

    /**
     * @brief count is a Q_PROPERTY defining number of elements
     *
     * Q_PROPERTY can be used in QML as if it is a public variable, i.e. <em>'var x = model.count'</em> or <em>'model.count = 10'</em> and
     * the appropriate setter/getter methods will be called automatically. In this particular example we don't need a public setter method,
     * we're implementing only the getter method.
     *
     * @return number of elements
     */
    int count() const;

    /**
     * @brief Get all stored websites resources.
     *
     * This method returns a const reference to the container used by WebsitesModel to store websites Resouce.
     * So if WebsitesModel changes the content (for example by addWebsite() method) then the referenced container will change as well.
     *
     * @return const reference to QVector<Resource> member
     */
    const QVector<Resource>& getResources() const;

    /**
     * @brief Remove all elements stored in container.
     *
     * It will emit countChanged() signal.
     */
    void clear();

signals:
    /**
     * @brief Emitted when number of elements changes.
     *
     * Can be caused by addWebsite() or clear().
     *
     * @param count number of elements after the change
     */
    void countChanged(int count);

public slots:
    /**
     * @brief Return name of a Resource at specified position.
     * @param index position of Resource in the container
     * @return QString with name if index is correct or empty QString if index if not correct
     */
    QString name(int index) const;

    /**
     * @brief Return url of a Resource at specified position.
     * @param index position of Resource in the container.
     * @return QString with url if index is correct or empty QString if index if not correct
     */
    QString url(int index) const;

    /**
     * @brief Return icon path of a Resource at specified position.
     * @param index position of Resource in the container.
     * @return QString with icon path if index is correct or empty QString if index if not correct
     */
    QString icon(int index) const;

private:
    QVector<Resource> m_webs;
    int m_count;
};

#endif // WEBSITES_MODEL_H
