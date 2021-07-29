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

//убрать QObject или понадобится для работы с бд?
class DataBaseHandler
{
private:
    sql::Driver *driver_;
    sql::Connection *connect_;

    std::unique_ptr<Parser> parser_handler_;
    std::vector<std::string> settings_;

    void readSettings();
    void connect_to_DB();



public:
    explicit DataBaseHandler();

     void create_table();

    void insertForecastsToDB();
    void insertCurrencyExchangeRateToDB();




signals:

};

#endif // DB_HANDLER_H
