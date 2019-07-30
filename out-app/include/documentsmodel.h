/**
 * @file documentsmodel.h
 * @author Jakub Precht
 * @date 2019-08-01
 */

#ifndef DOCUMENTSMODEL_H
#define DOCUMENTSMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include "resource.h"

/**
 * @brief The DocumentsModel is a container responsible for serving data to GUI written in QML.
 *
 * It implements QAbstractListModel, an interface used by QML items to automatically pull data from model.
 * Properties visible in QML's delegate element are defined by DataRoles enum. The most important method
 * in this class is data(), which for given index and role will return expected value.
 *
 * @see https://doc.qt.io/qt-5/model-view-programming.html
 * @see https://doc.qt.io/qt-5/qabstractlistmodel.html
 */
class DocumentsModel : public QAbstractListModel
{
    Q_OBJECT

    /**
     * @brief The DataRoles enum describes roles that can be passed as argument to data() method.
     *
     * Qt has many predefined roles, so we need to assign to our first role the first empty value,
     * which is defined by Qt::UserRole. For our purpose we need 4 roles: name of the document, url to
     * the remote version, path under which it is stored in system and timestamp of last modification.
     */
    enum DataRoles {
        NAME = Qt::UserRole,
        URL,
        PATH,
        TIMESTAMP
    };

public:

    /**
     * @brief Default constructor. Doesn't do anything special.
     * @param parent pointer to an instance of QObject; if not null, this class will be deleted automatically when
     * pointed parent object is deleted
     */
    explicit DocumentsModel(QObject *parent = nullptr);

    /**
     * @brief Returns number of all elements, as this class is a single column model.
     * @return number of all elements
     */
    int rowCount(const QModelIndex & = QModelIndex()) const override;

    /**
     * @brief Method responsible for serving data holds by the model.
     * @param index of the Resource in the container
     * @param role as defined by DataRoles enum.
     * @return QString wrapped by QVariant, which represents the requested value of the specified Resource.
     *
     * If the index or role does not exists, it returns empty QVariant.
     */
    QVariant data(const QModelIndex &index, int role) const override;

    /**
     * @brief Map enum values to properties visible in QML delegate element.
     * @return QHash map where key is DataRoles enum value and value is a name of property.
     *
     * Using this method we can map DataRoles::NAME into "name" string, and then inside QML delegate element
     * we can use it like that: <em>'text: name'</em>. Of course, we need to specify the model for ListView item.
     * We should set it to the instance of DocumentsModel exposed to QML engine in main.cpp file.
     */
    QHash<int, QByteArray> roleNames() const override;

    /**
     * @brief addDocument
     * @param document
     */
    void addDocument(const Resource &document);

    /**
     * @brief Remove all elements store in the model.
     *
     * It shall call appropriate signals to inform GUI about it, so the view will be refreshed.
     */
    void clear();

    /**
     * @brief Get all stored websites resources.
     *
     * This method returns a const reference to the container used by WebsitesModel to store websites Resouce.
     * So if WebsitesModel changes the content (for example by addWebsite() method) then the referenced container will change as well.
     *
     * @return const reference to QVector<Resource> member
     */
    const QVector<Resource>& getResources() const;

private:
    QVector<Resource> m_docs;
};

#endif // DOCUMENTSMODEL_H
