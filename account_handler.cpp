#include "account_handler.hpp"

AccountHandler::AccountHandler(QObject *parent) : QObject(parent),
    curl_handler_(nullptr), db_handler_(nullptr), parser_(nullptr),
    bank_name_("Some bank"), account_("1234567890")
{
    curl_handler_ = std::make_unique<CurlHandler>();
    db_handler_ = std::make_unique<DataBaseHandler>();
    parser_ = std::make_unique<Parser>();
}

bool AccountHandler::login()
{
    //данные откуда берутся?
    //вводить каждый раз или тянуть с бд?
    return true;
}

bool AccountHandler::logout()
{
    return true;
}

bool AccountHandler::buy(double amount)
{
    //авторизауется? или уже авторизован
    //совершает покупку
    //заносит данные в бд об операции
    //покупает amount долларов на счете

//    //мб добавить функцию, которая иниц-т Purchase и возвращает заполненный экземпляр
//    //по сути всё повторяется
//    Purchase purchase;
//    purchase.date = getCurrentTimeStamp();
//    purchase.type = __func__;
//    purchase.amount = amount;
//    purchase.price = parser_->getCurrentExcangeRate();
//    purchase.sum = (amount * purchase.price);
//    purchase.bank_name = bank_name_;
//    purchase.account = account_;

    //TODO вывод не в консоль а в qml окно с ссобщением
    if(db_handler_->insertBuySellOperation(getPurchaseInstance(amount, "buy")))
    {
        qDebug() << "Bought "<<amount<<" dollars";
        return true;
    }
    else
    {
        qDebug() << "Some error occured during bying";
        return false;
    }
}

bool AccountHandler::sell(double amount)
{
//    Purchase purchase;
//    purchase.date = getCurrentTimeStamp();
//    purchase.type = __func__;
//    purchase.amount = amount;
//    purchase.price = parser_->getCurrentExcangeRate();
//    purchase.sum = (amount * purchase.price);
//    purchase.bank_name = bank_name_;
//    purchase.account = account_;

    //TODO вывод не в консоль а в qml окно с ссобщением
    if(db_handler_->insertBuySellOperation(getPurchaseInstance(amount, "sell")))
    {
        qDebug() << "Sold "<<amount<<" dollars";
        return true;
    }
    else
    {
        qDebug() << "Some error occured during selling";
        return false;
    }
}

bool AccountHandler::sellAll()
{
    double balance = getBankAccountBalanceFromDB();
    if(sell(balance)) //вызывает продажу с аргументом-балансом денег на счету
    {
        qDebug() << "Sold all "<<balance<<" dollars";
        return true;
    }
    else
    {
        qDebug() << "Some error occured during selling all";
        return false;
    }

}

double AccountHandler::getBankAccountBalanceFromDB()
{
    return db_handler_->getAccountBalance();
}

double AccountHandler::getBankAccountBalanceFromSite()
{
    return 30.55;
}

const string AccountHandler::getCurrentTimeStamp() const
{
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    stringstream ss; ss<< put_time(&tm, "%H:%M:%S %d.%m.%Y");
    return ss.str();
}

const Purchase AccountHandler::getPurchaseInstance(double amount,
                                                   const std::string& type) const
{
    Purchase purchase;
    purchase.date = getCurrentTimeStamp();
    purchase.type = type;
    purchase.amount = amount;
    purchase.price = parser_->getCurrentExcangeRate();
    purchase.sum = (amount * purchase.price);
    purchase.bank_name = bank_name_;
    purchase.account = account_;

    return purchase;
}

//будет принимать аргументы
bool AccountHandler::updateBankAccountBalanceOnDB() const
{
    return db_handler_->updateBankAccount();
}
