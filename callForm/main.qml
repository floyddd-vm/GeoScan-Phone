import QtQuick.Layouts 1.3
import Qt.labs.controls 1.0
import Qt.labs.controls.material 1.0
import Qt.labs.controls.universal 1.0
import Qt.labs.settings 1.0
import QtQuick 2.6


ApplicationWindow {

    id: window
    width: 480
    height: 640
    visible: true
    title: "Qt Labs Controls"
    readonly property int itemWidth: Math.max(button.implicitWidth, Math.min(button.implicitWidth * 2, pane.availableWidth / 3))
    property string style: "Material"
    header: ToolBar {
        RowLayout {
            spacing: 20
            anchors.fill: parent
/*
            Rectangle {
                        id: backButton
                        width: 60//opacity ? 60 : 0
                        anchors.left: parent.left
                        anchors.leftMargin: 20
                        opacity: 1//stackView.depth > 1
                        anchors.verticalCenter: parent.verticalCenter
                        //antialiasing: true
                        height: 60
                        radius: 4

                        color: "black"//backmouse.pressed ? "#222" : "transparent"
                        //Behavior on opacity { NumberAnimation{} }
                        Image {
                            //anchors.verticalCenter: parent.verticalCenter
                            source: "qrc:/back.png"
                        }
                        MouseArea {
                            id: backmouse
                            anchors.fill: parent
                            anchors.margins: -10
                            onClicked:
                            {
                                console.log(stackView.depth);
                                stackView.pop()
                            }
                        }
                    }
            */
            Button {

                text: "Back"
                width: itemWidth
                onClicked: {
                        stackView.pop()
                }
            }
            Button {
                text: "First"
                width: itemWidth
                onClicked: {
                        stackView.push("qrc:/addContact.qml")
                        saveBtn.enabled = true
                    }
            }
            Button {
                id: button
                text: "Second"
                width: itemWidth
                onClicked: {
                        stackView.push("qrc:/incoming_call.qml")
                    }
                //model: ListModel {
                //    ListElement { title: "addContact"; source: "qrc:/addContact.qml" }
               //     ListElement { title: "Button"; source: "qrc:/incoming_call.qml" }
               // }
            }
            Button {
                id: saveBtn
                text: "Save"
                enabled: false
                width: itemWidth
                onClicked: {
                        //callMain.addContact()
                        stackView.pop()
                }
            }
        }
    }


    StackView {
        id: stackView
        anchors.fill: parent

        initialItem: Pane {
            id: pane
            anchors.fill: parent


            Label {
                color: "#26282a"
                text: "Стартуем"
                anchors.margins: 20
                anchors.top: logo.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: arrow.top
                horizontalAlignment: Label.AlignHCenter
                verticalAlignment: Label.AlignVCenter
                wrapMode: Label.Wrap
            }
        }
    }
}
