#include "forecaster.hpp"

static const std::string path {"/home/chaginsergey/Qt Projects/pages"};

Forecaster::Forecaster(QObject *parent) : QObject(parent)
{
    //переименовать файлы классов curl и db handler
    //добавить исключения-файл-класс

    curl_handler_ = std::make_unique<CurlHandler>();
    db_handler_ = std::make_unique<DataBaseHandler>();
}

bool Forecaster::startProgram()
{
    getForecastFromRBK();

    return true;
}


bool Forecaster::getForecastFromRBK()
{
    const std::string url_rbk{"https://quote.rbc.ru/ticker/59111"};
    curl_handler_->query(url_rbk, methodType::GET);

    CDocument html;
    html.parse(curl_handler_->getResponse());

    CSelection purchases = html.find(".q-item__review__container");

    if (purchases.nodeNum() == 0)
        return false;
            //else
            //    cerr << purchases.nodeNum() << endl;

            //cerr<< purchases.nodeAt(1).text();

    for (std::size_t i = 0; i < purchases.nodeNum(); ++i)
    {

        rbk_forekast_data_.emplace("forecast_date", html.find(".q-item__review__date_big").nodeAt(i).text()); //дата прогноза

        CNode node = purchases.nodeAt(i);
        rbk_forekast_data_.emplace("sum", node.find(".q-item__review__sum").nodeAt(0).text()); //прогноз стоимость
        rbk_forekast_data_.emplace("change", node.find(".q-item__review__change").nodeAt(0).text()); //изменение прогноза? или что
        rbk_forekast_data_.emplace("to_date", node.find(".q-item__review__value").nodeAt(1).text()); //к дате
        rbk_forekast_data_.emplace("forecaster", node.find(".q-item__review__value").nodeAt(2).text()); //прогнозист
        rbk_forekast_data_.emplace("accuracy", node.find(".q-item__review__value").nodeAt(3).text()); //точность
    }


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
    static int page_counter{1};

    std::ofstream ofile;
    ofile.open(path + std::to_string(page_counter) + "_page_.xml");

    if (!data.empty())
        ofile << data << "\n\n";

    ofile << curl_handler_->getResponseHeaders() << "\n\n" << curl_handler_->getResponse();
    ofile.close();

    ++page_counter;
}














