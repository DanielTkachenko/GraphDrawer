#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "customgraph.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<CustomGraph>("customgraph", 1, 0, "CustomGraph");

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("GraphDrawer", "Main");

    return app.exec();
}
