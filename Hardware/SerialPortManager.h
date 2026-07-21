#pragma once

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace PharmaTrack
{

class SerialPortManager : public QObject
{
    Q_OBJECT

public:
    explicit SerialPortManager(QObject* parent = nullptr);
    ~SerialPortManager();

    QStringList availablePorts() const;

    bool openPort(
        const QString& portName,
        qint32 baudRate,
        QSerialPort::DataBits dataBits,
        QSerialPort::Parity parity,
        QSerialPort::StopBits stopBits,
        QSerialPort::FlowControl flowControl =
                QSerialPort::NoFlowControl);

    void closePort();

    bool isConnected() const;

    bool writeData(const QByteArray& data);
    QByteArray readData();

    QString currentPort() const;

qint32 currentBaudRate() const;

QSerialPort::DataBits currentDataBits() const;

QSerialPort::Parity currentParity() const;

QSerialPort::StopBits currentStopBits() const;

signals:
    void connected();
    void disconnected();
    void dataReceived(const QByteArray& data);
    void errorOccurred(const QString& error);

private slots:
    void onReadyRead();
    void onErrorOccurred(QSerialPort::SerialPortError error);

private:

    //----------------------------------------------------
    // Serial Port
    //----------------------------------------------------

    QSerialPort m_serialPort;
    
    //----------------------------------------------------
// Last Received Data
//----------------------------------------------------
    //----------------------------------------------------
    // Current Configuration
    //----------------------------------------------------
    QByteArray m_lastData;
    QString m_currentPort;

    qint32 m_currentBaudRate;

    QSerialPort::DataBits m_currentDataBits;

    QSerialPort::Parity m_currentParity;

    QSerialPort::StopBits m_currentStopBits;
};

}