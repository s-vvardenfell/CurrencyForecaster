//import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.12

import PurchaseTableModel 0.1
import SortFilterProxyModel 0.1

//import QtQuick.Window 2.15
//import QtQuick.Layouts 1.1
//import QtQuick.Controls 1.2

//TODO
/*
  Сделать дефолтный margin, spacing, radius
  нужен не только баланс $ реальный и в бд но и баланс рублевый!
    мб с отображением счета, т.е. нужен Label на всю ширину второго ColumnLayout
  */
Window
{
    width: 1024
    height: 740
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

            Item {//мб не нужен уже
                Layout.minimumHeight: rlayout.height / 20
            }


            ToolBar {

                Layout.fillWidth: true

                TextField {
                    id: searchBox

                    placeholderText: "Search..."
                    inputMethodHints: Qt.ImhNoPredictiveText

                    width: rlayout.width / 5
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            TableView {
                id: tableView

                Layout.fillWidth: true
                Layout.fillHeight: true

//                Layout.fillWidth: true
//                Layout.maximumHeight: rlayout.height / 3
////                frameVisible: false
////                sortIndicatorVisible: true

//                Layout.minimumWidth: 400
//                Layout.minimumHeight: 240
//                Layout.preferredWidth: 600
//                Layout.preferredHeight: 400

                TableViewColumn {
                    id: dateColumn
                    title: "Date"
                    role: "date"
                    movable: false
                    resizable: false
                    width: tableView.width / 2
                }

                TableViewColumn {
                    id: ptypeColumn
                    title: "Type"
                    role: "ptype"
                    movable: false
                    resizable: false
                    width: tableView.width / 2
                }

                model: SortFilterProxyModel {
                    id: proxyModel
    //                source: sourceModel.count > 0 ? sourceModel : null
                    source: sourceModel.columnCount() > 0 ? sourceModel : null
                    sortOrder: tableView.sortIndicatorOrder
                    sortCaseSensitivity: Qt.CaseInsensitive
                    sortRole: sourceModel.columnCount() > 0 ?
                                  tableView.getColumn(tableView.sortIndicatorColumn).role : ""

                    filterString: "*" + searchBox.text + "*"
                    filterSyntax: SortFilterProxyModel.Wildcard
                    filterCaseSensitivity: Qt.CaseInsensitive
                }

                PurchaseTableModel{
                    id: sourceModel
                }

            }

//            ListView
//            {
//                id: lv
//                model : pmodel
//                spacing: 6

//                Layout.fillWidth: true
//                Layout.fillHeight: true

////                ScrollBar.vertical: ScrollBar {}

//                delegate: Rectangle
//                {
//                    height: lv.height / 5
//                    width: lv.width

//                    border.color:  "black"
//                    radius: 5
//                    border.width: 2
////                    color: "red"

//                    required property string date
//                    required property string ptype
//                    required property double amount
//                    required property double price
//                    required property double sum
//                    required property string bank_name
//                    required property string account

////                    Button
////                    {
////                        anchors.centerIn: parent
////                    }

//                    Text
//                    {
//                        anchors.fill: parent
//                        text: qsTr(date + ", " + ptype + ", " + parseInt(amount) + ", " + parseFloat(sum))
//                    }

//                }

//            }


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

                    Label
                    {

                        Layout.fillWidth: true
                        Layout.fillHeight: true

                        Text
                        {//надпись вылезает если уменьшить размер сильно - перенос текста сделать
                            id: realblncTxtRub
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
                            id: virtblncTxtRub
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


//            Rectangle
//            {
//                color: 'lightgrey'
//                Layout.fillWidth: true
//                Layout.fillHeight: true


//                Text
//                {
//                    anchors.centerIn: parent
//                    text: "Reserved place - current margin calculation and so"
//                }
//            }

            ListView
            {
                id: lv2
                model : cmodel
                spacing: 6

                Layout.fillWidth: true
                Layout.fillHeight: true

//                ScrollBar.vertical: ScrollBar {}

                delegate: Rectangle
                {
                    height: lv2.height / 5
                    width: lv2.width

                    border.color:  "black"
                    radius: 5
                    border.width: 2
//                    color: "red"

                    required property string currency
                    required property string change
                    required property string cost

//                    Button
//                    {
//                        anchors.centerIn: parent
//                    }

                    Text
                    {
                        anchors.fill: parent
                        text: qsTr(currency + ", " + change + ", " + cost)
                    }

                }

            }


        }


        }

    }


