#ifndef BALANCEDATAOBJECT_HPP
#define BALANCEDATAOBJECT_HPP

#include "utility.hpp"

class BalanceDataObject
{
public:
    BalanceDataObject(const BalanceData& data);

    QString date() const;
    QString balance() const;

private:
    QString date_;
    QString balance_;
};

#endif // BALANCEDATAOBJECT_HPP
