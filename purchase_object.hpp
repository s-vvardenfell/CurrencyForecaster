#ifndef PURCHASEOBJECT_H
#define PURCHASEOBJECT_H

#include <QAbstractListModel>
#include <QStringList>
#include <QObject>

class PurchaseObject
{
public:
    PurchaseObject(const QString &type, const QString &size);

    QString id() const;
    QString date() const;
    QString ptype() const;
    QString amount() const;
    QString price() const;
    QString sum() const;

private:

    QString id_;
    QString date_;
    QString ptype_;
    QString amount_;
    QString price_;
    QString sum_;
};

class PurchaseModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum PurchaseRoles {
        IdRole = Qt::UserRole + 1,
        DateRole,
        PtypeRole,
        AmountRole,
        PriceRole,
        SumRole
    };

    PurchaseModel(QObject *parent = 0);
//![1]

    void addPurchase(const PurchaseObject &Purchase);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<PurchaseObject> m_Purchases;
//![2]
};

#endif // PURCHASEOBJECT_H
