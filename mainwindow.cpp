#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    foreach (QSerialPortInfo serialPortInfo,  QSerialPortInfo::availablePorts()) {
        ui->serialPorts->addItem(serialPortInfo.portName());
        ui->serialPorts_2->addItem(serialPortInfo.portName());
        ui->serialPorts_3->addItem(serialPortInfo.portName());
    }
    initSerialPort();
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
    connect(thirdDevice, SIGNAL(readyRead()), this, SLOT(onRxDataFromThirdDevice()));
}

void MainWindow::onRxDataFromFirstDevice()
{
    if (firstDevice->canReadLine()) {
        QString rxData = QString::fromLatin1(firstDevice->readLine());
        ui->miniterminal->appendPlainText(rxData.replace("\r\n", ""));
        if (rxData.contains("+TX=")) {
            ui->txData->setText(rxData.replace("+TX=", "").left(15).append("|").append(QDateTime::currentDateTime().toString("hh:mm:ss")));
        }else if (rxData.contains("+RX=")) {
            ui->currentRXData->setText(rxData.replace("+RX=", ""));
        }
    }
    if (firstDevice->bytesAvailable() > 0) QMetaObject::invokeMethod(this, "onRxDataFromFirstDevice", Qt::QueuedConnection);
}

void MainWindow::onRxDataFromSecondDevice()
{
    if (secondDevice->canReadLine()) {
        QString rxData = QString::fromLatin1(secondDevice->readLine());
        ui->miniterminal_2->appendPlainText(rxData.replace("\r\n",""));
        if (rxData.contains("+TX=")) {
            ui->txData_2->setText(rxData.replace("+TX=", "").left(15).append(QDateTime::currentDateTime().toString("hh:mm:ss")));
        }else if (rxData.contains("+RX=")) {
            ui->currentRXData_2->setText(rxData.replace("+RX=", ""));
        }
    }
    if (secondDevice->bytesAvailable() > 0) QMetaObject::invokeMethod(this, "onRxDataFromSecondDevice", Qt::QueuedConnection);
}

void MainWindow::onRxDataFromThirdDevice()
{
    if (thirdDevice->canReadLine()) {
        QString rxData = QString::fromLatin1(thirdDevice->readLine());
        ui->miniterminal_3->appendPlainText(rxData);
        if (rxData.contains("+TX=")) {
            ui->txData_3->setText(rxData.replace("+TX=", ""));
        }else if (rxData.contains("+RX=")) {
            ui->currentRXData_3->setText(rxData.replace("+RX=", ""));
        }
    }
    if (thirdDevice->bytesAvailable() > 0) QMetaObject::invokeMethod(this, "onRxDataFromThirdDevice");
}

void MainWindow::on_connectBtn_clicked()
{
    if (!firstDevice->isOpen()) {
        firstDevice->setPortName(ui->serialPorts->currentText());
        if (firstDevice->open(QIODevice::ReadWrite)){
            ui->serialPorts_2->removeItem(ui->serialPorts->currentIndex());
            ui->serialPorts_3->removeItem(ui->serialPorts->currentIndex());
            ui->connectBtn->setText("Disconnect");
        }else{
            qDebug() << "Error: " << firstDevice->errorString();
        }
    }else{
        firstDevice->close();
        ui->connectBtn->setText("Connect");
    }

}

void MainWindow::on_connectBtn_2_clicked()
{
    if (!secondDevice->isOpen()) {
        secondDevice->setPortName(ui->serialPorts_2->currentText());
        if (secondDevice->open(QIODevice::ReadWrite)){
            ui->serialPorts->removeItem(ui->serialPorts_2->currentIndex());
            ui->serialPorts_3->removeItem(ui->serialPorts_3->currentIndex());
            ui->connectBtn_2->setText("Disconnect");
        }else{
            qDebug () << "Error: " << secondDevice->errorString();
        }
    }else{
        secondDevice->close();
        ui->connectBtn_2->setText("Connect");
    }
}

void MainWindow::on_connectBtn_3_clicked()
{
    if (!secondDevice->isOpen()) {
        secondDevice->setPortName(ui->serialPorts_3->currentText());
        if (secondDevice->open(QIODevice::ReadWrite)){
            ui->serialPorts->removeItem(ui->serialPorts_3->currentIndex());
            ui->serialPorts_2->removeItem(ui->serialPorts_3->currentIndex());
            ui->connectBtn_3->setText("Disconnect");
        }
    }else{
        thirdDevice->close();
        ui->connectBtn_3->setText("Connect");
    }
}
