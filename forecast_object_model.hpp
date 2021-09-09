#ifndef FORECASTOBJECTMODEL_HPP
#define FORECASTOBJECTMODEL_HPP

#include <QAbstractListModel>
#include <QObject>

#include "forecast_object.hpp"

class ForecastObjectModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ForecastObjectModelRoles
    {
        ParserRole = Qt::UserRole + 1,
        ValueRole,
        ForecastDateRole,
        PeriodRole,
        AccuracyRole,
        ValueReviewRole
    };

    explicit ForecastObjectModel(QObject *parent = nullptr);

    void addForecastObject(const ForecastObject &object);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<ForecastObject> forecast_object_;

};

#endif // FORECASTOBJECTMODEL_HPP
