#ifndef PARSER_H
#define PARSER_H

//#define NO_LOGS

#include <memory>
#include <fstream>
#include <vector>

#include <QDebug>

#include "gq/Document.h"
#include "gq/Node.h"
#include "gq/Selection.h"

#include "nlohmann/json.hpp"

#include "curl_handler.hpp"
#include "programm.hpp"


using json = nlohmann::json;

//вынести в отельный файл?

typedef struct ForecastData
{
    std::string Parser_;
    std::string value_;
    std::string forecast_date_;
    std::string period_;
    std::string accuracy_{"null"};
    std::string value_review_{"null"};

}ForecastData;

typedef struct CurrencyExchangeData
{
    std::string currency_;
    std::string change_;
    std::string cost_;

}CurrencyExchangeData;

class Parser
{

public:
    explicit Parser();

    std::vector<ForecastData> getForecastsFromRBK();
    std::vector<ForecastData> getForecastsFromRmbr();
    double getCurrentExcangeRate();

//private:
    std::unique_ptr<CurlHandler> curl_handler_;

    std::vector<ForecastData> rmbr_data_;
    std::vector<ForecastData> rbk_data_;

    std::map<std::string, std::string> parameters_;

    double price_;

    //возвращаемые значения и хранение данных продумать
    //мб стоит инсертить данные прогноза в бд на текущий день
    //а в нужном месте забирать
    bool parseForecastRBK();
    bool parseForecastRmbr();
    bool parseCurrencyExchangeRate(); //TODO




};

#endif // PARSER_H
