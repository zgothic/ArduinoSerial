#ifndef SMARTTABLE_H
#define SMARTTABLE_H

#include <QtCore/QDebug>
#include <QApplication>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QString>
#include <QtWidgets>

#include <iostream>

class SmartTable : public QWidget
{
    Q_OBJECT
private:
    QSerialPort serial;
    QByteArray dataBuffer;
public:
    SmartTable(const QString &deviceName /*QString deviceBaudRate,*/, QWidget *parent = 0 )
        :QWidget(parent)
    {
        QSerialPortInfo info(deviceName);
        // Check info of the port
        qDebug() << "Name        : " << info.portName();
        qDebug() << "Manufacturer: " << info.manufacturer(); //if showing manufacturer, means Qstring &name is good
        qDebug() << "Busy: " << info.isBusy() << endl;

        // Initialize Serial
        serial.setPortName(deviceName);;
        serial.open(QIODevice::ReadWrite);
        serial.setBaudRate(QSerialPort::Baud9600);
        serial.setDataBits(QSerialPort::Data8);
        serial.setParity(QSerialPort::NoParity);
        serial.setStopBits(QSerialPort::OneStop);
        serial.setFlowControl(QSerialPort::NoFlowControl);

        serial.open(QIODevice::ReadWrite);
        QObject::connect(&serial, SIGNAL( readyRead() ), this, SLOT( read() ) );
    }
signals:
    void signalBlue(bool);
    void signalOrange();
    void signalRed();
    void signalLight();
    void signalShowTask(int);
    void signalNewTask(int);
    void signalDeleteTask(int);

public slots:

    void read()
    {
        qDebug() << "signal:";
        if (serial.isOpen() && serial.isWritable() && serial.isReadable())
        {
            dataBuffer.append(serial.readAll());
            generateSignal();
        }
        else
        {
            qDebug() << "An error occured" << endl;
        }
        qApp->processEvents();
    }

    void generateSignal()
    {
        //static const char *
        if(dataBuffer.contains("blueon"))
        {
            emit signalBlue(true);
            dataBuffer.clear();
        }

        if(dataBuffer.contains("blueoff") )
        {
            emit signalBlue(false);
            dataBuffer.clear();
        }

        if(dataBuffer.contains("orange"))
        {
            emit signalOrange();
            dataBuffer.clear();
        }

        if(dataBuffer.contains("red") )
        {
            emit signalRed();
            dataBuffer.clear();
        }

        /*if(dataBuffer.contains("light") )
        {
            emit signalLight();
            dataBuffer.clear();
        }*/

        if(dataBuffer.contains("task1on") )
        {
            emit signalNewTask(1);
            dataBuffer.clear();
        }

        if(dataBuffer.contains("task2on") )
        {
            emit signalNewTask(2);
            dataBuffer.clear();
        }

        if(dataBuffer.contains("task3on") )
        {
            emit signalNewTask(3);
            dataBuffer.clear();
        }

        if(dataBuffer.contains("task1off") )
        {
            emit signalDeleteTask(1);
            dataBuffer.clear();
        }

        if(dataBuffer.contains("task2off") )
        {
            emit signalDeleteTask(2);
            dataBuffer.clear();
        }

        if(dataBuffer.contains("task3off") )
        {
            emit signalDeleteTask(3);
            dataBuffer.clear();
        }

        if(dataBuffer.contains("task1show") )
        {
            emit signalShowTask(1);
            dataBuffer.clear();
        }

        if(dataBuffer.contains("task2show") )
        {
            emit signalShowTask(2);
            dataBuffer.clear();
        }

        if(dataBuffer.contains("task3show") )
        {
            emit signalShowTask(3);
            dataBuffer.clear();
        }
    }
};

#endif // SMARTTABLE_H
