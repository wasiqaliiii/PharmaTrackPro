#include "SerialPortManager.h"
#include <QDebug>
namespace PharmaTrack
{

SerialPortManager::SerialPortManager(QObject* parent)
    : QObject(parent)
{
    connect(&m_serialPort,
            &QSerialPort::readyRead,
            this,
            &SerialPortManager::onReadyRead);

    connect(&m_serialPort,
            &QSerialPort::errorOccurred,
            this,
            &SerialPortManager::onErrorOccurred);
}

SerialPortManager::~SerialPortManager()
{
    closePort();
}

QStringList SerialPortManager::availablePorts() const
{
    QStringList ports;

    const auto serialPorts = QSerialPortInfo::availablePorts();

    for (const auto& port : serialPorts)
    {
        ports.append(port.portName());
    }

    return ports;
}

bool SerialPortManager::openPort(const QString& portName,
                                 qint32 baudRate)
{
    if (m_serialPort.isOpen())
        m_serialPort.close();

    m_serialPort.setPortName(portName);

    m_serialPort.setBaudRate(baudRate);
    m_serialPort.setDataBits(QSerialPort::Data7);
m_serialPort.setParity(QSerialPort::EvenParity);
    m_serialPort.setStopBits(QSerialPort::OneStop);
    m_serialPort.setFlowControl(QSerialPort::NoFlowControl);

    if (!m_serialPort.open(QIODevice::ReadWrite))
    {
        emit errorOccurred(m_serialPort.errorString());
        return false;
    }

    emit connected();

    return true;
}

void SerialPortManager::closePort()
{
    if (!m_serialPort.isOpen())
        return;

    m_serialPort.close();

    emit disconnected();
}

bool SerialPortManager::isConnected() const
{
    return m_serialPort.isOpen();
}

bool SerialPortManager::writeData(const QByteArray& data)
{
    if (!m_serialPort.isOpen())
        return false;

    return m_serialPort.write(data) > 0;
}

void SerialPortManager::onReadyRead()
{
    QByteArray data = m_serialPort.readAll();

    qDebug() << "Bytes Received:" << data.toHex(' ');
    qDebug() << "Text Received :" << QString::fromUtf8(data);

    emit dataReceived(data);
}

void SerialPortManager::onErrorOccurred(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::NoError)
        return;

    emit errorOccurred(m_serialPort.errorString());
}

}