#include "forecast_object.hpp"

ForecastObject::ForecastObject(const ForecastData &data) :
    parser_(QString::fromStdString(data.parser_)),
    value_(QString::fromStdString(data.value_)),
    forecast_date_(QString::fromStdString(data.forecast_date_)),
    period_(QString::fromStdString(data.period_)),
    accuracy_(QString::fromStdString(data.accuracy_)),
    value_review_(QString::fromStdString(data.value_review_))
{

}


QString ForecastObject::parser()
{
    return parser_;
}

QString ForecastObject::value()
{
    return value_;
}

QString ForecastObject::forecast_date()
{
    return forecast_date_;
}

QString ForecastObject::period()
{
    return period_;
}

QString ForecastObject::accuracy()
{
    return accuracy_;
}
QString ForecastObject::value_review()
{
    return value_review_;
}
