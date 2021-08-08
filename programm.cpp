#include "programm.hpp"

namespace Programm
{
    static const std::string path {"/home/chaginsergey/Downloads/"};

    const string loadDocument(const string& file_name)
    {
        ifstream ifile;
        ifile.open(path + file_name);

        if(!ifile)
        {
            qDebug() <<"Cannot open file: "<<file_name.c_str()<<Qt::endl;
            return "";
        }


        string doc, line;

        while(getline(ifile, line))
            doc+=line;

        return doc;
    }

    bool saveDocument(const std::string& filename, const std::string& data)
    {
        std::ofstream ofile(path + filename);
        if (!ofile) { qDebug() << "Cannot open file"<<Qt::endl; return false; }
        ofile << data;
        ofile.close();
        return true;

    }

    const std::string parseDataFromPage(const std::string& where, const std::string& lstr, const std::string& rstr, bool with_left)
    {
        size_t lpos{}, rpos{};
        std::string ret_val;

        if ((where.find(lstr) == std::string::npos) || (where.find(rstr) == std::string::npos))
        {
            qDebug()<<"No data to parse\n"<<Qt::endl;
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



    void normalizeString(std::string& where, const std::string& what)
    {
        size_t to_remove{};

        while((to_remove = where.find(what)) != std::string::npos)
            where.erase(to_remove, 1);

    }

    std::string normalizeString(std::string where)
    {
        size_t to_remove{};

        while((to_remove = where.find('\t')) != std::string::npos) {where.erase(to_remove, 1);}
        while((to_remove = where.find('\r')) != std::string::npos) {where.erase(to_remove, 1);}
        while((to_remove = where.find('\n')) != std::string::npos) {where.erase(to_remove, 1);}
        while((to_remove = where.find(' ')) != std::string::npos) {where.erase(to_remove, 1);}

        return where;
    }
}
