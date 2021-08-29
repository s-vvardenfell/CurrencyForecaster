
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.12
import QtQuick 2.12

import QtQuick 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2

import SortFilterProxyModel 1.1

ApplicationWindow
{
    width: 840
    height: 480
    visible: true
    title: qsTr("Currency Manager")
    id: window

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


    TableView
    {
        id: tableView

        frameVisible: false
        sortIndicatorVisible: true

        anchors.fill: parent

        Layout.minimumWidth: 400
        Layout.minimumHeight: 240
        Layout.preferredWidth: 600
        Layout.preferredHeight: 400

        TableViewColumn {
            id: titleColumn
            title: "Title"
            role: "title"
            movable: false
            resizable: false
            width: tableView.viewport.width /3
        }


        TableViewColumn {
            id: authorColumn
            title: "Author"
            role: "author"
            movable: false
            resizable: false
            width: tableView.viewport.width / 3
        }

        TableViewColumn {
            id: dateColumn
            title: "Date"
            role: "date"
            movable: false
            resizable: false
            width: tableView.viewport.width / 3
//            width: tableView.viewport.width - authorColumn.width
        }

        model: SortFilterProxyModel {
            id: proxyModel
            source: sourceModel.count > 0 ? sourceModel : null

            sortOrder: tableView.sortIndicatorOrder
            sortCaseSensitivity: Qt.CaseInsensitive
            sortRole: sourceModel.count > 0 ? tableView.getColumn(tableView.sortIndicatorColumn).role : ""

            filterString: "*" + searchBox.text + "*"
            filterSyntax: SortFilterProxyModel.Wildcard
            filterCaseSensitivity: Qt.CaseInsensitive
        }

        ListModel {
            id: sourceModel
            ListElement {
                title: "Moby-Dick"
                author: "Herman Melville"

            }
            ListElement {
                title: "The Adventures of Tom Sawyer"
                author: "Mark Twain"

            }
            ListElement {
                title: "Cat’s Cradle"
                author: "Kurt Vonnegut"

            }
            ListElement {
                title: "Herbert West—Reanimator"
                author: "H. P. Lovecraft"

            }
        }
    }

}
