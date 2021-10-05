#include "balancedataobject.hpp"

BalanceDataObject::BalanceDataObject(const BalanceData& data) :
    date_(QString::fromStdString(data.date_)), balance_(QString::fromStdString(data.balance_))
{

}

QString BalanceDataObject::date() const
{
    return this->date_;
}

QString BalanceDataObject::balance() const
{
    return this->balance_;
}
