#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick/qquickview.h>

#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qqml.h>
#include <QtQuick/qquickitem.h>

#include <QQmlContext>
#include <QtNetwork>
//#include <qtelephonynamespace.h>
#include <QLocalSocket>
#include "callMain.h"


QObject *qml;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    QQmlContext* ctx = engine.rootContext();

    CallMain *cm = new CallMain();
    ctx->setContextProperty("callMain", cm);
    ctx->setContextProperty("callObj", cm->callObj);
    engine.load(QUrl("qrc:incoming_call.qml"));
    if (engine.rootObjects().isEmpty())
        return -1;


    //Форма вызвана извне, параметром передан номер телефона - вызывать incoming_call.qml
    qDebug() << "argc " << argc;
    if(argc > 1)
    {
              qDebug() << "argv " << argv[1];
        //QString number = argv[1];   // номер телефона

            //ctxt->setContextProperty("myModel", QVariant::fromValue(dataList));

        //------------------------------------
        //qml = view.rootObject();


       // QObject::connect(qml, SIGNAL(acceptSignal()), cm->callObj , SLOT(accept()));
        //QObject::connect(qml, SIGNAL(declineSignal()), cm->callObj , SLOT(decline()));
        //QObject::connect(qml, SIGNAL(endCallSignal()), cm , SLOT(onEndCall()));
        QObject::connect(cm, SIGNAL(appQuit()), QGuiApplication::instance() , SLOT(quit()));
        QObject *phoneField = engine.rootObjects().first()->findChild<QObject*>("phone");
        QString phoneNum = argv[1];
        phoneField->setProperty("text",QVariant(phoneNum.remove(0, 1)));
    //    view.show(); //showFullScreen();
   //     view.resize(480, 640);
    }

    return app.exec();
}


