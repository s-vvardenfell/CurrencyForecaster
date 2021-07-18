#include "forecaster.hpp"

static const std::string path {"/home/chaginsergey/Qt Projects/pages/"};

Forecaster::Forecaster(QObject *parent) : QObject(parent)
{
    //переименовать файлы классов curl и db handler
    //добавить исключения
    //logPage мб должен принимать номер документа-название для удобства
    //добавить в rambler и рбк проверку вдруг появится новый источник/обновятся данные

    //там где week year month пересчитать в рельные даты мб? будет единообразно с рбк

    //парсить тарифы того банка где буду менять
    //логин в лк альфы? или тиньков? мб александровкий - лучше тариф чем в альфе

    //forecaster дб таки parser'ом
    //отдельный класс который работает с площадкой - логин, продажа-покупка AccountHandler


    //getForecasts() вызывает функции-парсеры разных площадок
    //мб storeForecasts() //полученные прогнозы сохраняет в бд
    //мб тогда не нужны переменные - члены rmbr_vec_ и тд,
    //ф-ии парсинга будут передавать результат работы
    //сразу в ф-ю сохранения в бд, мб вызываться ею или вызываться в аргументах
    //какой класс создает чьи экземпляры? мб дб_хандлер создает экземпляр форекастера - парсера
        //и получает getRBK / getRMBRData() ? геттерами


    curl_handler_ = std::make_unique<CurlHandler>();
//    db_handler_ = std::make_unique<DataBaseHandler>(); //мб дб_хандлер создает экземпляр форекастера

}

bool Forecaster::startProgram()
{
    getForecastsFromRBK();
    getForecastsFromRmbr();

    return true;
}


bool Forecaster::getForecastsFromRBK()
{
    curl_handler_->setHeader("Connection", "Keep-Alive");
    curl_handler_->setHeader("Host", "quote.rbc.ru");
    curl_handler_->setHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) 	Chrome/91.0.4472.124 Safari/537.36");
    curl_handler_->setHeader("Accept", "text/html, application/xhtml+xml, image/jxr, */*");
    curl_handler_->setHeader("Referer", "https://www.google.com/");
    curl_handler_->setHeader("Accept-Language", "en-US,en;q=0.9");

    const std::string url_rbk{"https://quote.rbc.ru/ticker/59111"};
    curl_handler_->query(url_rbk, methodType::GET);

    logPage();

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

        ForecastData rdata{};

        rdata.forecaster_ = node.find(".q-item__review__value").nodeAt(2).text();
        rdata.value_ = normalizeString(node.find(".q-item__review__sum").nodeAt(0).text());
        rdata.forecast_date_ = html.find(".q-item__review__date_big").nodeAt(i).text();
        rdata.period_ = node.find(".q-item__review__value").nodeAt(1).text();
        rdata.accuracy_ = normalizeString(node.find(".q-item__review__value").nodeAt(3).text());
        rdata.value_review_= normalizeString(node.find(".q-item__review__change").nodeAt(0).text());

        rbk_vec_.push_back(rdata);
    }

//    for(const auto& forecast: rbk_vec_)
//    {
//        qDebug()<<QString::fromStdString(forecast.forecaster_ +" " + forecast.forecast_date_+" "+forecast.value_+" "+forecast.period_+" "+forecast.accuracy_+" "+forecast.value_review_);
//    }

    return true;
}


bool Forecaster::getForecastsFromRmbr()
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
            ForecastData rdata{};
            json temp = jdata_period[i];

            rdata.forecaster_ = temp["forecaster"]["name"].get<std::string>();

            std::string temp_str = temp["date"].get<std::string>();
            rdata.forecast_date_ = temp_str.substr(0, temp_str.find('T'));

            rdata.value_ = to_string(temp.find("value").value());
            rdata.period_ = period;

            rmbr_vec_.push_back(rdata);

        }
    }

//    for(const auto& forecast: rmbr_vec_)
//    {
//        qDebug()<<QString::fromStdString(forecast.forecaster_ +" " + forecast.forecast_date_+" "+forecast.value_+" "+forecast.period_+" "+forecast.accuracy_+" "+forecast.value_review_);
//    }

    return true;
}

const std::string Forecaster::loadDocument(const std::string& filename) const
{
    //std::ifstream infile;

    //if (!infile)
    //	throw std::runtime_error("Can't open file: "+ filename);

    //std::ostringstream oss;

    //std::copy(std::istreambuf_iterator<char>(infile),
    //	std::istreambuf_iterator<char>(), std::ostreambuf_iterator<char>(oss));

    //infile.close();

    //return oss.str();

    std::ifstream ifile(filename);
    if (!ifile) { qDebug() << "Cannot read file"; return ""; }
    std::string page, line;
    while (getline(ifile, line))
        page += line;

    return page;
}

bool Forecaster::saveDocument(const std::string& filename, const std::string& data) const
{
    std::ofstream ofile(filename);
    if (!ofile) { qDebug() << "Cannot open file"; return false; }
    ofile << data;
    ofile.close();
    return true;

}

const std::string Forecaster::parseDataFromPage(const std::string& where, const std::string& lstr, const std::string& rstr, bool with_left) const
{
    size_t lpos{}, rpos{};
    std::string ret_val;

    if ((where.find(lstr) == std::string::npos) || (where.find(rstr) == std::string::npos))
    {
        qDebug()<<QString::fromLatin1("No data to parse\n");
        return "";
    }

    if (!with_left)
    {
        lpos = where.find(lstr);
        rpos = where.find(rstr, lpos);
        ret_val = where.substr(lpos + lstr.size(), rpos - lpos - lstr.size());
    }
    else
    {
        lpos = where.find(lstr);
        rpos = where.find(rstr, lpos);
        ret_val = where.substr(lpos, rpos - lpos);
    }

    while ((lpos = ret_val.find("\"")) != std::string::npos) ret_val.erase(lpos, 1);

    return ret_val;
}

void Forecaster::logPage(const std::string& data) const
{
#if defined(NO_LOGS)
    return;
#endif

    static int page_counter{1};

    std::ofstream ofile;
    ofile.open(path + std::to_string(page_counter) + "_page_.xml");

    if (!data.empty())
        ofile << data << "\n\n";

    ofile << curl_handler_->getResponseHeaders() << "\n\n" << curl_handler_->getResponse();
    ofile.close();

    ++page_counter;
}

void Forecaster::normalizeString(std::string& where, const std::string& what)
{
    size_t to_remove{};

    while((to_remove = where.find(what)) != std::string::npos)
        where.erase(to_remove, 1);

}

std::string Forecaster::normalizeString(std::string where)
{
    size_t to_remove{};

    while((to_remove = where.find('\t')) != std::string::npos) {where.erase(to_remove, 1);}
    while((to_remove = where.find('\r')) != std::string::npos) {where.erase(to_remove, 1);}
    while((to_remove = where.find('\n')) != std::string::npos) {where.erase(to_remove, 1);}
    while((to_remove = where.find(' ')) != std::string::npos) {where.erase(to_remove, 1);}

    return where;
}












