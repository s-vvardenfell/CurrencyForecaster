#include "purchase_object.hpp"

PurchaseObject::PurchaseObject(const QString &type, const QString &size)
{
     date_ = "date";
     ptype_ = "ptype";
     amount_ = 1234.66;
     price_ = 55.6;
     sum_ = 1233.4;
     bank_name_ = "sber";
     account_ = "22222";
}

PurchaseObject::PurchaseObject(const Purchase &purchase)
{
    date_ = QString::fromStdString(purchase.date);
    ptype_ = QString::fromStdString(purchase.type);
    amount_ = purchase.amount;
    price_ = purchase.price;
    sum_ = purchase.sum;
    bank_name_ = QString::fromStdString(purchase.bank_name);
    account_ = QString::fromStdString(purchase.account);
}

QString PurchaseObject::date() const
{
    return date_;
}

QString PurchaseObject::ptype() const
{
    return ptype_;
}

double PurchaseObject::amount() const
{
    return amount_;
}

double PurchaseObject::price() const
{
    return price_;
}

double PurchaseObject::sum() const
{
    return sum_;
}

QString PurchaseObject::bank_name() const
{
    return bank_name_;
}

QString PurchaseObject::account() const
{
    return account_;
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

    if (role == DateRole)
        return Purchase.date();
    else if (role == PtypeRole)
        return Purchase.ptype();
    else if (role == AmountRole)
        return Purchase.amount();
    else if (role == PriceRole)
        return Purchase.price();
    else if (role == SumRole)
        return Purchase.sum();
    else if (role == BankNameRole)
        return Purchase.bank_name();
    else if (role == AccountRole)
        return Purchase.account();


    return QVariant();
}

//![0]
QHash<int, QByteArray> PurchaseModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[DateRole] = "date";
    roles[PtypeRole] = "ptype";
    roles[AmountRole] = "amount";
    roles[PriceRole] = "price";
    roles[SumRole] = "sum";
    roles[BankNameRole] = "bank_name";
    roles[AccountRole] = "account";

    return roles;
}
