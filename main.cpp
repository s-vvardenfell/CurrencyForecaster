#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "db_handler.hpp"
#include "account_handler.hpp"

//TODO
//добавить исключения
//добавить в rambler и рбк проверку вдруг появится новый источник/обновятся данные

//там где week year month пересчитать в рельные даты мб? будет единообразно с рбк

//парсить тарифы того банка где буду менять
    //альфа/тинькоф/газпромбанк(!)
//логин в лк альфы? или тиньков? мб александровкий - лучше тариф чем в альфе /газпромбанк

//CurlHandler стоит прокси не на локалхост

//хранение копеек/центов в дробной части мб плохой идеей, мб нужна структура доллар

//curl handler мб стоит таки переделать метод query на post и get

//возможно получение курса обмена придется перенести в account manager
    //тк parser занимается только открытыми данными

//дб либо 2 разные таблицы на покупку-продажу
    //либо нужен стоблец "тип процедуры" иначе непонятно покупал или продавал!
//обрезать хранение в таблице до 2-3 знаков после запятой


//вывод баланса в гуи?
//вывод операций в гуи - отельная вкладка

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
