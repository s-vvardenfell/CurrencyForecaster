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

    Connections
    {
        target: Account
//        onSendUNameToQmlForHeaderSignl: page3.title = text;
    }

    GridLayout
    {
        id: grid
        anchors.fill: parent

        ColumnLayout
        {

            Layout.fillWidth: true
            Layout.fillHeight: true

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
                Button
                {
                    id: buySell
                    text: "Sell $";
                    Layout.fillWidth: true

                    onPressed:
                    {
                        Account.sell(spinboxSell.value);
                        spinboxSell.value = 0.0
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

//            ListView
            ColumnLayout
            {
                id: listView
                spacing: 2

                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.alignment: Qt.AlignTop

//https://github.com/s-vvardenfell/Diary-Calendar/blob/master/WorkPage.qml
//                verticalLayoutDirection: ListView.BottomToTop
//                spacing: 12
//                ScrollBar.vertical: ScrollBar {}
//                model: m_model

                Label
                {
                    text: "some purchase1"
                    Layout.fillWidth: true
                    background: Rectangle
                    {
                        border.color:  "#2b5278"
                        radius: 2
                        border.width: 2
                    }
                }

                Label
                {
                    text: "some purchase2"
                    Layout.fillWidth: true
                    background: Rectangle
                    {
                        border.color:  "#2b5278"
                        radius: 2
                        border.width: 2
                    }
                }

                Label
                {
                    text: "some purchase3"
                    Layout.fillWidth: true
                    background: Rectangle
                    {
                        border.color:  "#2b5278"
                        radius: 2
                        border.width: 2
                    }
                }
            }

        }

        ColumnLayout
        {
            Layout.fillWidth: true
            Layout.fillHeight: true

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

            Label
            {
                text: "Forecasts";
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


    }

}
