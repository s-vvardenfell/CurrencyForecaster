import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.12


/*
окно покупки - кнопка, ввод кол-ва - мб отдельный список как в ежедневнике
    кнопка продажи - на конкретном лоте
кнопка продать всё - с предварительным расчетом в новом окне
отображение имеющихся лотов с ценами и тд
отображение текущего курса
отображение прогнозов
вывод ошибок


*/



Window {
    width: 840
    height: 480
    visible: true
    title: qsTr("Currency Manager")

//    Connections
//    {
//        target: Account
//    }

    GridLayout
    {
        id: grid
        anchors.fill: parent

        ColumnLayout
        {

//            Layout.fillWidth: true
//            Layout.fillHeight: true

            Layout.maximumWidth: parent.width * 0.5
            Layout.maximumHeight: parent.height * 0.3

            Layout.minimumWidth: parent.width * 0.5
            Layout.minimumHeight: parent.height * 0.3

            Layout.alignment: Qt.AlignTop

            id: buyWgt

            RowLayout
            {
                Layout.fillWidth: true
                Layout.fillHeight: true

                Button
                {
                    id: buyBtn
                    text: "Buy $";
                    Layout.fillWidth: true

                    onPressed:
                    {
                        Account.buy(spinboxBuy.value);
                        spinboxBuy.value = 0.0
                        accBalLbl.text = Account.getBankAccountBalanceFromSite();
                        dbBalLbl.text = Account.getBankAccountBalanceFromDB();
                    }
                }

                SpinBox
                {
                    id: spinboxBuy
                    Layout.fillWidth: true
                }

            }

            RowLayout
            {
                Layout.fillWidth: true
                Layout.fillHeight: true

                Button
                {
                    id: buySell
                    text: "Sell $";
                    Layout.fillWidth: true

                    onPressed:
                    {
                        Account.sell(spinboxSell.value);
                        spinboxSell.value = 0.0
                        accBalLbl.text = Account.getBankAccountBalanceFromSite();
                        dbBalLbl.text = Account.getBankAccountBalanceFromDB();
                    }
                }

                SpinBox
                {
                    id: spinboxSell
                    Layout.fillWidth: true
                }
            }

            Button
            {
                id: sellAll
                text: "Sell all $";
                Layout.fillWidth: true

                onPressed:
                {
                    Account.sellAll();
                    spinboxBuy.value = 0.0
                    spinboxSell.value = 0.0
                    accBalLbl.text = Account.getBankAccountBalanceFromSite();
                    dbBalLbl.text = Account.getBankAccountBalanceFromDB();
                }
            }

            Label
            {
                Layout.alignment: Qt.AlignCenter
                id: lblLV
//                horizontalAlignment: Text.AlignHCenter
                text: qsTr("Purchases: ")
                //у каждой Purchase должны выводиться данные из бд

            }

            ListView
            {
                width: 100; height: 200
                model : mmodel

                spacing: 3

                delegate: Text
                {
                    required property string id
                    required property string date
                    required property string ptype
                    required property string amount
                    required property string price
                    required property string sum

                    text: "Purchase: " + id + ", " + date + ", " + ptype
                        + ", " + amount + ", " + price + ", " + sum
                }
            }

        }

        ColumnLayout
        {
            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout
            {
//                Layout.fillWidth: true
//                Layout.fillHeight: true
                Layout.maximumWidth: parent.width
                Layout.maximumHeight : parent.height * 0.2

                Label
                {
                    id: accBalLbl
                    text: "Account balance: \n" + Account.getBankAccountBalanceFromSite();
                    font.bold: true;

                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    background: Rectangle
                    {
                        border.color:  "#2b5278"
                        radius: 2
                        border.width: 2
                    }
                }

                Label
                {
                    id: dbBalLbl
                    text: "Database balance: \n"+ Account.getBankAccountBalanceFromDB();
                    font.bold: true;

                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    background: Rectangle
                    {
                        border.color:  "#2b5278"
                        radius: 2
                        border.width: 2
                    }
                }
            }



            Label
            {
                text: "Actual Currency";
                font.bold: true;
                Layout.fillWidth: true
                Layout.fillHeight: true
                background: Rectangle
                {
                    border.color:  "#2b5278"
                    radius: 2
                    border.width: 2
                }
            }

            RowLayout
            {
                Layout.fillWidth: true
                Layout.fillHeight: true

                id: rowParsedData
//                Layout.maximumWidth: parent.width
                Layout.maximumHeight : parent.height * 0.4 //работает

                Frame
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    background: Rectangle
                    {
                        border.color:  "#2b5278"
                        radius: 2
                        border.width: 2
                    }

                    Column
                    {
                        Label
                        {
                            text: "Rambler";
                        }

                        Label
                        {
                            text: "data";
                        }
                    }

                }

                Frame
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    background: Rectangle
                    {
                        border.color:  "#2b5278"
                        radius: 2
                        border.width: 2
                    }

                    Column
                    {
                        Label
                        {
                            text: "RBK";
                        }

                        Label
                        {
//                            text: Account..
                        }
                    }
                }
            }



        }


    }

}
