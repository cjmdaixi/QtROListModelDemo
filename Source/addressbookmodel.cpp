#include "addressbookmodel.h"

AddressBookModel::AddressBookModel(QObject *parent)
    : QAbstractListModel(parent)
{
    qRegisterMetaType<AddressDataRoles>();
}

int AddressBookModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_addresses.size();
}

QVariant AddressBookModel::data(const QModelIndex &index, int role) const
{
    auto row = index.row();
    QVariant result;
    if (row >= 0 && row < m_addresses.size() ) {
        const auto addressData = m_addresses.at(row);
        switch (role) {
        case NameRole:
            result = QVariant::fromValue(addressData.name);
            break;
        case SeniorityRole:
            result = QVariant::fromValue(addressData.seniority);
            break;
        case TitleRole:
            result = QVariant::fromValue(addressData.title);
            break;
        case AddressRole:
            result = QVariant::fromValue(addressData.address);
            break;
        default:
            break;
        }
    }
    return result;
}

QHash<int, QByteArray> AddressBookModel::roleNames() const
{
    auto roles = QHash<int, QByteArray>{
        {NameRole, "name"},
        {SeniorityRole, "seniority"},
        {TitleRole, "title"},
        {AddressRole, "address"}
    };
    return roles;
}

void AddressBookModel::addTestData()
{
    auto testData = QList<AddressData>{
        {"Jinming Chen", 2, "Senior software engineer", "King Rd. #32, Xihu District"},
        {"Shuang Zhou", 1, "Software engineer", "Xiali Rd. #3, Xiacheng District"},
        {"LianHua Xian", 5, "Department Manager", "Binghu Rd. #132, WestDi District"},
        {"Siyuan Yu", 2, "Test engineer", "King Rd. #15, Xihu District"}
    };
    beginInsertRows(QModelIndex(), m_addresses.size(), m_addresses.size() + testData.size() - 1);
    for(const auto &d : testData){
        m_addresses.push_back(d);
    }
    endInsertRows();
}

QVariantMap AddressBookModel::item(int idx) const
{
    if(idx < 0 || idx >= m_addresses.size())
        return QVariantMap();
    const auto & addressData = m_addresses.at(idx);
    auto result = QVariantMap{
        {"name", addressData.name},
        {"seniority", addressData.seniority},
        {"title", addressData.title},
        {"address", addressData.address}
    };
    return result;
}

void AddressBookModel::remove(const int idx)
{
    if(idx < 0 || idx >= m_addresses.size())
        return;
    beginRemoveRows(QModelIndex(), idx, idx);
    m_addresses.removeAt(idx);
    endRemoveRows();
}

void AddressBookModel::modify(const int idx,
                              const QString &name,
                              const int seniority,
                              const QString &title,
                              const QString &address)
{
    if(idx < 0 || idx >= m_addresses.size())
        return;

    auto &addressData = m_addresses[idx];
    addressData = AddressData{name, seniority, title, address};
    emit dataChanged(index(idx), index(idx));
}

void AddressBookModel::append(QString name, int seniority, QString title, QString address)
{
    beginInsertRows(QModelIndex(), m_addresses.size(), m_addresses.size());
    m_addresses.push_back({name, seniority, title, address});
    endInsertRows();
}
