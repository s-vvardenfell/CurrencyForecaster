#include "forecast_object_model.hpp"

ForecastObjectModel::ForecastObjectModel(QObject *parent) : QAbstractListModel(parent)
{

}

void ForecastObjectModel::addForecastObject(const ForecastObject &object)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    forecast_object_ << object;
    endInsertRows();
}

int ForecastObjectModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return forecast_object_.count();
}

QVariant ForecastObjectModel::data(const QModelIndex & index, int role) const
{
    if (index.row() < 0 || index.row() >= forecast_object_.count())
        return QVariant();

    const ForecastObject &object = forecast_object_[index.row()];

    if (role == ParserRole)
        return object.parser();
    else if (role == ValueRole)
        return object.value();
    else if (role == ForecastDateRole)
        return object.forecast_date();
    else if (role == PeriodRole)
        return object.period();
    else if (role == AccuracyRole)
        return object.accuracy();
    else if (role == ValueReviewRole)
        return object.value_review();

    return QVariant();
}

QHash<int, QByteArray> ForecastObjectModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[ParserRole] = "parser";
    roles[ValueRole] = "value";
    roles[ForecastDateRole] = "forecast_date";
    roles[PeriodRole] = "period";
    roles[AccuracyRole] = "accuracy";
    roles[ValueReviewRole] = "value_review";

    return roles;
}
