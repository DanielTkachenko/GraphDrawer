#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "FileReader.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    FileReader fileReader;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("fileReader", &fileReader);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    qmlRegisterType<FileReader>("filereader", 1, 0,"FileReader");
    //if (engine.rootObjects().isEmpty())
    //    return -1;

    /*QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);*/
    engine.loadFromModule("GraphDrawer", "Main");

    return app.exec();
}
