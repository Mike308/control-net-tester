#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QDate>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSerialPort *firstDevice;
    QSerialPort *secondDevice;
    QSerialPort *thirdDevice;
    void initSerialPort();

private slots:
    void onRxDataFromFirstDevice();
    void onRxDataFromSecondDevice();
    void onRxDataFromThirdDevice();


    void on_connectBtn_clicked();
    void on_connectBtn_2_clicked();
    void on_connectBtn_3_clicked();
};

#endif // MAINWINDOW_H
