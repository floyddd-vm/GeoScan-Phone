#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gsmcall.h"

#include <qlocalsocket.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    GSMCall *callObj;
    QLocalSocket *socket;
public slots:
    void callEvent(QString number);
    void callDone();
    void onInitialized(bool initialized);
    //void onFinished(const QString &id, const int &code);
    void onOperatorName(QString name);
    void outCallEvent(QString str);
    void onSignalLevel(int signalLevel, int errorLevel);
private slots:

    void on_pushButton_3_clicked();

    void on_btnAccept_clicked();

    void on_btnDecline_clicked();

private:
    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
