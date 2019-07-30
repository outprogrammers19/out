/**
 * @file resource.h
 * @author Jakub Precht
 * @date 2019-07-30
 */

#ifndef RESOURCE_H
#define RESOURCE_H

#include <QString>

/**
 * @brief The Resource struct used to store and pass information about websites and documents.
 *
 * Note that not all resources must use all elements of this struct.
 */
struct Resource
{
    /**
     * @brief name of the resource to appear in the application
     */
    QString name;

    /**
     * @brief url to the resource to access it online
     */
    QString url;

    /**
     * @brief path to the resource when stored locally, where root is the resource directory specified in settings
     */
    QString path;

    /**
     * @brief path to a icon that will appear in application, where root is the resource directory specified in settings
     */
    QString icon;

    /**
     * @brief timestamp of latest modification.
     */
    QString timestamp;
};

#endif // RESOURCE_H
