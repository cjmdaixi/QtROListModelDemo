import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ListView{
        id: addressBookListView
        model: addressBookModel
        anchors.fill: parent
        highlight: Rectangle {
            color: "#FFFF88"
        }
        highlightMoveDuration: 200
        delegate: Item{
            id: delegateItemRoot
            width: addressBookListView.width
            height: 100
            GridLayout{
                anchors{fill: parent; margins: 5; topMargin: 10; bottomMargin: 10}
                columns: 2
                Label{
                    id: nameLabel
                    text: name
                    font{pointSize: 15; bold: true}
                    Layout.columnSpan: 2
                }
                RowLayout{
                    Label{text: "Seniority:"}
                    Label{
                        id: seniorityLabel
                        text: seniority
                    }
                }
                RowLayout{
                    Label{text: "Title:"}
                    Label{
                        id: titleLabel
                        text: title
                    }
                }
                RowLayout{
                    Label{text: "Address:"}
                    Label{
                        id: addressLabel
                        text: address
                    }
                    Layout.columnSpan: 2
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    addressBookListView.currentIndex = index;
                }
            }
        }// delegate
    }// ListView
}
