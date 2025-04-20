#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <iostream>
#include "plotview.h"
#include "plotcontroller.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<PlotView>("plotview", 1, 0, "PlotView");
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("GraphDrawer", "Main");

    QObject* window = engine.rootObjects().first();

    PlotView *view = window->findChild<PlotView*>("PlotView");
    PlotController plotController(view);
    engine.rootContext()->setContextProperty("plotController", &plotController);


    return app.exec();
}
