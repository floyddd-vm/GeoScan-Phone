import QtQuick 2.6
import QtQuick.Layouts 1.3
import Qt.labs.controls 1.0

StackView {
    id: stackView
    initialItem:currentDialog
    anchors.topMargin: 5;
    anchors.fill: parent
    Rectangle{
        anchors.fill: parent
        color: "#ffffff"
    }

    ListView {
            id: currentDialog
            spacing: 5

            model: chatContact
            delegate: Rectangle {

                width : currentDialog.width* 0.8
                implicitHeight: messageItem.implicitHeight +20

                anchors.leftMargin:10;
                anchors.rightMargin:10;
                radius: 5

                anchors.right: model.modelData.status < 2 ? parent.right  : undefined
                anchors.left: model.modelData.status > 1 ? parent.left  : undefined


                color: "#f9f8f8"
                border.color: "#eceaea"


                Text {
                    id: messageItem
                    text: model.modelData.message
                    textFormat: Text.AutoText //
                    //height:real
                    anchors.fill: parent;
                    anchors.topMargin: 10;
                    anchors.leftMargin: 10;
                    anchors.rightMargin: 10;
                    anchors.bottomMargin: 10;
                    wrapMode: Text.WordWrap;
                    styleColor: "#00000000";
                    verticalAlignment: Text.AlignVCenter;
                }
            }

            ScrollIndicator.vertical: ScrollIndicator { }
        }


        Rectangle {
            id: footer

            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0

            Rectangle{
                       anchors.top: parent.top
                       height:1;
                       width: parent.width
                       color: "#313740"
                    }

            implicitHeight: textInput.implicitHeight +20

            TextArea {
                id:textInput
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5

                width: parent.width * 0.8
                wrapMode: Label.Wrap

                anchors.left: parent.left
                anchors.leftMargin: 10


                placeholderText: "Введите сообщение"
            }

            Image{

                source:"images/sendSms.png"
                anchors.verticalCenter: parent
                anchors.right: parent.right
                anchors.rightMargin: 10
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10

                MouseArea {
                    id: sendBtn
                    anchors.fill: parent
                    onClicked: {
                        signal.onSendMsg("", textInput.text)
                        //stackView.push("qrc:chatList.qml");
                    }
                }
            }

        }
}
