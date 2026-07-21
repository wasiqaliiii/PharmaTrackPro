#include "SerialDriver.h"

#include <QDebug>
#include <QEventLoop>
#include <QThread>

namespace PharmaTrack
{

////////////////////////////////////////////////////////
/// Constructor
////////////////////////////////////////////////////////

SerialDriver::SerialDriver(QObject* parent)
    : ScannerDriver(parent)
{
    //////////////////////////////////////////////////////
    /// Serial Port
    //////////////////////////////////////////////////////

    m_serial = new QSerialPort(this);

    connect(m_serial,
            &QSerialPort::readyRead,
            this,
            &SerialDriver::onReadyRead);

    connect(m_serial,
            &QSerialPort::errorOccurred,
            this,
            &SerialDriver::onErrorOccurred);

    //////////////////////////////////////////////////////
    /// Reconnect Timer
    //////////////////////////////////////////////////////

    m_reconnectTimer = new QTimer(this);

    m_reconnectTimer->setInterval(3000);

    connect(m_reconnectTimer,
            &QTimer::timeout,
            this,
            &SerialDriver::reconnect);
}

////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////

SerialDriver::~SerialDriver()
{
    disconnectDriver();
}

////////////////////////////////////////////////////////
/// Connect Driver
////////////////////////////////////////////////////////

bool SerialDriver::connectDriver()
{
    if (m_connected)
        return true;

    if (autoDetectScanner())
    {
        qDebug() << "[Serial] Scanner connected.";

        emit connected();

        return true;
    }

    if (!m_reconnectTimer->isActive())
    {
        m_reconnectTimer->start();
    }

    qDebug() << "[Serial] No scanner detected.";

    return false;
}

////////////////////////////////////////////////////////
/// Auto Detect Scanner
////////////////////////////////////////////////////////

bool SerialDriver::autoDetectScanner()
{
    const QList<QSerialPortInfo> ports =
            QSerialPortInfo::availablePorts();

    if (ports.isEmpty())
    {
        qDebug() << "[Serial] No COM ports available.";

        return false;
    }

    static const QList<qint32> baudRates =
    {
        115200,
        57600,
        38400,
        19200,
        9600
    };

    for (const QSerialPortInfo& port : ports)
    {
        qDebug() << "[Serial] Testing"
                 << port.portName();

        for (qint32 baudRate : baudRates)
        {
            if (!connectPort(
                        port.portName(),
                        baudRate))
            {
                continue;
            }

            if (testCommunication())
            {
                m_portName = port.portName();
                m_baudRate = baudRate;
                m_connected = true;

                qDebug() << "[Serial] Connected:"
                         << m_portName
                         << "@"
                         << m_baudRate;

                return true;
            }

            m_serial->close();
        }
    }

    return false;
}

////////////////////////////////////////////////////////
/// Connect Port
////////////////////////////////////////////////////////

bool SerialDriver::connectPort(
        const QString& portName,
        qint32 baudRate)
{
    if (m_serial->isOpen())
    {
        m_serial->close();
    }

    m_serial->setPortName(portName);

    m_serial->setBaudRate(baudRate);

    m_serial->setDataBits(
                QSerialPort::Data8);

    m_serial->setParity(
                QSerialPort::NoParity);

    m_serial->setStopBits(
                QSerialPort::OneStop);

    m_serial->setFlowControl(
                QSerialPort::NoFlowControl);

    if (!m_serial->open(
                QIODevice::ReadWrite))
    {
        return false;
    }

    return true;
}

////////////////////////////////////////////////////////
/// Disconnect Driver
////////////////////////////////////////////////////////

void SerialDriver::disconnectDriver()
{
    if (m_serial->isOpen())
    {
        m_serial->close();
    }

    m_connected = false;

    if (!m_reconnectTimer->isActive())
    {
        m_reconnectTimer->start();
    }

    emit disconnected();
}

////////////////////////////////////////////////////////
/// Test Communication
////////////////////////////////////////////////////////

bool SerialDriver::testCommunication()
{
    if (!m_serial->isOpen())
    {
        return false;
    }

    //////////////////////////////////////////////////////
    /// Wait briefly for incoming data.
    /// Most industrial scanners continuously transmit
    /// decoded data once a barcode is scanned.
    //////////////////////////////////////////////////////

    if (m_serial->waitForReadyRead(500))
    {
        QByteArray data = m_serial->readAll();

        while (m_serial->waitForReadyRead(20))
        {
            data.append(m_serial->readAll());
        }

        if (!data.isEmpty())
        {
            emit dataReceived(data);

            return true;
        }
    }

    //////////////////////////////////////////////////////
    /// Port opened successfully.
    /// Keep it available even if no barcode has been
    /// scanned yet.
    //////////////////////////////////////////////////////

    return true;
}

////////////////////////////////////////////////////////
/// Send
////////////////////////////////////////////////////////

bool SerialDriver::send(
        const QByteArray& data)
{
    if (!m_connected)
    {
        return false;
    }

    if (!m_serial->isOpen())
    {
        return false;
    }

    qint64 bytesWritten =
            m_serial->write(data);

    if (bytesWritten == -1)
    {
        emit errorOccurred(
                    m_serial->errorString());

        return false;
    }

    return m_serial->waitForBytesWritten(1000);
}

////////////////////////////////////////////////////////
/// Ready Read
////////////////////////////////////////////////////////

void SerialDriver::onReadyRead()
{
    while (m_serial->bytesAvailable())
    {
        QByteArray data =
                m_serial->readAll();

        if (!data.isEmpty())
        {
            emit dataReceived(data);

            qDebug() << "[Serial] Data:"
                     << QString::fromUtf8(data).trimmed();
        }
    }
}

////////////////////////////////////////////////////////
/// Error Occurred
////////////////////////////////////////////////////////

void SerialDriver::onErrorOccurred(
        QSerialPort::SerialPortError error)
{
    if (error ==
            QSerialPort::NoError)
    {
        return;
    }

    qDebug() << "[Serial] Error:"
             << m_serial->errorString();

    emit errorOccurred(
                m_serial->errorString());

    if (error ==
            QSerialPort::ResourceError ||
        error ==
            QSerialPort::DeviceNotFoundError ||
        error ==
            QSerialPort::PermissionError)
    {
        if (m_serial->isOpen())
        {
            m_serial->close();
        }

        if (m_connected)
        {
            m_connected = false;

            emit connectionLost();

            emit disconnected();
        }

        if (!m_reconnectTimer->isActive())
        {
            m_reconnectTimer->start();
        }
    }
}

////////////////////////////////////////////////////////
/// Reconnect
////////////////////////////////////////////////////////

void SerialDriver::reconnect()
{
    if (m_connected)
    {
        m_reconnectTimer->stop();

        return;
    }

    qDebug() << "[Serial] Searching for scanner...";

    if (autoDetectScanner())
    {
        m_reconnectTimer->stop();

        m_connected = true;

        emit connected();

        qDebug() << "[Serial] Scanner reconnected.";
    }
}

////////////////////////////////////////////////////////
/// Information
////////////////////////////////////////////////////////

bool SerialDriver::isConnected() const
{
    return m_connected;
}

QString SerialDriver::portName() const
{
    return m_portName;
}

qint32 SerialDriver::baudRate() const
{
    return m_baudRate;
}

}