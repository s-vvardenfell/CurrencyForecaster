#ifndef ACCOUNTHANDLER_HPP
#define ACCOUNTHANDLER_HPP

#include <memory>
#include <iomanip>

#include <QObject>
#include <QDebug>

#include "curl_handler.hpp"
#include "db_handler.hpp"
#include "parser.hpp"

class AccountHandler : public QObject
{
    Q_OBJECT

public:
    explicit AccountHandler(QObject *parent = nullptr);

    Q_INVOKABLE bool buy(double amount);
    Q_INVOKABLE bool sell(double amount);
    Q_INVOKABLE bool sellAll();

    //отдельная ф-я сверяет баланс и корректирует если есть разница
    Q_INVOKABLE double getBankAccountBalanceFromDB(); //баланс в бд
    Q_INVOKABLE double getBankAccountBalanceFromSite(); //баланс в лк на сайте
    Q_INVOKABLE double getExcangeRate(); //нужна ли эта ф-я если парсим все валюты блоком?

    std::vector<CurrencyExchangeData> getExcangeRates() const;
    std::vector<Purchase> getActiveLots() const;

private:
    std::unique_ptr<DataBaseHandler> db_handler_;
    std::unique_ptr<Parser> parser_;

    std::string bank_name_; //сделать аргументами по умолчанию getPurchaseInstance, убрать отсюда
    std::string account_;

    const Purchase getPurchaseInstance(double amount, const std::string& type) const;
    bool updateBankAccountBalanceOnDB(int sum) const;

//public slots:


//signals:


};

#endif // ACCOUNTHANDLER_HPP
