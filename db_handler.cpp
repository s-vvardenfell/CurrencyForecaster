#include "db_handler.hpp"



DataBaseHandler::DataBaseHandler(): driver_(nullptr),
    connection_(nullptr), parser_handler_(nullptr)
{
    settings_ = Programm::readSettings("db_settings.txt");

    connectToDB();

    parser_handler_ = make_unique<Parser>();

}

void DataBaseHandler::connectToDB()
{
    driver_ = get_driver_instance();
    connection_ = driver_->connect(settings_.at(0), settings_.at(1), settings_.at(2));
    connection_->setSchema(settings_.at(3));
}

//TODO
void DataBaseHandler::insertForecastsToDB()
{
    auto data1 = parser_handler_->parseForecast0();
    auto data2 = parser_handler_->parseForecast1();
}

//TODO
void DataBaseHandler::insertCurrencyExchangeRateToDB()
{
//    auto exchange_rate = parser_handler_->getCurrencyExchangeRate(); //not implemented

}

//нужен ли select max если там сейчас одно значение
//и оно update просто?
double DataBaseHandler::getAccountBalance() const
{
    sql::Statement *stmt;
    sql::ResultSet *res;

    stmt = connection_->createStatement();
    res = stmt->executeQuery("SELECT balance FROM account_balance WHERE id = "
                            "(SELECT MAX(id) FROM account_balance);");

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

std::vector<Purchase> DataBaseHandler::getActualPurchases() const
{
    std::vector<Purchase> purchases;
    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;

    pstmt = connection_->prepareStatement(
    "SELECT date, type, amount, price, sum, bank_name, account FROM my_purchases WHERE type = 'buy'");

    res = pstmt->executeQuery();


    while (res->next())
    {
        Purchase purchase;

        purchase.date = res->getString(1);
        purchase.type = res->getString(2);
        purchase.amount = res->getDouble(3);
        purchase.price = res->getDouble(4);
        purchase.sum = res->getDouble(5);
        purchase.bank_name = res->getString(6);
        purchase.account = res->getString(7);

        purchases.push_back(purchase);
    }

    delete res;
    delete pstmt;

    return purchases;
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





