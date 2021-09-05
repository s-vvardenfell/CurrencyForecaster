import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

//import PurchaseTableModel 0.1
import SortFilterProxyModel 0.1


    ApplicationWindow {
        id: window
        width: 1024
        height: 740
        visible: true
        title: "TV TEST"

        toolBar: ToolBar {
            TextField {
                id: searchBox

                placeholderText: "Search..."
                inputMethodHints: Qt.ImhNoPredictiveText

                width: window.width / 5 * 2
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        TableView {
            id: tableView

//            frameVisible: false
//            sortIndicatorVisible: true

            anchors.fill: parent

            Layout.minimumWidth: 400
            Layout.minimumHeight: 240
            Layout.preferredWidth: 600
            Layout.preferredHeight: 400



            TableViewColumn {
                id: dateColumn
                title: "Date"
                role: "date"
                movable: false
                resizable: false
                width: tableView.viewport.width / 7
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
                width: tableView.viewport.width / 7
            }

            TableViewColumn {
                id: sumColumn
                title: "Sum"
                role: "sum"
                movable: false
                resizable: false
                width: tableView.viewport.width / 7
            }

            TableViewColumn {
                id: accountColumn
                title: "Account"
                role: "account"
                movable: false
                resizable: false
                width: tableView.viewport.width / 7
            }

            TableViewColumn {
                id: bankColumn
                title: "Bank"
                role: "bank_name"
                movable: false
                resizable: false
                width: tableView.viewport.width / 7
            }

            model: SortFilterProxyModel {
                id: proxyModel
//                source: sourceModel.columnCount() > 0 ? sourceModel : null
                source: ptmodel
                sortOrder: tableView.sortIndicatorOrder
                sortCaseSensitivity: Qt.CaseInsensitive
                sortRole: sourceModel.columnCount() > 0 ?
                              tableView.getColumn(tableView.sortIndicatorColumn).role : ""

                filterString: "*" + searchBox.text + "*"
                filterSyntax: SortFilterProxyModel.Wildcard
                filterCaseSensitivity: Qt.CaseInsensitive
            }

//            PurchaseTableModel{
//                id: sourceModel
//            }
        }
    }

