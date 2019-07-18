QT += qml quick quickcontrols2 network
CONFIG += c++14
TARGET = OUT

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += include

HEADERS += \
    include/documentsmodel.h \
    include/downloader.h \
    include/manager.h \
    include/resource.h \
    include/websitesmodel.h

SOURCES += \
    src/documentsmodel.cpp \
    src/downloader.cpp \
    src/main.cpp \
    src/manager.cpp \
    src/websitesmodel.cpp

RESOURCES += qml.qrc

OTHER_FILES += \
    other/config/websites-list.json \
    other/config/documents-list.json \
    resources/config.ini

RC_ICONS = other/out.ico
ICON = other/out.ico

# copy resources to build directoriesw

COPIES += copy_to_build_dir
copy_to_build_dir.files += $$files(other/out.ico)
copy_to_build_dir.path = $$OUT_PWD

COPIES += copy_to_resources_dir
copy_to_resources_dir.files += $$files(resources/websites-list.json)
copy_to_resources_dir.files += $$files(resources/documents-list.json)
copy_to_resources_dir.files += $$files(resources/config.ini)
copy_to_resources_dir.path = $$OUT_PWD/resources

COPIES += copy_to_websites_icons_dir
copy_to_websites_icons_dir.files += $$files(resources/websites-icons/*)
copy_to_websites_icons_dir.path = $$OUT_PWD/resources/websites-icons

COPIES += copy_to_documents_dir
copy_to_documents_dir.files += $$files(resources/documents/*)
copy_to_documents_dir.path = $$OUT_PWD/resources/documents

## Additional import path userd to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

## Additional import path used to resolve QML modules just for Qt Quick Designer
#QML_DESIGNER_IMPORT_PATH =

## Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
