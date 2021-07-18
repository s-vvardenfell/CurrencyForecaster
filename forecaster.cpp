#include "forecaster.hpp"

static const std::string path {"/home/chaginsergey/Qt Projects/pages/"};

Forecaster::Forecaster(QObject *parent) : QObject(parent)
{
    //переименовать файлы классов curl и db handler
    //добавить исключения
    //logPage мб должен принимать номер документа-название для удобства
    //rbk_forekast_data_ можно заменить на структуру или что-то общее для всех сайтов?
        //в тот же map можно после очистки положить другие данные

    //спарсить rambler
    //добавить в rambler и рбк проверку вдруг появится новый источник/обновятся данные


    curl_handler_ = std::make_unique<CurlHandler>();
//    db_handler_ = std::make_unique<DataBaseHandler>();

}

bool Forecaster::startProgram()
{
//    getForecastsFromRBK();
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

    logPage();//1

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

        rbk_forekast_data_.emplace("forecast_date", html.find(".q-item__review__date_big").nodeAt(i).text()); //дата прогноза

        CNode node = select.nodeAt(i);
        rbk_forekast_data_.emplace("sum", node.find(".q-item__review__sum").nodeAt(0).text()); //прогноз стоимость
        rbk_forekast_data_.emplace("change", node.find(".q-item__review__change").nodeAt(0).text()); //изменение прогноза? или что
        rbk_forekast_data_.emplace("to_date", node.find(".q-item__review__value").nodeAt(1).text()); //к дате
        rbk_forekast_data_.emplace("forecaster", node.find(".q-item__review__value").nodeAt(2).text()); //прогнозист
        rbk_forekast_data_.emplace("accuracy", node.find(".q-item__review__value").nodeAt(3).text()); //точность
    }


    return true;
}


bool Forecaster::getForecastsFromRmbr()
{
    curl_handler_->setHeader("Host", "finance.rambler.ru");
    curl_handler_->setHeader("Referer", "https://www.yandex.ru/");

    const std::string url_rmb{"https://finance.rambler.ru/currencies/consensus"};

    curl_handler_->query(url_rmb, methodType::GET);

    logPage();//2

    CDocument html;
    html.parse(curl_handler_->getResponse());
    CSelection select = html.find(".finance__forecast");

//    qDebug()<< QString::fromStdString(select.nodeAt(0).text());
    saveDocument(path + "page_data",select.nodeAt(0).text());

//    json jsonData = json::parse(curl_handler_->getResponse().data());

//    jsonData = jsonData["forecaster"];

//    qDebug()<<QString::fromStdString(jsonData["char_code"].get<std::string>());

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














