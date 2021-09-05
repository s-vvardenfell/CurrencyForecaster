#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>
#include <QtQuick/qquickview.h>

#include "account_handler.hpp"
#include "purchase_object.hpp"
#include "currency_exchange_data_object.hpp"
#include "purchase_tablemodel.hpp"

#include "sortfilterproxymodel.hpp"
#include "purchase_tablemodel.hpp"

//TODO
//добавить исключения
//добавить в rambler и рбк проверку вдруг появится новый источник/обновятся данные

//нельзя продать если баланс 0!

//CurlHandler стоит прокси не на локалхост
//хранение копеек/центов в дробной части мб плохой идеей, мб нужна структура доллар
//curl handler мб стоит таки переделать метод query на post и get

//виджеты прогнозов и текущего курса
    //сделать через бд! + можно будет потом строить графики

//getActualPurchases добавить условие не проданные лоты, т.е. сначала добавить колонку в таблицу

//сделать правильную структуру: Account не должен создавать CurlHandler, но должен Parser мб

//ф-ии buyAll в Account и reloadData в QML

//tableView для списка операций
    //убрать старый listView

//убрать в бд адреса и тд сайтов которые я парсирую, тянуть их из бд / настроек
//сделать tv рабочий

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    try
    {
        QGuiApplication app(argc, argv);

        QQmlApplicationEngine engine;
//        const QUrl url(QStringLiteral("qrc:/new_window.qml"));
        const QUrl url(QStringLiteral("qrc:/tv_test2.qml"));
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                         &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);


        AccountHandler acc;
//        engine.rootContext()->setContextProperty("Account", &acc);


//        //список операций
//        PurchaseModel pmodel;
//        std::vector<Purchase> lots{ acc.getActiveLots() };
//        for(const auto& lot : lots)
//        {
//            pmodel.addPurchase(PurchaseObject(lot));
//        }
//        engine.rootContext()->setContextProperty("pmodel", &pmodel);


//        //список курсов валют
//        CurrencyExchangeDataObjectModel cmodel;
//        std::vector<CurrencyExchangeData> currencies { acc.getExcangeRates() };
//        for(const auto& rate : currencies)
//        {
//            cmodel.addCurrencyExchangeDataObject(CurrencyExchangeDataObject(rate));
//        }
//        engine.rootContext()->setContextProperty("cmodel", &cmodel);

        //список операций
        PurchaseTableModel ptmodel;
        std::vector<Purchase> lots{ acc.getActiveLots() };
        for(const auto& lot : lots)
        {
            ptmodel.addPurchase(PurchaseObject(lot));
        }
        engine.rootContext()->setContextProperty("ptmodel", &ptmodel);


        //исп мб этот тип для модели ListView тоже
        qmlRegisterType<SortFilterProxyModel>("SortFilterProxyModel", 0, 1, "SortFilterProxyModel");
//        qmlRegisterType<PurchaseTableModel>("PurchaseTableModel", 0, 1, "PurchaseTableModel");


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
