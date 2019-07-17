#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QQuickStyle>

#include "websitesmodel.h"
#include "documentsmodel.h"

int main(int argc, char *argv[])
{
    // Set application's settings inaccessible in QML
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling); // NOTE: not tested on HiDpi
    QQuickStyle::setStyle("Fusion");

    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon("out.ico"));

    // Load custom C++ classes to be visible in QML engine
    QQmlApplicationEngine engine;

    WebsitesModel websModel;
    websModel.readWebsitesList("config/websites-list.json");
    engine.rootContext()->setContextProperty("websModel", &websModel);

    DocumentsModel docsModel;
    engine.rootContext()->setContextProperty("docsModel", &docsModel);

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
