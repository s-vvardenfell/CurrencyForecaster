#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <QObject>




class DataBaseHandler : public QObject
{
    Q_OBJECT
public:
    explicit DataBaseHandler(QObject *parent = nullptr);

signals:

};

#endif // DATA_HANDLER_H
