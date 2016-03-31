import QtQuick 2.5
import QtQuick.Window 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0

ApplicationWindow {
    id: window
    width: 400
    height: 600
    property alias mainRec: mainRec
    visible: true
    title: "Qt Labs Controls"
Item {
    id: win

//    signal acceptSignal()
//    signal declineSignal()
//    signal endCallSignal()
    //signal isFaded()
    //width: 480
    //height: 640

    anchors.fill: parent
    Rectangle {
        id: mainRec

        color: "#2c2c2c"
        anchors.fill: parent

        Rectangle {
            id: rectangle1
            color: "#3f51b5"
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 258
            anchors.top: parent.top
            anchors.topMargin: 0


            Text {
                id: phoneName
                x: 111
                y: 141
                objectName: "phone"
                width: 258
                height: 50
                color: "white"
                text: qsTr("Phone number")
                anchors.horizontalCenterOffset: 0
                anchors.top: parent.top
                anchors.topMargin: 141
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 40
                wrapMode: Text.NoWrap
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }

        DropShadow {
            anchors.fill: rectangle1
            horizontalOffset: 0
            verticalOffset: 3
            radius: 8.0
            samples: 17
            color: "#aa000000"
            source: rectangle1
        }


Item{
    id: btnWrap
    anchors.fill : parent
        MouseArea {
            id: acceptBtn
            y: 477
            height: 90
            hoverEnabled: false
            anchors.left: parent.left
            anchors.leftMargin: 55
            anchors.right: parent.right
            anchors.rightMargin: 254
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 73
            opacity: 1.0
            onClicked : {
                //btnWrap.opacity = 0.0
                animateOpacity.start()
                console.log("clicked")
                //declineBtn.enabled = false
                //declineBtn.visible = false
                acceptBtn.enabled = false
                declineBtn.isEnd = true
                //acceptBtn.visible = false
                //endCallBtn.enabled = true
                //endCallBtn.visible = true
                declineBtn.anchors.left = undefined
                declineBtn.anchors.right = undefined
                declineBtn.anchors.bottom = undefined
                animateOpacity2.start()
                callObj.accept()
                //callMain.addCallRec()
                //win.acceptSignal()
                //endCallBtn.isFaded()
                // Появление кнопки завершения вызова
                // Анимация

            }

            Image {

                x: 0
                y: 0
                width: 90
                height: 90
                //anchors.top: avatar.bottom
                anchors.topMargin: 70
                source: "icons/accept.png"
            }

        }
        NumberAnimation {
            id: animateOpacity
            target: acceptBtn
            properties: "opacity"
            from: 1.0
            to: 0.0
            duration: 150

            //loops: Animation.Infinite
            //easing {type: Easing.OutBack; overshoot: 300}
        }
        NumberAnimation {
            id: animateOpacity2
            target: declineBtn
            properties: "x"
            //from: 0.0
            to: (mainRec.width / 2) - (declineBtn.width / 2)
            duration: 200
            //loops: Animation.Infinite
            //easing {type: Easing.OutBack; overshoot: 300}
        }
        MouseArea {
            id: declineBtn
            property bool isEnd : false
            y: 437
            height: 90
            anchors.left: parent.left
            anchors.leftMargin: 269
            anchors.right: parent.right
            anchors.rightMargin: 43
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 73
            onClicked : {
                //win.declineSignal()
                if(!isEnd)
                {
                    btnWrap.visible = false
                    callMain.onDeclined()
                }

                else
                    callMain.onEndCall()
                //declineBtn.enabled = false
                //declineBtn.visible = false
                acceptBtn.enabled = false
                //acceptBtn.visible = false
                //endCallBtn.visible = false
            }

            Image {

                x: 1
                y: 0
                width: 90
                height: 90
                anchors.right: parent.right
                anchors.rightMargin: -1
                transformOrigin: Item.Center
                //anchors.top: avatar.bottom
                anchors.topMargin: 78
                source: "icons/decline.png"
            }
        }
    }
    }
}
}

