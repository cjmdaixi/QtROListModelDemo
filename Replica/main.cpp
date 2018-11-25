#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QRemoteObjectNode>
#include <QAbstractItemModelReplica>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QRemoteObjectNode node;
    node.connectToNode(QUrl("local:addressbook"));
    auto addressBookModel = node.acquireModel("AddressBookModel");
    engine.rootContext()->setContextProperty("addressBookModel", addressBookModel);

    QObject::connect(addressBookModel, &QAbstractItemModelReplica::initialized, &app, [&]{
        qDebug()<<"initialized.";
    });
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
