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

    double getCurrentExcangeRate();
    std::vector<CurrencyExchangeData> parseCurrencyExchangeRate() const;

private:
    std::vector<std::string> settings_;
    std::unique_ptr<CurlHandler> curl_handler_;
};

#endif // PARSER_H
