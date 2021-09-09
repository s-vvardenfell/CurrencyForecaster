#ifndef PURCHASEOBJECT_H
#define PURCHASEOBJECT_H

#include "db_handler.hpp"

class PurchaseObject
{
public:
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

#endif // PURCHASEOBJECT_H
