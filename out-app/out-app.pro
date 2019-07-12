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
    other/websites_list.json

RC_ICONS = other/app-icon/out.ico
ICON = other/app-icon/out.ico

# copy websites_list.json and icons to build direcotry

COPIES += copy_to_build_dir
copy_to_build_dir.files += $$files(other/websites-list.json)
copy_to_build_dir.files += $$files(other/app-icon/out.ico)
copy_to_build_dir.path = $$OUT_PWD

COPIES += copy_to_website_icons_dir
copy_to_website_icons_dir.files = $$files(other/website-icons/*.png)
copy_to_website_icons_dir.path = $$OUT_PWD/website-icons


## Additional import path userd to resolve QML modules in Qt Creator's code model
#QML_IMPORT_PATH =

## Additional import path used to resolve QML modules just for Qt Quick Designer
#QML_DESIGNER_IMPORT_PATH =

## Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
