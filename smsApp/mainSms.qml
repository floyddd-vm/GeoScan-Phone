import QtQuick 2.6
import QtQuick.Layouts 1.3
import Qt.labs.controls 1.0
import Qt.labs.controls.material 1.0
import Qt.labs.controls.universal 1.0
import Qt.labs.settings 1.0

ApplicationWindow {
    id: window
    width: 360
    height: 520
    visible: true
    title: "Qt Labs Controls";



    header: ToolBar {
        anchors.left: parent.left
        anchors.right: parent.right
        RowLayout {
            spacing: 20
            anchors.fill: parent

            Button {
                    opacity: stackView.depth > 1
                    onClicked: {
                        titleLabel.text = "Сообщения"
                        stackView.pop();
                    }
             }

            Label {
                objectName: "title"
                id: titleLabel
                text: "Сообщения"
                color: "#ffffff"
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

        }
    }



        StackView {
            id: stackView
            anchors.fill: parent

            Rectangle{
                anchors.fill: parent
                color: "#ffffff"
            }

            initialItem: ListView {
                        id: dialogList
                        anchors.fill: parent
                        model: myModel

                        spacing: 1


                        delegate: Rectangle {
                            id : dialogItem
                            x: 0
                            y: 48
                            height: 62
                            color: "#FFFFFF"
                            z: 1

                            width: parent.width

                            Rectangle {
                                id: rectangle2
                                color: "#eceaea"
                                height: 1;
                                width: parent.width* 0.98
                                anchors.horizontalCenter: parent.horizontalCenter
                            }

                            Text {
                                id: phone;
                                text: model.modelData.contact ;
                                anchors.rightMargin: 51
                                anchors.topMargin: 0
                                anchors.bottomMargin: 31
                                anchors.fill: parent;
                                styleColor: "#00000000";
                                verticalAlignment: Text.AlignVCenter;
                                horizontalAlignment:Text.AlignLeft
                                anchors.leftMargin: 10
                                font.pixelSize: 15
                            }

                            Rectangle {
                                id: radiusNotification
                                visible: model.modelData.status == 6 ? true: false
                                width: 10
                                height: 10
                                color: "#9cff89"
                                radius: 40
                                anchors.top: parent.top
                                anchors.topMargin: 15
                                anchors.right: parent.right
                                anchors.rightMargin: 15
                            }

                            Text {

                                id: message;
                                clip:false
                                text: model.modelData.message ;
                                font.family: "Verdana"
                                style: Text.Normal
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin: 0
                                anchors.left: parent.left
                                anchors.leftMargin: 10
                                anchors.top: phone.bottom
                                anchors.topMargin: -1
                                anchors.right: dateTime.left
                                anchors.rightMargin: 24
                                wrapMode: Text.NoWrap;
                                verticalAlignment: Text.AlignVCenter;
                                horizontalAlignment:Text.AlignLeft
                                font.pixelSize: 12

                                elide:Text.ElideRight;
                            }

                            Text {
                                id: dateTime;
                                x: 268
                                text: model.modelData.dateTime
                                anchors.right: parent.right
                                anchors.rightMargin: 5
                                anchors.top: phone.bottom
                                anchors.topMargin: 0
                                anchors.bottom: parent.bottom
                                anchors.bottomMargin: 0

                                verticalAlignment: Text.AlignVCenter
                                font.pixelSize: 10

                            }

                            Connections {
                                target: signal
                                //ChatChoice: {
                                //console.log("Received in QML from C++: " + count)
                                //}
                              }

                            MouseArea {
                                id: mouseArea1
                                anchors.rightMargin: 0
                                anchors.bottomMargin: 0
                                anchors.leftMargin: 0
                                anchors.topMargin: 0
                                anchors.fill: parent

                                onClicked: {
                                    signal.onChatChoice(model.modelData.id,model.modelData.contact)
                                    stackView.push("qrc:chatList.qml");
                                }
                            }

                        }
                     ScrollIndicator.vertical: ScrollIndicator { }

                }
        }





}
