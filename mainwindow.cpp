#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initSerialPort()
{
    firstDevice = new QSerialPort();
    secondDevice = new QSerialPort();
    thirdDevice = new QSerialPort();
    firstDevice->setBaudRate(9600);
    firstDevice->setDataBits(QSerialPort::Data8);
    firstDevice->setStopBits(QSerialPort::OneStop);
    secondDevice->setBaudRate(9600);
    secondDevice->setDataBits(QSerialPort::Data8);
    secondDevice->setStopBits(QSerialPort::OneStop);
    thirdDevice->setBaudRate(9600);
    thirdDevice->setDataBits(QSerialPort::Data8);
    thirdDevice->setStopBits(QSerialPort::OneStop);
    connect(firstDevice, SIGNAL(readyRead()), this, SLOT(onRxDataFromFirstDevice()));
    connect(secondDevice, SIGNAL(readyRead()), this, SLOT(onRxDataFromSecondDevice()));
    connect(thirdDevice, SIGNAL(readyRead()), this, SLOT(onRxDataFromThirdDevice));
}

void MainWindow::onRxDataFromFirstDevice()
{
    if (firstDevice->canReadLine()) {
        QString rxData = QString::fromLatin1(firstDevice->readLine());
        ui->miniterminal->appendPlainText(rxData);
        if (rxData.contains("+TX=")) {
            ui->txData->setText(rxData.replace("+TX=", ""));
        }else if (rxData.contains("+RX=")) {
            ui->currentRXData->setText(rxData.replace("+RX=", ""));
        }
    }
    if (firstDevice->bytesAvailable() > 0) QMetaObject::invokeMethod(this, "onRxDataFromFirstDevice");
}

void MainWindow::onRxDataFromSecondDevide()
{
    if (secondDevice->bytesAvailable() > 0) QMetaObject::invokeMethod(this, "onRxDataFromSecondDevice");
}

void MainWindow::onRxDataFromThridDevice()
{
    if (thirdDevice->bytesAvailable() > 0) QMetaObject::invokeMethod(this, "onRxDataFromThirdDevice");
}
