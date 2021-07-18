#ifndef FORECASTER_HPP
#define FORECASTER_HPP

//#define NO_LOGS

#include <memory>
#include <fstream>
#include <vector>

#include <QObject>
#include <QDebug>

#include "gq/Document.h"
#include "gq/Node.h"
#include "gq/Selection.h"

#include "nlohmann/json.hpp"

#include "db_handler.hpp"
#include "curl_handler.hpp"

using json = nlohmann::json;

typedef struct ForecastData
{
    std::string forecaster_;
    std::string value_;
    std::string forecast_date_;
    std::string period_;
    std::string accuracy_{"null"};
    std::string value_review_{"null"};

}ForecastData;

class Forecaster : public QObject
{
    Q_OBJECT
public:
    explicit Forecaster(QObject *parent = nullptr);

    bool startProgram();
    bool getForecastsFromRBK();
    bool getForecastsFromRmbr();

private:
    std::unique_ptr<CurlHandler> curl_handler_;
//    std::unique_ptr<DataBaseHandler> db_handler_;

    std::vector<ForecastData> rmbr_vec_;
    std::vector<ForecastData> rbk_vec_;

    std::map<std::string, std::string> parameters_;
//    std::map<std::string, std::string> rbk_forekast_data_;

    const std::string loadDocument(const std::string& filename) const;
    bool saveDocument(const std::string& filename, const std::string& data) const;
    void logPage(const std::string& post_data="") const;

    const std::string parseDataFromPage(const std::string& where, const std::string& lstr, const std::string& rstr, bool with_left = false) const;
    void normalizeString(std::string& where, const std::string& what);
    std::string normalizeString(std::string where);
signals:

};

#endif // FORECASTER_HPP
