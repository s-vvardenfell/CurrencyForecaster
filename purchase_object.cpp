#include "purchase_object.hpp"

PurchaseObject::PurchaseObject(const QString &type, const QString &size)
{
     id_ = "id";
     date_ = "date";
     ptype_ = "ptype";
     amount_ = "amount";
     price_ = "price";
     sum_ = "sum";
}

QString PurchaseObject::id() const
{
    return id_;
}

QString PurchaseObject::date() const
{
    return date_;
}

QString PurchaseObject::ptype() const
{
    return ptype_;
}

QString PurchaseObject::amount() const
{
    return amount_;
}

QString PurchaseObject::price() const
{
    return price_;
}

QString PurchaseObject::sum() const
{
    return sum_;
}

PurchaseModel::PurchaseModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void PurchaseModel::addPurchase(const PurchaseObject &Purchase)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_Purchases << Purchase;
    endInsertRows();
}

int PurchaseModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return m_Purchases.count();
}

QVariant PurchaseModel::data(const QModelIndex & index, int role) const
{
    if (index.row() < 0 || index.row() >= m_Purchases.count())
        return QVariant();

    const PurchaseObject &Purchase = m_Purchases[index.row()];

    if (role == IdRole)
        return Purchase.id();
    else if (role == DateRole)
        return Purchase.date();
    else if (role == PtypeRole)
        return Purchase.ptype();
    else if (role == AmountRole)
        return Purchase.amount();
    else if (role == PriceRole)
        return Purchase.price();
    else if (role == SumRole)
        return Purchase.sum();


    return QVariant();
}

//![0]
QHash<int, QByteArray> PurchaseModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[IdRole] = "id";
    roles[DateRole] = "date";
    roles[PtypeRole] = "ptype";
    roles[AmountRole] = "amount";
    roles[PriceRole] = "price";
    roles[SumRole] = "sum";

    return roles;
}
