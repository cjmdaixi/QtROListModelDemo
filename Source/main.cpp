#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QRemoteObjectHost>
#include "addressbookmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    AddressBookModel addressBookModel;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("addressBookModel", &addressBookModel);

    QRemoteObjectHost host(QUrl("local:addressbook"));
    host.enableRemoting(&addressBookModel, "AddressBookModel", addressBookModel.roles());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
