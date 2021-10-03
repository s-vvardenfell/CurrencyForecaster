#include "currexcdata_object.hpp"

CurrExcDataObject::CurrExcDataObject(const CurrencyExchangeData &data) :
    currency_(QString::fromStdString(data.currency_.substr(0, data.currency_.size()-6))),
    change_(QString::fromStdString(data.change_)),
    cost_(QString::fromStdString(data.cost_))
{
              //TODO инфы больше чем 3 члена
                //можно спарсить англ название отдельно и выводить
}

QString CurrExcDataObject::currency() const
{
    return this->currency_;
}

QString CurrExcDataObject::change() const
{
    return this->change_;
}

QString CurrExcDataObject::cost() const
{
    return this->cost_;
}
