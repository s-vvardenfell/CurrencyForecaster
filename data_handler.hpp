#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include <QObject>

#include "Document.h"
#include "Node.h"
#include "Selection.h"

#include "gumbo.h"

class data_handler : public QObject
{
    Q_OBJECT
public:
    explicit data_handler(QObject *parent = nullptr);

signals:

};

#endif // DATA_HANDLER_H
