QT += qml quick quickcontrols2
CONFIG += c++14
TARGET = OUT

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += include

HEADERS += \
    include/datamodel.h

SOURCES += \
    src/datamodel.cpp \
    src/main.cpp

RESOURCES += qml.qrc

OTHER_FILES += \
    other/websites/websites-list.json \
    other/documents/documents-list.json

RC_ICONS = other/app-icons/out.ico
ICON = other/app-icons/out.ico

# copy resources to build directories

COPIES += copy_to_build_dir
copy_to_build_dir.files += $$files(other/app-icons/out.ico)
copy_to_build_dir.path = $$OUT_PWD

COPIES += copy_to_websites_dir
copy_to_websites_dir.files += $$files(other/websites/websites-list.json)
copy_to_websites_dir.path = $$OUT_PWD/websites

COPIES += copy_to_website_icons_dir
copy_to_website_icons_dir.files += $$files(other/websites/website-icons/*)
copy_to_website_icons_dir.path = $$OUT_PWD/websites/website-icons

COPIES += copy_to_documents_dir
copy_to_documents_dir.files += $$files(other/documents/documents-list.json)
copy_to_documents_dir.path = $$OUT_PWD/documents

COPIES += copy_to_documents_files_dir
copy_to_documents_files_dir.files += $$files(other/documents/document-files/*)
copy_to_documents_files_dir.path = $$OUT_PWD/documents/document-files


## Additional import path userd to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

## Additional import path used to resolve QML modules just for Qt Quick Designer
#QML_DESIGNER_IMPORT_PATH =

## Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
