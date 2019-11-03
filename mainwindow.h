#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>

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
    void onRxDataFromSecondDevide();
    void onRxDataFromThridDevice();


};

#endif // MAINWINDOW_H
