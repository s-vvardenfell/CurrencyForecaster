#include "purchase_tablemodel.hpp"


PurchaseTableModel::PurchaseTableModel(QObject *parent) : QAbstractTableModel(parent)
{

}

int PurchaseTableModel::rowCount(const QModelIndex &) const
{
    return 10;//КАК ЭТО ОПРЕДЕЛЮ
}

int PurchaseTableModel::columnCount(const QModelIndex &) const
{
    return 6;
}

QVariant PurchaseTableModel::data(const QModelIndex &index, int role) const
{
//    switch (role) {
//        case Qt::DisplayRole:
//            return QString("%1, %2").arg(index.column()).arg(index.row());
//        default:
//            break;
//    }
//    return QVariant();

//    if (index.row() < 0 || index.row() >= m_Purchases.count())
//        return QVariant();

//    const PurchaseObject &Purchase = m_Purchases[index.row()];

        if (role == DateRole)
            return "Purchase.date()";
        else if (role == PtypeRole)
            return "Purchase.ptype()";
        else if (role == AmountRole)
            return "Purchase.amount()";
        else if (role == PriceRole)
            return "Purchase.price()";
        else if (role == SumRole)
            return "Purchase.sum()";
        else if (role == BankNameRole)
            return "Purchase.bank_name()";
        else if (role == AccountRole)
            return "Purchase.account()";


    return QVariant();
}

QHash<int, QByteArray> PurchaseTableModel::roleNames() const
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
