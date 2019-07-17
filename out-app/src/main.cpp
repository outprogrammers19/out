#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QQuickStyle>

#include "manager.h"
#include "websitesmodel.h"
#include "documentsmodel.h"

int main(int argc, char *argv[])
{
    // Set application's settings inaccessible in QML
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // NOTE: not tested on HiDpi
    QQuickStyle::setStyle("Fusion");

    // Create instanceof qapplication before manager and models
    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon("out.ico"));

    // Create C++ classes and load settings
    WebsitesModel websModel;
    DocumentsModel docsModel;
    Manager manager;

    // TOOD errors, msgs or print status in gui:
    if (manager.readAppConfig("") == false) {
        return -1;
    }
    if (manager.readWebsitesConfig(websModel) == false) {
//        return -1;
    }
    if (manager.readDocumentsConfig(docsModel) == false) {
//        return -1;
    }

    QQmlApplicationEngine engine;

    // Expose C++ classes to the QML engine
    engine.rootContext()->setContextProperty("websModel", &websModel);
    engine.rootContext()->setContextProperty("docsModel", &docsModel);
    engine.rootContext()->setContextProperty("manager", &manager);

    // Load QML files
    const QUrl url(QStringLiteral("qrc:///qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    // Start execution loop
    return app.exec();
}
