#include "db_handler.hpp"



DataBaseHandler::DataBaseHandler(): driver_(nullptr),
    connection_(nullptr), parser_handler_(nullptr)
{
    readSettings();
    connect_to_DB();

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

void DataBaseHandler::connect_to_DB()
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

void DataBaseHandler::create_table()
{
    sql::Statement *stmt;
    stmt = connection_->createStatement();
    stmt->execute("CREATE TABLE people33 (id INT PRIMARY KEY AUTO_INCREMENT NOT NULL, full_name VARCHAR(50) NOT NULL, "
        "birthday DATE NOT NULL, sex VARCHAR(10) NOT NULL);");

    delete stmt;
}

void DataBaseHandler::insert_purchase(const Purchase& purchase)
{
    sql::PreparedStatement *pstmt;
    pstmt = connection_->prepareStatement(
    "INSERT INTO my_purchases (date, amount, price, sum, bank_name, account) VALUES (?,?,?,?,?,?);");

    pstmt->setString(1, purchase.date);
    pstmt->setInt(2, purchase.amount);
    pstmt->setDouble(3, purchase.price);
    pstmt->setDouble(4, purchase.sum);
    pstmt->setString(5, purchase.bank_name);
    pstmt->setString(6, purchase.account);

    pstmt->executeUpdate();
    delete pstmt;
}











