#ifndef FORECASTOBJECT_HPP
#define FORECASTOBJECT_HPP

#include "parser.hpp"

class ForecastObject
{
public:
    ForecastObject(const ForecastData &data);

    QString parser() const;
    QString value() const;
    QString forecast_date() const;
    QString period() const;
    QString accuracy() const;
    QString value_review() const;

private:
    QString parser_;
    QString value_;
    QString forecast_date_;
    QString period_;
    QString accuracy_{"no"};
    QString value_review_{"no"};
};

#endif // FORECASTOBJECT_HPP
