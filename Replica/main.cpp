#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QRemoteObjectNode>
#include <QAbstractItemModelReplica>
#include <QtDebug>
enum AddressDataRoles{
    NameRole = Qt::UserRole + 1,
    SeniorityRole,
    TitleRole,
    AddressRole
};

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QRemoteObjectNode node;
    node.connectToNode(QUrl("local:addressbook"));
    QVector<int> roles = QVector<int>{NameRole, SeniorityRole, TitleRole, AddressRole};

    auto addressBookModel = node.acquireModel("AddressBookModel", QtRemoteObjects::PrefetchData, roles);
    engine.rootContext()->setContextProperty("addressBookModel", addressBookModel);

    QObject::connect(addressBookModel, &QAbstractItemModelReplica::initialized, &app, [&]{
        qDebug()<<"initialized.";
    });
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
