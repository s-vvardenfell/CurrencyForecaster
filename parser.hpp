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
    std::string parser_;
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

    std::vector<ForecastData> parseForecast0();
    std::vector<ForecastData> parseForecast1();

    double getCurrentExcangeRate(); //вызывается в Account!! - временно вызывалось вместо нижней ф-и
    std::vector<CurrencyExchangeData> parseCurrencyExchangeRate() const;

private:
    std::vector<std::string> settings_;
    std::unique_ptr<CurlHandler> curl_handler_;
};

#endif // PARSER_H
