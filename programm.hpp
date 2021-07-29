#ifndef PROGRAMM_HPP
#define PROGRAMM_HPP

#endif // PROGRAMM_HPP

#include <string>
#include <fstream>
#include <QDebug>

using namespace std;

static const std::string path {"/home/chaginsergey/Qt Projects/pages/"};

namespace Programm
{

typedef struct ForecastData
{
    std::string Parser_;
    std::string value_;
    std::string forecast_date_;
    std::string period_;
    std::string accuracy_{"null"};
    std::string value_review_{"null"};

}ForecastData;

    const string loadDocument(const string& file_name);
    bool saveDocument(const std::string& filename, const std::string& data);
    const std::string parseDataFromPage(const std::string& where, const std::string& lstr, const std::string& rstr, bool with_left = false);
    void normalizeString(std::string& where, const std::string& what);
    std::string normalizeString(std::string where);

}
