import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2
import QtQuick.Controls 2.12

import SortFilterProxyModel 0.1


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
        spacing: 10

        ColumnLayout
        {
            id: clmn1

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: rlayout.width * 0.4

            TableView
            {
                id: balanceTV
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.maximumHeight: clmn1.height / 3

                model: bmodel

                TableViewColumn {
//                    id: dateColumn
                    title: "Date"
                    role: "date"
                    movable: false
                    resizable: false
                    width: balanceTV.viewport.width / 2
                }

                TableViewColumn {
//                    id: ptypeColumn
                    title: "Balance"
                    role: "balance"
                    movable: false
                    resizable: false
                    width: balanceTV.viewport.width / 2
                }

            }

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
                    height: clmn1.height / 12
                    width: lv2.width

                    border.color:  "black"
                    radius: 5
                    border.width: 2

                    required property string currency
                    required property string change
                    required property string cost

                    RowLayout
                    {
                        anchors.margins: 20
                        anchors.fill: parent

                        Text {
                            id: cur
                            text: currency
                            Layout.alignment: Qt.AlignLeft
                        }

                        Text {
                            id: ch
                            text: change
                            Layout.alignment: Qt.AlignHCenter
                        }

                        Text {
                            id: cst
                            text: cost
                            Layout.alignment: Qt.AlignRight
                        }
                    }
                }

            }
        }

        ColumnLayout
        {
            id: clmn2

            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: rlayout.width * 0.6

            RowLayout
            {
                Layout.maximumHeight: clmn2.height / 15
                Layout.fillWidth: true

                Button
                {
                    id: buyBtn
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
                    }
                }

                SpinBox
                {
                    id: spinboxBuy
                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Text {
                        anchors.centerIn: parent
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

                    onPressed:
                    {
                        Account.sellAll();
                        spinboxBuy.value = 0.0
                        spinboxSell.value = 0.0
                    }
                }

            }

            RowLayout
            {
                Layout.maximumHeight: rlayout.height / 15

                Button
                {
                    id: sellBtn
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
                    }
                }

            }

            Rectangle
            {
                id: currencySelector
                Layout.fillWidth: true
                Layout.fillHeight: true

                ButtonGroup
                {
                    id: btnGr
                    buttons: rbGrid.children

                    onClicked:
                    {
                        Account.getSelectedCurrency(btnGr.checkedButton.text)
                    }
                }

                 Grid {
                    id: rbGrid

                     RadioButton {
                         id:usd
                         checked: true
                         text: qsTr("USDRUB")
                     }
                     RadioButton {
                         id:eur
                         text: qsTr("EURRUB")
                     }
                     RadioButton {
                         id:gbp
                         text: qsTr("GBPRUB")
                     }
                     RadioButton {
                         id:cny
                         text: qsTr("CNYRUB")
                     }
                     RadioButton {
                         id:jpy
                         text: qsTr("JPYRUB")
                     }
                     RadioButton {
                         id:hkd
                         text: qsTr("HKDRUB")
                     }
                     RadioButton {
                         id:tryy
                         text: qsTr("TRYRUB")
                     }


                 }

            }

            ToolBar
            {

             Layout.fillWidth: true

             Label{
                    text: "Operations"
                    anchors.margins: 20
                    anchors.left: parent.left
                    anchors.verticalCenter: parent.verticalCenter
                }

                TextField {
                    id: searchBox

                    placeholderText: "Search..."
                    inputMethodHints: Qt.ImhNoPredictiveText

                    width: clmn2.width / 2
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                }
            }

            TableView
            {
                id: tableView
                Layout.fillWidth: true
                Layout.fillHeight: true

                Layout.maximumHeight: clmn2.height / 1.5

                TableViewColumn {
                    id: dateColumn
                    title: "Date"
                    role: "date"
                    movable: false
                    resizable: false
                    width: tableView.viewport.width / 3
                }

                TableViewColumn {
                    id: ptypeColumn
                    title: "Type"
                    role: "ptype"
                    movable: false
                    resizable: false
                    width: tableView.viewport.width / 7
                }

                TableViewColumn {
                    id: amountColumn
                    title: "Amount"
                    role: "amount"
                    movable: false
                    resizable: false
                    width: tableView.viewport.width / 7
                }

                TableViewColumn {
                    id: priceColumn
                    title: "Price"
                    role: "price"
                    movable: false
                    resizable: false
                    width: tableView.viewport.width / 5
                }

                TableViewColumn {
                    id: sumColumn
                    title: "Sum"
                    role: "sum"
                    movable: false
                    resizable: false
                    width: tableView.viewport.width / 5
                }

//                TableViewColumn {
//                    id: accountColumn
//                    title: "Account"
//                    role: "account"
//                    movable: false
//                    resizable: false
//                    width: tableView.viewport.width / 7
//                }

//                TableViewColumn {
//                    id: bankColumn
//                    title: "Bank"
//                    role: "bank_name"
//                    movable: false
//                    resizable: false
//                    width: tableView.viewport.width / 7
//                }

                model: SortFilterProxyModel {
                    id: proxyModel
                    source: ptmodel.columnCount() > 0 ? ptmodel : null
                    sortOrder: tableView.sortIndicatorOrder
                    sortCaseSensitivity: Qt.CaseInsensitive
                    sortRole: sourceModel.columnCount() > 0 ?
                                  tableView.getColumn(tableView.sortIndicatorColumn).role : ""

                    filterString: "*" + searchBox.text + "*"
                    filterSyntax: SortFilterProxyModel.Wildcard
                    filterCaseSensitivity: Qt.CaseInsensitive
                }

            }

        }

    }
}
