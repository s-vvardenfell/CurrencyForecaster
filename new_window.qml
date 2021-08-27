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
                        text: "SELL"
                    }
                }

                SpinBox
                {
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
                        text: "BUY"
                    }
                }

                SpinBox
                {

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

            }

//GroupBox !!!!!!!!!!!!!!!!!!!!11
            Item { //чтобы itemDelegate не показывался поверх кнопок выше
                Layout.minimumHeight: rlayout.height / 30
            }


            ListView
            {
                model: 100

                Component {
                    id: itemDelegate
                    Text { text: "I am item number: " + index }
                }

                Layout.fillWidth: true
                Layout.fillHeight: true

                footer:Label{
                    anchors.centerIn: parent
                    text: "End"
                }

                delegate: itemDelegate

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

                Label
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Text
                    {//надпись вылезает если уменьшить размер сильно - перенос текста сделать
                        anchors.centerIn: parent
                        text: "Balance real and virtual"
                    }

//                    background: Rectangle
//                    {
//                        border.color:  "#2b5278"
//                        radius: 2
//                        border.width: 2
//                    }
                }

                Label
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Text
                    {
                        anchors.centerIn: parent
                        text: "Actual currency"
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
