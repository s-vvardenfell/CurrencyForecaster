#ifndef FORECASTER_HPP
#define FORECASTER_HPP

#include <memory>
#include <fstream>

#include <QObject>
#include <QDebug>

#include "gq/Document.h"
#include "gq/Node.h"
#include "gq/Selection.h"

#include "data_handler.hpp"
#include "parser.hpp"


class Forecaster : public QObject
{
    Q_OBJECT
public:
    explicit Forecaster(QObject *parent = nullptr);

    bool startProgram();
    bool getForecastFromRBK();

private:
    std::unique_ptr<CurlHandler> curl_handler_;
    std::unique_ptr<DataBaseHandler> db_handler_;

    std::map<std::string, std::string> parameters_;
    std::map<std::string, std::string> rbk_forekast_data_;


    void logPage(const std::string& post_data) const;

    const std::string parseDataFromPage(const std::string& where, const std::string& lstr, const std::string& rstr, bool with_left = false) const;

signals:

};

#endif // FORECASTER_HPP
