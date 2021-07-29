#include "db_handler.hpp"



DataBaseHandler::DataBaseHandler(): driver_(nullptr), connect_(nullptr), parser_handler_(nullptr)
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
    connect_ = driver_->connect(settings_.at(0), settings_.at(1), settings_.at(2));
    connect_->setSchema(settings_.at(3));

    for(const auto& a: settings_)
        qDebug()<<a.c_str()<<Qt::endl;
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
    stmt = connect_->createStatement();
    stmt->execute("CREATE TABLE people33 (id INT PRIMARY KEY AUTO_INCREMENT NOT NULL, full_name VARCHAR(50) NOT NULL, "
        "birthday DATE NOT NULL, sex VARCHAR(10) NOT NULL);");

    delete stmt;

}

