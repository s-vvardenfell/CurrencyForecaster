#include "db_handler.hpp"



DataBaseHandler::DataBaseHandler(): driver_(nullptr),
    connection_(nullptr), parser_handler_(nullptr)
{
    readSettings();
    connectToDB();

    parser_handler_ = make_unique<Parser>();


}

void DataBaseHandler::readSettings()
{
    std::string settings_doc{ Programm::loadDocument("settings.txt") };

    size_t pos{ 0 };

    while ((pos = settings_doc.find(';')) != std::string::npos)
    {
        settings_.push_back(settings_doc.substr(0, pos));
        settings_doc.erase(0, (settings_.back()).size() + 1);
    }

}

void DataBaseHandler::connectToDB()
{
    driver_ = get_driver_instance();
    connection_ = driver_->connect(settings_.at(0), settings_.at(1), settings_.at(2));
    connection_->setSchema(settings_.at(3));
}


void DataBaseHandler::insertForecastsToDB()
{
    auto rbk_data = parser_handler_->getForecastsFromRBK();
    auto rmbr_data = parser_handler_->getForecastsFromRmbr();
}


void DataBaseHandler::insertCurrencyExchangeRateToDB()
{
//    auto exchange_rate = parser_handler_->getCurrencyExchangeRate(); //not implemented

}

double DataBaseHandler::getAccountBalance() const
{
    sql::Statement *stmt;
    sql::ResultSet *res;

    stmt = connection_->createStatement();
    res = stmt->executeQuery("SELECT balance FROM account_balance WHERE id = (SELECT MAX(id) FROM account_balance);");

    res->next();
    double balance = res->getInt("balance");

    delete res;
    delete stmt;

    return balance;
}

bool DataBaseHandler::updateBankAccount(int sum) const
{
    sql::Statement *stmt;
    sql::ResultSet *res;

    stmt = connection_->createStatement();
    res = stmt->executeQuery("SELECT MAX(id) FROM account_balance;");

    res->next();
    int id = res->getInt(1);

    delete res;
    delete stmt;

    sql::PreparedStatement *pstmt;
    pstmt = connection_->prepareStatement(
    "UPDATE account_balance SET date=?, balance=(balance+?) WHERE id =?;");

    pstmt->setString(1, Programm::getDateTime());
    pstmt->setInt(2, sum);
    pstmt->setInt(3, id);

    pstmt->executeUpdate();
    delete pstmt;

    //TODO нужна проверка
    return true;
}



void DataBaseHandler::createTable()
{
    sql::Statement *stmt;
    stmt = connection_->createStatement();
    stmt->execute("CREATE TABLE people33 (id INT PRIMARY KEY AUTO_INCREMENT NOT NULL, full_name VARCHAR(50) NOT NULL, "
        "birthday DATE NOT NULL, sex VARCHAR(10) NOT NULL);");

    delete stmt;
}

bool DataBaseHandler::insertBuySellOperation(const Purchase& purchase)
{
    sql::PreparedStatement *pstmt;
    pstmt = connection_->prepareStatement(
    "INSERT INTO my_purchases (date, type, amount, price, sum, bank_name, account) VALUES (?,?,?,?,?,?,?);");

    pstmt->setString(1, purchase.date);
    pstmt->setString(2, purchase.type);
    pstmt->setDouble(3, purchase.amount);
    pstmt->setDouble(4, purchase.price);
    pstmt->setDouble(5, purchase.sum);
    pstmt->setString(6, purchase.bank_name);
    pstmt->setString(7, purchase.account);

    pstmt->executeUpdate();
    delete pstmt;

    //TODO нужна проверка
    return true;
}











