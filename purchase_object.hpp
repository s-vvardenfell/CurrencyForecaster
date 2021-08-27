#ifndef PURCHASEOBJECT_H
#define PURCHASEOBJECT_H

#include <QAbstractListModel>
#include <QStringList>
#include <QObject>

#include "db_handler.hpp"

class PurchaseObject
{
public:
    PurchaseObject(const QString &type, const QString &size); //FOR TEST
    PurchaseObject(const Purchase &purchase);

    QString date() const;
    QString ptype() const;
    double amount() const;
    double price() const;
    double sum() const;
    QString bank_name() const;
    QString account() const;

private:
    QString date_;
    QString ptype_;
    double amount_;
    double price_;
    double sum_;
    QString bank_name_;
    QString account_;
};

class PurchaseModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum PurchaseRoles {
        DateRole = Qt::UserRole + 1,
        PtypeRole,
        AmountRole,
        PriceRole,
        SumRole,
        BankNameRole,
        AccountRole
    };

    PurchaseModel(QObject *parent = 0);

    void addPurchase(const PurchaseObject &Purchase);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<PurchaseObject> m_Purchases;

};

#endif // PURCHASEOBJECT_H
