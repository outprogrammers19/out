#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QQuickStyle>

#include "datamodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QQuickStyle::setStyle("Fusion");

    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon("out.ico"));

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:///qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    DataModel model;
    model.readWebsitesList("websites-list.json");
    engine.rootContext()->setContextProperty("dataModel", &model);

    engine.load(url);
    return app.exec();
}
