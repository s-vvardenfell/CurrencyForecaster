#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>

#include "db_handler.hpp"
#include "account_handler.hpp"
#include "purchase_object.hpp"

//TODO
//добавить исключения
//добавить в rambler и рбк проверку вдруг появится новый источник/обновятся данные

//CurlHandler стоит прокси не на локалхост
//хранение копеек/центов в дробной части мб плохой идеей, мб нужна структура доллар
//curl handler мб стоит таки переделать метод query на post и get

//возможно получение курса обмена придется перенести в account manager
    //тк parser занимается только открытыми данными

//виджет лотов сделать - все покупки тянуть как с бд?
//виджеты прогнозов и текущего курса
    //сделать через бд! + можно будет потом строить графики


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    try
    {
        QGuiApplication app(argc, argv);

        QQmlApplicationEngine engine;
        const QUrl url(QStringLiteral("qrc:/main.qml"));
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                         &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);


        AccountHandler acc;
        engine.rootContext()->setContextProperty("Account", &acc);


        PurchaseModel pmodel;
        pmodel.addPurchase(PurchaseObject("Wolf", "Medium"));
        pmodel.addPurchase(PurchaseObject("Polar bear", "Large"));
//        pmodel.addPurchase(PurchaseObject("Quoll", "Small"));
//        pmodel.addPurchase(PurchaseObject("Quoll", "Small"));

        pmodel.addPurchase(PurchaseObject(Purchase{"123", "Medi2um", 45.45, 32.2, 21.3, "bank1", "acc"}));
        pmodel.addPurchase(PurchaseObject(Purchase{"1123", "Medi3um", 425.45, 312.2, 221.3,  "bank2", "acc"}));

        //вызвать метод getPurchases AccountHandler который вернет список Purchase
        //который ему отдаст db_handler
        //которым в цикле иниц-тся PurchaseModel

        engine.rootContext()->setContextProperty("pmodel", &pmodel);




        engine.load(url);
        return app.exec();

    }
    catch (sql::SQLException &e)
    {
        qDebug() << "# ERR: SQLException in " << __FILE__;
        qDebug() << "(" << __FUNCTION__ << ") on line "<< __LINE__ << Qt::endl;
        qDebug() << "# ERR: " << e.what();
        qDebug() << " (MySQL error code: " <<e.getErrorCode();
        qDebug() << ", SQLState: " << e.getSQLState().c_str() <<" )" << Qt::endl;
    }
    catch (std::exception& ex)
    {
        qDebug()<<ex.what()<<"\n";
    }


}
