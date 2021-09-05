#include "parser.hpp"



Parser::Parser() :
    curl_handler_(nullptr), rmbr_data_(), rbk_data_(), parameters_(),  price_()
{
    curl_handler_ = std::make_unique<CurlHandler>();

    curl_handler_->setHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) 	Chrome/91.0.4472.124 Safari/537.36");
    curl_handler_->setHeader("Connection", "Keep-Alive");
    curl_handler_->setHeader("Accept-Language", "en-US,en;q=0.9");

    settings_ = Programm::readSettings("parser_settings.txt");

}

std::vector<ForecastData> Parser::parseForecast0()
{
    const std::string url{settings_.at(0)};
    std::vector<ForecastData> fdata;

    //убрал хедеры в конструктор
    curl_handler_->setHeader("Host", Programm::getHostFromUrl(url));
    curl_handler_->setHeader("Accept", "text/html, application/xhtml+xml, image/jxr, */*");
    curl_handler_->setHeader("Referer", "https://www.google.com/");

    curl_handler_->query(url, methodType::GET);

    CDocument html;
    html.parse(curl_handler_->getResponse());

    CSelection select = html.find(".q-item__review__container");

    if (select.nodeNum() == 0)
        return fdata;
            //else
            //    cerr << select.nodeNum() << endl;

            //cerr<< select.nodeAt(1).text();


    for (std::size_t i = 0; i < select.nodeNum(); ++i)
    {
        CNode node = select.nodeAt(i);

        ForecastData rdata{};

        rdata.Parser_ = node.find(".q-item__review__value").nodeAt(2).text();
        rdata.value_ = Programm::normalizeString(node.find(".q-item__review__sum").nodeAt(0).text());
        rdata.forecast_date_ = html.find(".q-item__review__date_big").nodeAt(i).text();
        rdata.period_ = node.find(".q-item__review__value").nodeAt(1).text();
        rdata.accuracy_ = Programm::normalizeString(node.find(".q-item__review__value").nodeAt(3).text());
        rdata.value_review_= Programm::normalizeString(node.find(".q-item__review__change").nodeAt(0).text());

        fdata.push_back(rdata);
    }

//    for(const auto& forecast: rbk_vec_)
//    {
//        qDebug()<<QString::fromStdString(forecast.Parser_ +" " + forecast.forecast_date_+" "+forecast.value_+" "+forecast.period_+" "+forecast.accuracy_+" "+forecast.value_review_);
//    }

    return fdata;
}


std::vector<ForecastData> Parser::parseForecast1()
{
    const std::string url{settings_.at(1)};
    std::vector<ForecastData> fdata;

    curl_handler_->setHeader("Host", Programm::getHostFromUrl(url));
    curl_handler_->setHeader("Referer", "https://www.yandex.ru/");

    curl_handler_->query(url, methodType::GET);

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
            ForecastData rdata{};
            json temp = jdata_period[i];

            rdata.Parser_ = temp["Parser"]["name"].get<std::string>();

            std::string temp_str = temp["date"].get<std::string>();
            rdata.forecast_date_ = temp_str.substr(0, temp_str.find('T'));

            rdata.value_ = to_string(temp.find("value").value());
            rdata.period_ = period;

            fdata.push_back(rdata);

        }
    }

//    for(const auto& forecast: rmbr_vec_)
//    {
//        qDebug()<<QString::fromStdString(forecast.Parser_ +" " + forecast.forecast_date_+" "+forecast.value_+" "+forecast.period_+" "+forecast.accuracy_+" "+forecast.value_review_);
//    }

    return fdata;
}

double Parser::getCurrentExcangeRate()
{
   //мб где-то в конструкторе вызывать parseCurrencyExchangeRate
    price_ = 78.45;

    return price_;
}

std::vector<CurrencyExchangeData> Parser::parseCurrencyExchangeRate() const
{
    const std::string url{settings_.at(2)};
    vector<CurrencyExchangeData> data{};

    curl_handler_->setHeader("Host", Programm::getHostFromUrl(url));
    curl_handler_->setHeader("User-Agent", "Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:91.0) Gecko/20100101 Firefox/91.0");

    curl_handler_->query(url, methodType::GET);

    string table_name = Programm::parseDataFromPage(curl_handler_->getResponse(),
                                                    "Table__table_", " Table__", true);
    CDocument html{};
    html.parse(curl_handler_->getResponse());

    CSelection select = html.find('.' + table_name);

    if(!select.nodeNum())
    {
        qDebug()<<"No results in parseCurrencyExchangeRate()";
        return data;
    }

    int num = select.nodeAt(0).childAt(1).childNum();

    data.reserve(num);

    for(int i = 0; i< num; ++ i)
    {
        CurrencyExchangeData temp;

        temp.currency_ = select.nodeAt(0).childAt(1).childAt(i).childAt(0).text().c_str();
        temp.change_ = select.nodeAt(0).childAt(1).childAt(i).childAt(1).text().c_str();
        temp.cost_ = select.nodeAt(0).childAt(1).childAt(i).childAt(2).text().c_str();

        data.push_back(temp);
    }

    return data;
}


std::vector<ForecastData> Parser::getForecastsFromRBK()
{
    return rmbr_data_;
}

std::vector<ForecastData> Parser::getForecastsFromRmbr()
{
    return rbk_data_;
}











