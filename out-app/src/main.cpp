/**
 * @file main.cpp
 * @author Jakub Precht
 * @date 2019-08-19
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
