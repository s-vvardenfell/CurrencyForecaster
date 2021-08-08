#ifndef ACCOUNTHANDLER_HPP
#define ACCOUNTHANDLER_HPP


class AccountHandler
{
public:
    AccountHandler();

    bool authorize();
    bool buy();
    bool sell();
    bool sellAll();
};

#endif // ACCOUNTHANDLER_HPP
