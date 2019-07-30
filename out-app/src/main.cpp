/**
 * @file main.cpp
 *
 * @mainpage OUT - The Open University of Tanzania application
 * @version 1.0
 * @author Jakub Precht
 * @date 2019-08-01
 * @see https://github.com/precht/out/
 *
 * @section intro_sec Introduction
 *
 * This application was created to help people navigate through different university's online resources and to
 * provide offline access to important documents.
 * It is written with the use of Qt framework, mainly in C++ and QML languages.
 *
 *
 * @section update_sec Update application content
 *
 * Application uses very simple update mechanism - there is a HTTP folder on university's server and the application makes
 * a copy of that folder in local data directory. '<em>websites-list.json</em>' describes what website links should be visible
 * on the first page and '<em>websites-icons</em>' directory contains icons to be displayed next to these links. '<em>documents-list.json</em>'
 * describes files to be visible on the second page and '<em>documents</em>' directory is where local copies of these documents are stored. Thus,
 * it is possible to open these documents without an internet connection.
 *
 * @section compile_sec Compilation
 *
 * Currently the application uses Qt framework version 5.13.
 * Any additional dependencies should be installed automatically with the Qt framework.
 * The app is compiled with GCC 9.1.0 under Linux and MinGW 7.3.0 under Windows.
 *
 * After installing Qt framework open out-app.pro with QtCreator and build the project.
 * To generate documentation from source code comments go to <b>docs</b> directory and run '<em>doxygen</em>' from command line
 * (you need to install Doxygen first).
 *
 */


#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QQuickStyle>

#include "manager.h"
#include "websitesmodel.h"
#include "documentsmodel.h"

/**
 * @brief main function that loads all needed classes and resources and starts Qt's execution loop
 * @return 0 if application terminated normally
 */
int main(int argc, char *argv[])
{
    // Set application's settings inaccessible in QML
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // NOTE: not tested on HiDpi
    QQuickStyle::setStyle("Fusion");

    // Create instance of qapplication before manager and models
    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon("out.ico"));

    // App backend written in C++
    Manager manager;
    manager.initialize(); // TODO config path

    QQmlApplicationEngine engine;

    // Expose C++ classes to the QML engine
    engine.rootContext()->setContextProperty("manager", &manager);
    engine.rootContext()->setContextProperty("websModel", manager.getWebsitesModel());
    engine.rootContext()->setContextProperty("docsModel", manager.getDocumentsModel());

    // Load QML files
    const QUrl url(QStringLiteral("qrc:///qml/MainWindow.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    // Start execution loop
    return app.exec();
}

