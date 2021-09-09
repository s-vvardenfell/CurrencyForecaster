#ifndef CURREXCDATAOBJECT_HPP
#define CURREXCDATAOBJECT_HPP

#include "parser.hpp"

class CurrExcDataObject
{
public:
    CurrExcDataObject(const CurrencyExchangeData &currencyExchangeData);

    QString currency() const;
    QString change() const;
    QString cost() const;

private:

    QString currency_;
    QString change_;
    QString cost_;
};

#endif // CURREXCDATAOBJECT_HPP
