import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.4

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("QtRO ListModel Demo Source")

    RowLayout{
        anchors{fill: parent; margins: 10}

        ListView{
            id: addressBookListView
            model: addressBookModel
            Layout.fillHeight: true
            Layout.fillWidth: true
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

        ColumnLayout{
            Button{
                text: "Examples"
                onClicked: {
                    addressBookModel.addTestData();
                }
            }

            Button{
                text: "Add"
                onClicked: {
                    dialog.showAdd("Add address");
                }
            }
            Button{
                text: "Delete"
                onClicked: {
                    addressBookModel.remove(addressBookListView.currentIndex);
                }
            }
            Button{
                text: "Modify"
                onClicked: {
                    dialog.showModify("Modify address", addressBookListView.currentIndex);
                }
            }
            Item{
                Layout.fillHeight: true
            }
        }
    }

    Dialog{
        id: dialog

        standardButtons: Dialog.Ok | Dialog.Cancel
        closePolicy: Popup.NoAutoClose
        modal: true
        property int modifyIdx: -1
        onAccepted:{
            if(modifyIdx == -1){
                addressBookModel.append(nameTextField.text,
                                        senioritySpinBox.value,
                                        titleComboBox.currentText,
                                        addressTextField.text);
            }else{
                addressBookModel.modify(modifyIdx,
                                        nameTextField.text,
                                        senioritySpinBox.value,
                                        titleComboBox.currentText,
                                        addressTextField.text);
            }
        }

        function showModify(dialogTitle, idx){
            title = dialogTitle;
            modifyIdx = idx;
            var addressData = addressBookModel.item(idx);
            nameTextField.text = addressData.name;
            senioritySpinBox.value = addressData.seniority;
            titleComboBox.currentIndex = titleComboBox.find(addressData.title);
            addressTextField.text = addressData.address;

            dialog.open();
        }

        function showAdd(dialogTitle){
            title = dialogTitle;
            modifyIdx = -1;
            nameTextField.text = "";
            senioritySpinBox.value = 0;
            titleComboBox.currentIndex = 0;
            addressTextField.text = "";

            dialog.open();
        }

        x: window.width / 2 - width / 2
        y: window.height / 2 - height / 2
        GridLayout{
            columns: 2
            Label{text: "Name:"}
            TextField{
                id: nameTextField
                placeholderText: "Input the name..."
            }
            Label{text: "Seniority:"}
            SpinBox{
                id: senioritySpinBox
                from: 0
                to: 99
                stepSize: 1
            }
            Label{text: "Title:"}
            ComboBox{
                id: titleComboBox
                model: [
                    "Software engineer",
                    "Senior software engineer",
                    "Test engineer",
                    "Department manager"
                ]
                Layout.fillWidth: true
            }
            Label{text: "Address:"}
            TextField{
                id: addressTextField
                placeholderText: "Input the address..."
            }
        }
    }
}
