import QtQuick 2.0
import QtQuick.Controls 1.3

//![0]
Column{
    id: column1
    anchors.fill: parent

    signal chatChoice(string msg)
    width: 400
    height: 600

    Rectangle {
        id: header
        x: 0
        y: 0
        width: parent.width
        height: 48
        color: "#313740"
        z: 2

        Text {
            id: headerTitle
            color: "#ffffff"
            text: qsTr("Сообщения")
            font.family: "Verdana"
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 10
            font.pixelSize: 20
        }
    }


    //--------------------------------------------dialogList---------------------------

    ListView {
        id: dialogList
        anchors.fill: parent

        anchors.topMargin: header.height
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

                //layer.enabled: true
                elide:Text.ElideRight;
            }

            Text {
                id: dateTime;
                x: 268
                //width: dialogItem.width*0.2
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


            MouseArea {
                id: mouseArea1
                anchors.rightMargin: 0
                anchors.bottomMargin: 0
                anchors.leftMargin: 0
                anchors.topMargin: 0
                anchors.fill: parent

                onClicked: {
                    dialogList.visible = false
                    currentDialog.visible = true
                    column1.chatChoice(model.modelData.id)
                    bbtn.visible = true;
                    headerTitle.text = model.modelData.contact
                }
            }
        }





    }
    //-------------------------------------------------------------------------------------------
    Item{
        id: bbtn
        width: 50
        height: 50
        visible: true
        z:6
        // visible: false;
        Image {
            id: image1
            width: 30
            height: 30
            anchors.horizontalCenter: backButton.horizontalCenter
            anchors.verticalCenter: backButton.verticalCenter
            z: 4
            source: "ArrowLeft1.png"
        }
        Rectangle{
            id: backButton
            x: 5
            y: 5
            width: 38
            height: 38
            color: "#ffffff"
            opacity: 0.0
            radius: 40
            z: 4


            MouseArea {
                anchors.fill: parent;
                id: mouseArea2

                onPressed: {
                    //animateColor.start()
                    animateOpacity.start()
                    scaleTransform.start()
                    //animateOpacityTwo.start()
                }
                onReleased:
                {
                    scaleTransformTwo.start()
                    animateOpacityTwo.start()

                    dialogList.visible = true
                    currentDialog.visible = false
                    bbtn.visible = false;

                    headerTitle.text = qsTr("Сообщения")
                }
            }

            //PropertyAnimation {id: animateColor; target: backButton; properties: "color"; to: "green"; duration: 100}

            NumberAnimation {
                id: animateOpacity
                target: backButton
                properties: "opacity"
                from: 0.0
                to: 1.0
                duration: 200
            }
            NumberAnimation {
                id: animateOpacityTwo
                target: backButton
                properties: "opacity"
                from: 1.0
                to: 0.0
                duration: 200
            }

            PropertyAnimation {
                id:scaleTransform
                target: backButton
                properties: "scale"
                from: 1.0
                to: 2.0
                duration: 200
            }
            PropertyAnimation {
                id:scaleTransformTwo
                target: backButton
                properties: "scale"
                from: 2.0
                to: 1.0
                duration: 200
            }
        }
    }


    //---------------------------------CurrentChat-----------------------------------------------

    ListView {
        id: currentDialog
        anchors.bottom: footer.top
        anchors.bottomMargin: 0
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        visible: false
        anchors.topMargin: header.height+5

        spacing: 10

        model: chatContact
        delegate: Rectangle {
            //width: 300
            width : currentDialog.width* 0.8
            implicitHeight: messageItem.implicitHeight +20

            anchors.leftMargin:10;
            anchors.rightMargin:10;
            radius: 5
            //anchors.left: column1.left
            anchors.right: model.modelData.status < 2 ? parent.right  : false
            anchors.left: model.modelData.status > 1 ? parent.left  : false


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

    }

    Rectangle {
        id: footer
        height: 50
        color: "#313740"
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0

        Rectangle {
            id: textInputRectangle
            color: "#ffffff"
            radius: 13
            anchors.top: parent.top
            anchors.topMargin: 10
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 100
            anchors.left: parent.left
            anchors.leftMargin: 20

            TextEdit {
                id: textEdit1
                text: qsTr("Введите сообщение")
                anchors.top: parent.top
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.rightMargin: 8
                anchors.leftMargin: 8
                anchors.bottomMargin: 5
                anchors.topMargin: 5
                selectionColor: "#6361bd"
                font.pixelSize: 12
            }
        }

        Image {
            id: imageBtn
            width: 35
            height: 30
            anchors.horizontalCenter: radiusSendBtn.horizontalCenter
            anchors.right: parent.righr
            anchors.verticalCenter: parent.verticalCenter
            source: "images/sendSms.png"
        }

        Rectangle {
            id: radiusSendBtn
            width: 35
            height: 30
            color: "#ffffff"
            radius: 40
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 10
            opasity:0
        }

        MouseArea {
            id: sendSmsBtn
            width: 35
            height: 30
            anchors.horizontalCenter: imageBtn.horizontalCenter
            anchors.verticalCenter: imageBtn.verticalCenter
            onPressed: {
                //animateColor.start()
                animateOpacity1.start()
                scaleTransform1.start()
                //animateOpacityTwo.start()
            }
            onReleased:
            {
                scaleTransformTwo1.start()
                animateOpacityTwo1.start()

                //dialogList.visible = true
                //currentDialog.visible = false
                //bbtn.visible = false;

                headerTitle.text = qsTr("Новое сообщение")
            }
        }

        //PropertyAnimation {id: animateColor; target: backButton; properties: "color"; to: "green"; duration: 100}

        NumberAnimation {
            id: animateOpacity1
            target: radiusSendBtn
            properties: "opacity"
            from: 0.0
            to: 1.0
            duration: 200
        }
        NumberAnimation {
            id: animateOpacityTwo1
            target: radiusSendBtn
            properties: "opacity"
            from: 1.0
            to: 0.0
            duration: 200
        }

        PropertyAnimation {
            id:scaleTransform1
            target: radiusSendBtn
            properties: "scale"
            from: 1.0
            to: 2.0
            duration: 200
        }
        PropertyAnimation {
            id:scaleTransformTwo1
            target: radiusSendBtn
            properties: "scale"
            from: 2.0
            to: 1.0
            duration: 200
        }
    }





}

