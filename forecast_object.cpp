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

QString ForecastObject::parser() const
{
    return parser_;
}

QString ForecastObject::value() const
{
    return value_;
}

QString ForecastObject::forecast_date() const
{
    return forecast_date_;
}

QString ForecastObject::period() const
{
    return period_;
}

QString ForecastObject::accuracy() const
{
    return accuracy_;
}
QString ForecastObject::value_review() const
{
    return value_review_;
}
