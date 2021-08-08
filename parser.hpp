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


class Parser
{

public:
    explicit Parser();

    std::vector<Programm::ForecastData> getForecastsFromRBK();
    std::vector<Programm::ForecastData> getForecastsFromRmbr();

    bool parseCurrencyExchangeRateGPB(); //TODO + getter
private:
    std::unique_ptr<CurlHandler> curl_handler_;

    std::vector<Programm::ForecastData> rmbr_data_;
    std::vector<Programm::ForecastData> rbk_data_;

    std::map<std::string, std::string> parameters_;

    //возвращаемые значения и хранение данных продумать
    //мб стоит инсертить данные прогноза в бд на текущий день
    //а в нужном месте забирать
    bool parseForecastRBK();
    bool parseForecastRmbr();



};

#endif // PARSER_H
