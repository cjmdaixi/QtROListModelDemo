#ifndef ADDRESSBOOKMODEL_H
#define ADDRESSBOOKMODEL_H
#include <QAbstractListModel>
#include <QAbstractItemModelReplica>
#include <QList>

struct AddressData{
    QString name;
    int seniority;
    QString title;
    QString address;
};

class AddressBookModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum AddressDataRoles{
        NameRole = Qt::UserRole + 1,
        SeniorityRole,
        TitleRole,
        AddressRole
    };
    Q_ENUM(AddressDataRoles)

    explicit AddressBookModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
signals:

public slots:
    void addTestData();
    QVector<int> roles() const;
    QVariantMap item(int idx) const;
    void remove(const int idx);
    void modify(const int idx,
                const QString& name,
                const int seniority,
                const QString& title,
                const QString& address);
    void append(QString name,
                int seniority,
                QString title,
                QString address);
private:
    QList<AddressData> m_addresses;
};

#endif // ADDRESSBOOKMODEL_H
