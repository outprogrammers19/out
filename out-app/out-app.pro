QT += qml quick quickcontrols2
CONFIG += c++14
TARGET = OUT

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += include

HEADERS += \
    include/documentsmodel.h \
    include/websitesmodel.h

SOURCES += \
    src/documentsmodel.cpp \
    src/main.cpp \
    src/websitesmodel.cpp

RESOURCES += qml.qrc

OTHER_FILES += \
    other/config/websites-list.json \
    other/config/documents-list.json

RC_ICONS = other/app-icons/out.ico
ICON = other/app-icons/out.ico

# copy resources to build directories

COPIES += copy_to_build_dir
copy_to_build_dir.files += $$files(other/app-icons/out.ico)
copy_to_build_dir.path = $$OUT_PWD

COPIES += copy_to_config_dir
copy_to_config_dir.files += $$files(other/config/websites-list.json)
copy_to_config_dir.files += $$files(other/config/documents-list.json)
copy_to_config_dir.path = $$OUT_PWD/config

COPIES += copy_to_websites_icons_dir
copy_to_websites_icons_dir.files += $$files(other/websites-icons/*)
copy_to_websites_icons_dir.path = $$OUT_PWD/websites-icons

COPIES += copy_to_documents_dir
copy_to_documents_dir.files += $$files(other/documents/*)
copy_to_documents_dir.path = $$OUT_PWD/documents

## Additional import path userd to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

## Additional import path used to resolve QML modules just for Qt Quick Designer
#QML_DESIGNER_IMPORT_PATH =

## Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
