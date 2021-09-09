#ifndef PROGRAMM_HPP
#define PROGRAMM_HPP

#endif // PROGRAMM_HPP

#include <string>
#include <fstream>
#include <iomanip>

#include <QDebug>

#include "exception.hpp"

using namespace std;

namespace Programm
{
    const string loadDocument(const string& file_name);
    bool saveDocument(const std::string& filename, const std::string& data);
    const std::string parseDataFromPage(const std::string& where, const std::string& lstr, const std::string& rstr, bool with_left);

    //TODO ARGS
    void normalizeString(std::string& where, const std::string& what);
    std::string normalizeString(std::string where);

    const std::string getDateTime();

    std::vector<std::string> readSettings(const std::string& file);
    const std::string getHostFromUrl(const std::string& file);
}
