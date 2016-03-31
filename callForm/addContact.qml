import QtQuick 2.6
import Qt.labs.controls.material 1.0
import QtQuick.Layouts 1.3
import Qt.labs.controls 1.0
import Qt.labs.settings 1.0

Pane {
    id: pane

    Column {
        spacing: 40
        anchors.fill: parent
        anchors.topMargin: 50
        TextField {
            id: nameField
            placeholderText: "Имя"
            width: pane.width * 0.6
            anchors.horizontalCenter: parent.horizontalCenter
        }
        TextField {
            id: snameField
            placeholderText: "Фамилия"
            width: pane.width * 0.6
            anchors.horizontalCenter: parent.horizontalCenter
        }
        TextField {
            id: phoneField
            placeholderText: "+71234567890"
            width: pane.width * 0.6
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: saveBtn
            text: "Save"
            anchors.bottom: pane.bottom;
            anchors.horizontalCenter: parent.horizontalCenter
            width: pane.width * 0.9
            onClicked: {
                    //callMain.addContact()
                    if(phoneField.text.length != 0 && (nameField.text.length != 0 || snameField.text.length != 0))
                        callMain.addContact(nameField.text, snameField.text, phoneField.text)
                    else
                        console.log("Empty");
            }
        }
    }
}
