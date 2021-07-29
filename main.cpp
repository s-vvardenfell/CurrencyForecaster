#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "db_handler.hpp"

//TODO
//добавить исключения
//добавить в rambler и рбк проверку вдруг появится новый источник/обновятся данные

//там где week year month пересчитать в рельные даты мб? будет единообразно с рбк

//парсить тарифы того банка где буду менять
    //альфа/тинькоф/газпромбанк(!)
//логин в лк альфы? или тиньков? мб александровкий - лучше тариф чем в альфе

//отдельный класс который работает с площадкой - логин, продажа-покупка AccountHandler

//не должно быть кучи try-catch в каждой функции! это бессмысленно

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    try
    {

        DataBaseHandler db;
        db.create_table();


        qDebug()<<"some text"<<endl;





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



    return app.exec();
}
