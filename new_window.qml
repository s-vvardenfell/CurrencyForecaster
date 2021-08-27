import QtQuick 2.0

import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.12

Window
{
    width: 840
    height: 480
    visible: true
    title: qsTr("Currency Manager")

    RowLayout
    {
        id: rlayout
        anchors.fill: parent
        spacing: 6

        ColumnLayout
        {
            id: clmn1
            spacing: 6

            RowLayout
            {
                Layout.maximumHeight: rlayout.height / 8

                Button
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Text {
                        anchors.centerIn: parent
                        text: "BUY"
                    }

                    onPressed:
                    {
                        Account.buy(spinboxBuy.value);
                        spinboxBuy.value = 0.0
                        realblncTxt.text = Account.getBankAccountBalanceFromSite();
                        virtblncTxt.text = Account.getBankAccountBalanceFromDB();
                    }
                }

                SpinBox
                {
                    id: spinboxBuy
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Text {
                        anchors.centerIn: parent
                    }
                }

            }

            RowLayout
            {
                Layout.maximumHeight: rlayout.height / 8

                Button
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Text {
                        anchors.centerIn: parent
                        text: "SELL"
                    }

                    onPressed:
                    {
                        Account.sell(spinboxSell.value);
                        spinboxSell.value = 0.0
                        realblncTxt.text = Account.getBankAccountBalanceFromSite();
                        virtblncTxt.text = Account.getBankAccountBalanceFromDB();
                    }
                }

                SpinBox
                {
                    id: spinboxSell
                    Layout.fillWidth: true
                    Layout.fillHeight: true


                    Text {
                        anchors.centerIn: parent
                    }
                }

            }

            RowLayout
            {
                Layout.maximumHeight: rlayout.height / 8

                Button
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Text {
                        anchors.centerIn: parent
                        text: "SELL ALL"
                    }

                    onPressed:
                    {
                        Account.sellAll();
                        spinboxBuy.value = 0.0
                        spinboxSell.value = 0.0
                        realblncTxt.text = Account.getBankAccountBalanceFromSite();
                        virtblncTxt.text = Account.getBankAccountBalanceFromDB();
                    }
                }

                Button
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Text {
                        anchors.centerIn: parent
                        text: "BUY ALL"
                    }
                }

                Button
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Text {
                        anchors.centerIn: parent
                        text: "Reload data"
                    }
                }

            }

            Item {
                Layout.minimumHeight: rlayout.height / 25
                Layout.alignment: Qt.AlignLeft

                Text { //выровнять

                    text: "Дата | Тип | Количество | Цена | Сумма | Банк | Счет"
                }
            }

            Item {
                Layout.minimumHeight: rlayout.height / 40
            }


            ListView
            {
                id: lv
                model : pmodel
                spacing: 10

                Layout.fillWidth: true
                Layout.fillHeight: true

//                ScrollBar.vertical: ScrollBar {}

                delegate: Item
                {
                    id: delegate
                    Layout.fillWidth: true
                    height: rlayout.height / 20

                    required property string date
                    required property string ptype
                    required property double amount
                    required property double price
                    required property double sum
                    required property string bank_name
                    required property string account



//                    Text
//                    {
////                            width: lv.width
////                        anchors.fill: parent
////                        anchors.centerIn: parent
//                        font.pixelSize: 20

//                        id: name
//                        text: qsTr(date + ", " + ptype + ", " + parseInt(amount) +
//                                   ", " + parseFloat(price) + ", " + parseFloat(sum))


//                    }

                    Button
                    {
                        Layout.alignment: Qt.AlignRight
                    }

                    Rectangle
                    {
                        Layout.alignment: Qt.AlignCenter

                        border.color:  "black"
                        radius: 2
                        border.width: 10
                        color: "red"
                    }

                }





            }


        }


        ColumnLayout
        {
            id: clmn2
            spacing: 6

            Layout.maximumWidth: rlayout.width * 0.5
            Layout.minimumWidth: rlayout.width * 0.5

            RowLayout
            {
                Layout.maximumHeight: clmn2.height / 4

                ColumnLayout
                {
                    Label
                    {

                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        Text
                        {//надпись вылезает если уменьшить размер сильно - перенос текста сделать
                            id: realblncTxt
                            anchors.centerIn: parent
                            text: Account.getBankAccountBalanceFromSite()
                        }

                        background: Rectangle
                        {
                            border.color:  "#2b5278"
                            radius: 2
                            border.width: 2
                        }
                    }


                    Label
                    {
                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        Text
                        {//надпись вылезает если уменьшить размер сильно - перенос текста сделать
                            id: virtblncTxt
                            anchors.centerIn: parent
                            text: Account.getBankAccountBalanceFromDB()
                        }

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
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Text
                    {
                        anchors.centerIn: parent
                        text: parseFloat(Account.getExcangeRate())
                    }
                }

            }

            Label
            {
                Layout.minimumHeight: clmn2.height / 4
                Layout.minimumWidth: clmn2.width

                Text
                {
                    anchors.centerIn: parent
                    text: "Predictions and forecasts"
                }

                background: Rectangle
                {
                    border.color:  "#2b5278"
                    radius: 2
                    border.width: 2
                }
            }


            Rectangle
            {
                color: 'lightgrey'
                Layout.fillWidth: true
                Layout.fillHeight: true


                Text
                {
                    anchors.centerIn: parent
                    text: "Reserved place"
                }
            }


        }

    }

}
