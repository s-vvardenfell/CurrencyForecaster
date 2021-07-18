#ifndef DB_HANDLER_H
#define DB_HANDLER_H

#include <QObject>



//убрать QObject или понадобится для работы с бд?
class DataBaseHandler : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseHandler(QObject *parent = nullptr);

signals:

};

#endif // DB_HANDLER_H
