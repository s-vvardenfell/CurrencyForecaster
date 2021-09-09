#ifndef FORECASTOBJECT_HPP
#define FORECASTOBJECT_HPP

#include "parser.hpp"

class ForecastObject
{
public:
    ForecastObject(const ForecastData &data);

    QString parser();
    QString value();
    QString forecast_date();
    QString period();
    QString accuracy();
    QString value_review();

private:
    QString parser_;
    QString value_;
    QString forecast_date_;
    QString period_;
    QString accuracy_{"no"};
    QString value_review_{"no"};
};

#endif // FORECASTOBJECT_HPP
