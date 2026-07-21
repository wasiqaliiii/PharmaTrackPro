#include "SerialPortManager.h"

#include <QDebug>

namespace PharmaTrack
{

SerialPortManager::SerialPortManager(QObject* parent)
    : QObject(parent),
      m_currentBaudRate(0),
      m_currentDataBits(QSerialPort::Data8),
      m_currentParity(QSerialPort::NoParity),
      m_currentStopBits(QSerialPort::OneStop)
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

////////////////////////////////////////////////////////
/// Available Ports
////////////////////////////////////////////////////////

QStringList SerialPortManager::availablePorts() const
{
    QStringList ports;

    const auto serialPorts =
            QSerialPortInfo::availablePorts();

    for(const auto& port : serialPorts)
    {
        ports.append(port.portName());
    }

    return ports;
}

////////////////////////////////////////////////////////
/// Connection
////////////////////////////////////////////////////////

bool SerialPortManager::openPort(
        const QString& portName,
        qint32 baudRate,
        QSerialPort::DataBits dataBits,
        QSerialPort::Parity parity,
        QSerialPort::StopBits stopBits,
        QSerialPort::FlowControl flowControl)
{
    //----------------------------------------------------
    // Close Previous Connection
    //----------------------------------------------------

    if(m_serialPort.isOpen())
    {
        m_serialPort.close();
        m_serialPort.clear();
    }

    //----------------------------------------------------
    // Configure Port
    //----------------------------------------------------

    m_serialPort.setPortName(portName);

    m_serialPort.setBaudRate(baudRate);

    m_serialPort.setDataBits(dataBits);

    m_serialPort.setParity(parity);

    m_serialPort.setStopBits(stopBits);

    m_serialPort.setFlowControl(flowControl);

    //----------------------------------------------------
    // Open
    //----------------------------------------------------

    if(!m_serialPort.open(QIODevice::ReadWrite))
    {
        emit errorOccurred(
                    m_serialPort.errorString());

        return false;
    }

    //----------------------------------------------------
    // Clear Old Data
    //----------------------------------------------------

    m_serialPort.clear(QSerialPort::AllDirections);

    m_lastData.clear();

    //----------------------------------------------------
    // Save Configuration
    //----------------------------------------------------

    m_currentPort = portName;

    m_currentBaudRate = baudRate;

    m_currentDataBits = dataBits;

    m_currentParity = parity;

    m_currentStopBits = stopBits;

    emit connected();

    return true;
}

void SerialPortManager::closePort()
{
    if(!m_serialPort.isOpen())
        return;

    //----------------------------------------------------
    // Close
    //----------------------------------------------------

    m_serialPort.close();

    m_serialPort.clear();

    //----------------------------------------------------
    // Clear Configuration
    //----------------------------------------------------

    m_currentPort.clear();

    m_currentBaudRate = 0;

    m_currentDataBits = QSerialPort::Data8;

    m_currentParity = QSerialPort::NoParity;

    m_currentStopBits = QSerialPort::OneStop;

    //----------------------------------------------------
    // Clear Data
    //----------------------------------------------------

    m_lastData.clear();

    emit disconnected();
}

////////////////////////////////////////////////////////
/// Status
////////////////////////////////////////////////////////

bool SerialPortManager::isConnected() const
{
    return m_serialPort.isOpen();
}

////////////////////////////////////////////////////////
/// Read / Write
////////////////////////////////////////////////////////

bool SerialPortManager::writeData(const QByteArray& data)
{
    if(!m_serialPort.isOpen())
        return false;

    return m_serialPort.write(data) > 0;
}

QByteArray SerialPortManager::readData()
{
    return m_lastData;
}

////////////////////////////////////////////////////////
/// Current Configuration
////////////////////////////////////////////////////////

QString SerialPortManager::currentPort() const
{
    return m_currentPort;
}

qint32 SerialPortManager::currentBaudRate() const
{
    return m_currentBaudRate;
}

QSerialPort::DataBits
SerialPortManager::currentDataBits() const
{
    return m_currentDataBits;
}

QSerialPort::Parity
SerialPortManager::currentParity() const
{
    return m_currentParity;
}

QSerialPort::StopBits
SerialPortManager::currentStopBits() const
{
    return m_currentStopBits;
}

////////////////////////////////////////////////////////
/// Slots
////////////////////////////////////////////////////////

void SerialPortManager::onReadyRead()
{
    m_lastData.append(
        m_serialPort.readAll());

    QString text =
            QString::fromUtf8(m_lastData);

    qDebug() << "Bytes Received:"
             << m_lastData.toHex(' ');

    qDebug() << "Text Received :"
             << text;

    emit dataReceived(m_lastData);
    m_lastData.clear();
}

void SerialPortManager::onErrorOccurred(
        QSerialPort::SerialPortError error)
{
    if(error == QSerialPort::NoError)
        return;

    emit errorOccurred(
                m_serialPort.errorString());
}

}