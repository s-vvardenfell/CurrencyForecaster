#ifndef DB_HANDLER_H
#define DB_HANDLER_H

#include <QDebug>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "parser.hpp"

enum class OperationType
{
    SELL,
    BUY
};

typedef struct Purchase
{
    std::string date;
    std::string type;
    double      amount;
    double      price;
    double      sum;
    std::string bank_name;
    std::string account;

}Purchase;

class DataBaseHandler
{

private:
    sql::Driver *driver_;
    sql::Connection *connection_;
    std::vector<std::string> settings_;

    void connectToDB();

public://проверить остальные методы на const
    explicit DataBaseHandler();

    void createTable();
    bool insertBuySellOperation(const Purchase& purchase);
    void insertCurrencyExchangeRateToDB();
    double getAccountBalance() const;
    bool updateBankAccount(int amount) const;
    std::vector<Purchase> getActualPurchases() const;

};

#endif // DB_HANDLER_H
