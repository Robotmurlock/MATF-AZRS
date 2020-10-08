#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "backend.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // qmlRegisterType<[IME KLASE]>([IME BIBLIOTEKE], [MAJOR], [MINOR], [IME])
    qmlRegisterType<BackEnd>("io.qt.examples.backend", 1, 0, "BackEnd");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
