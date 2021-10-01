QT += quick

CONFIG += c++17
#CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        account_handler.cpp \
        curl_handler.cpp \
        currexcdata_object.cpp \
        currexcdata_object_model.cpp \
        db_handler.cpp \
        main.cpp \
        parser.cpp \
        purchase_object.cpp \
        purchase_tablemodel.cpp \
        sortfilterproxymodel.cpp \
        utility.cpp

HEADERS += \
        account_handler.hpp \
        curl_handler.hpp \
        currexcdata_object.hpp \
        currexcdata_object_model.hpp \
        db_handler.hpp \
        exception.hpp \
        parser.hpp \
        purchase_object.hpp \
        purchase_tablemodel.hpp \
        sortfilterproxymodel.hpp \
        utility.hpp


INCLUDEPATH += \
        usr/include/x86_64-linux-gnu/curl \
        usr/include/curl \
        usr/local/include \
        usr/local/include/gq/
        #works if Document.h and others is in usr/local/include or
        #need to point gq/Document.h

LIBS+= \
       -lcurl \
       -lgumbo \
       -lgq \
       -lmysqlcppconn



RESOURCES += \
        appwindow.qml

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    appwindow.qml


