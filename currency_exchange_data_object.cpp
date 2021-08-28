#include "currency_exchange_data_object.hpp"


CurrencyExchangeDataObject::CurrencyExchangeDataObject(const CurrencyExchangeData &currencyExchangeData)
{
    this->currency_ = QString::fromStdString(currencyExchangeData.currency_);
    this->change_ = QString::fromStdString(currencyExchangeData.change_);
    this->cost_ = QString::fromStdString(currencyExchangeData.cost_);
}

QString CurrencyExchangeDataObject::currency() const
{
    return this->currency_;
}

QString CurrencyExchangeDataObject::change() const
{
    return this->change_;
}

QString CurrencyExchangeDataObject::cost() const
{
    return this->cost_;
}

CurrencyExchangeDataObjectModel::CurrencyExchangeDataObjectModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void CurrencyExchangeDataObjectModel::addCurrencyExchangeDataObject
(const CurrencyExchangeDataObject &object)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_CurrencyExchangeDataObjects << object;
    endInsertRows();
}

int CurrencyExchangeDataObjectModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return m_CurrencyExchangeDataObjects.count();
}

QVariant CurrencyExchangeDataObjectModel::data(const QModelIndex & index, int role) const
{
    if (index.row() < 0 || index.row() >= m_CurrencyExchangeDataObjects.count())
        return QVariant();

    const CurrencyExchangeDataObject &object = m_CurrencyExchangeDataObjects[index.row()];

    if (role == CurrencyRole)
        return object.currency();
    else if (role == ChangeRole)
        return object.change();
    else if (role == CostRole)
        return object.cost();

    return QVariant();
}


QHash<int, QByteArray> CurrencyExchangeDataObjectModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[CurrencyRole] = "currency";
    roles[ChangeRole] = "change";
    roles[CostRole] = "cost";

    return roles;
}

