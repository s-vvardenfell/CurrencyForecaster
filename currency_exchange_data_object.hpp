#ifndef CURRENCYEXCHANGEDATAOBJECT_HPP
#define CURRENCYEXCHANGEDATAOBJECT_HPP

#include <QAbstractListModel>
#include <QStringList>
#include <QObject>

#include "db_handler.hpp"
#include "parser.hpp"

class CurrencyExchangeDataObject
{
public:
    CurrencyExchangeDataObject(const CurrencyExchangeData &currencyExchangeData);

    QString currency() const;
    QString change() const;
    QString cost() const;

private:

    QString currency_;
    QString change_;
    QString cost_;
};

class CurrencyExchangeDataObjectModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum CurrencyExchangeDataObjectRoles
    {
        CurrencyRole = Qt::UserRole + 1,
        ChangeRole,
        CostRole
    };

    CurrencyExchangeDataObjectModel(QObject *parent = 0);

    void addCurrencyExchangeDataObject(const CurrencyExchangeDataObject &CurrencyExchangeDataObject);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<CurrencyExchangeDataObject> m_CurrencyExchangeDataObjects;

};

#endif // CURRENCYEXCHANGEDATAOBJECT_HPP


