#include "account_handler.hpp"

AccountHandler::AccountHandler() : curl_handler_(nullptr)
{
    curl_handler_ = std::make_unique<CurlHandler>();
}

bool AccountHandler::authorize()
{
    return true;
}

bool AccountHandler::buy(size_t amount)
{
    qDebug() << "Bought "<<amount<<" dollars";
    return true;
}

bool AccountHandler::sell(size_t amount)
{
    qDebug() << "Sold "<<amount<<" dollars";
    return true;
}

bool AccountHandler::sellAll()
{
    qDebug() << "Sold out";
    return true;
}
