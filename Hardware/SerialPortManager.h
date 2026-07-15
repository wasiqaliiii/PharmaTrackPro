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

    bool openPort(const QString& portName,
                  qint32 baudRate = QSerialPort::Baud115200);

    void closePort();

    bool isConnected() const;

    bool writeData(const QByteArray& data);

signals:
    void connected();
    void disconnected();
    void dataReceived(const QByteArray& data);
    void errorOccurred(const QString& error);

private slots:
    void onReadyRead();
    void onErrorOccurred(QSerialPort::SerialPortError error);

private:
    QSerialPort m_serialPort;
};

}