#include "parser.hpp"



Parser::Parser() : curl_handler_(nullptr)
{
    curl_handler_ = std::make_unique<CurlHandler>();
}

bool Parser::parseRBK()
{
    curl_handler_->setHeader("Connection", "Keep-Alive");
    curl_handler_->setHeader("Host", "quote.rbc.ru");
    curl_handler_->setHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) 	Chrome/91.0.4472.124 Safari/537.36");
    curl_handler_->setHeader("Accept", "text/html, application/xhtml+xml, image/jxr, */*");
    curl_handler_->setHeader("Referer", "https://www.google.com/");
    curl_handler_->setHeader("Accept-Language", "en-US,en;q=0.9");

    const std::string url_rbk{"https://quote.rbc.ru/ticker/59111"};
    curl_handler_->query(url_rbk, methodType::GET);

    CDocument html;
    html.parse(curl_handler_->getResponse());

    CSelection select = html.find(".q-item__review__container");

    if (select.nodeNum() == 0)
        return false;
            //else
            //    cerr << select.nodeNum() << endl;

            //cerr<< select.nodeAt(1).text();


    for (std::size_t i = 0; i < select.nodeNum(); ++i)
    {
        CNode node = select.nodeAt(i);

        Programm::ForecastData rdata{};

        rdata.Parser_ = node.find(".q-item__review__value").nodeAt(2).text();
        rdata.value_ = Programm::normalizeString(node.find(".q-item__review__sum").nodeAt(0).text());
        rdata.forecast_date_ = html.find(".q-item__review__date_big").nodeAt(i).text();
        rdata.period_ = node.find(".q-item__review__value").nodeAt(1).text();
        rdata.accuracy_ = Programm::normalizeString(node.find(".q-item__review__value").nodeAt(3).text());
        rdata.value_review_= Programm::normalizeString(node.find(".q-item__review__change").nodeAt(0).text());

        rbk_data_.push_back(rdata);
    }

//    for(const auto& forecast: rbk_vec_)
//    {
//        qDebug()<<QString::fromStdString(forecast.Parser_ +" " + forecast.forecast_date_+" "+forecast.value_+" "+forecast.period_+" "+forecast.accuracy_+" "+forecast.value_review_);
//    }

    return true;
}


bool Parser::parseRmbr()
{
    curl_handler_->setHeader("Host", "finance.rambler.ru");
    curl_handler_->setHeader("Referer", "https://www.yandex.ru/");

    const std::string url_rmb{"https://finance.rambler.ru/currencies/consensus"};

    curl_handler_->query(url_rmb, methodType::GET);

    CDocument html;
    html.parse(curl_handler_->getResponse());
    CSelection select = html.find(".j-currency-forecast");

    json data = json::parse(select.nodeAt(0).attribute("data-data").data());

    std::array<std::string, 3> periods = {"week", "month", "year"};

    for(const auto& period: periods)
    {
        json jdata_period = data[period];

        for(size_t i = 0; i<jdata_period.size(); ++i)
        {
            Programm::ForecastData rdata{};
            json temp = jdata_period[i];

            rdata.Parser_ = temp["Parser"]["name"].get<std::string>();

            std::string temp_str = temp["date"].get<std::string>();
            rdata.forecast_date_ = temp_str.substr(0, temp_str.find('T'));

            rdata.value_ = to_string(temp.find("value").value());
            rdata.period_ = period;

            rmbr_data_.push_back(rdata);

        }
    }

//    for(const auto& forecast: rmbr_vec_)
//    {
//        qDebug()<<QString::fromStdString(forecast.Parser_ +" " + forecast.forecast_date_+" "+forecast.value_+" "+forecast.period_+" "+forecast.accuracy_+" "+forecast.value_review_);
//    }

    return true;
}


std::vector<Programm::ForecastData> Parser::getForecastsFromRBK()
{
    return rmbr_data_;
}

std::vector<Programm::ForecastData> Parser::getForecastsFromRmbr()
{
    return rbk_data_;
}










