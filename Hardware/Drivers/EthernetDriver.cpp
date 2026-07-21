#include "EthernetDriver.h"
#include <QDateTime>
#include <QDebug>
#include <QHostAddress>
#include <QFile>
#include <QTextStream>
namespace PharmaTrack
{
static void logMessage(const QString& msg)
{
    QFile file("scanner_log.txt");

    if (file.open(QIODevice::Append | QIODevice::Text))
    {
        QTextStream out(&file);
        out << QDateTime::currentDateTime().toString("hh:mm:ss.zzz")
            << "  "
            << msg
            << "\n";
    }
}
////////////////////////////////////////////////////////
/// Constructor
////////////////////////////////////////////////////////

EthernetDriver::EthernetDriver(QObject* parent)
    : ScannerDriver(parent)
{
    //////////////////////////////////////////////////////
    /// Socket
    //////////////////////////////////////////////////////

    m_socket = new QTcpSocket(this);

    connect(m_socket,
            &QTcpSocket::connected,
            this,
            &EthernetDriver::onConnected);

    connect(m_socket,
            &QTcpSocket::disconnected,
            this,
            &EthernetDriver::onDisconnected);

    connect(m_socket,
            &QTcpSocket::readyRead,
            this,
            &EthernetDriver::onReadyRead);

    connect(m_socket,
            &QAbstractSocket::errorOccurred,
            this,
            &EthernetDriver::onSocketError);

    //////////////////////////////////////////////////////
    /// Heartbeat Timer
    //////////////////////////////////////////////////////

    m_heartbeatTimer = new QTimer(this);

    m_heartbeatTimer->setInterval(1000);

    connect(m_heartbeatTimer,
            &QTimer::timeout,
            this,
            &EthernetDriver::sendHeartbeat);

    //////////////////////////////////////////////////////
    /// Reconnect Timer
    //////////////////////////////////////////////////////

    m_reconnectTimer = new QTimer(this);

    m_reconnectTimer->setInterval(3000);

    connect(m_reconnectTimer,
            &QTimer::timeout,
            this,
            &EthernetDriver::reconnect);
}

////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////

EthernetDriver::~EthernetDriver()
{
    disconnectDriver();
}

////////////////////////////////////////////////////////
/// Connect Driver
////////////////////////////////////////////////////////

bool EthernetDriver::connectDriver()
{
    if (m_ipAddress.isEmpty())
        return false;

    if (m_port == 0)
        return false;

    connectToScanner(
                m_ipAddress,
                m_port);

    return true;
}

////////////////////////////////////////////////////////
/// Connect Scanner
////////////////////////////////////////////////////////

void EthernetDriver::connectToScanner(
        const QString& ipAddress,
        quint16 port)
{
    m_ipAddress = ipAddress;
    m_port = port;

    if (m_socket->state() !=
            QAbstractSocket::UnconnectedState)
    {
        m_socket->abort();
    }

    logMessage(QString("Connecting to %1:%2")
           .arg(ipAddress)
           .arg(port));
static int ethCount = 0;

qDebug() << "[EthernetDriver] connectToScanner:"
         << ++ethCount;
    m_socket->connectToHost(
                QHostAddress(ipAddress),
                port);
    qDebug() << "[Ethernet] Socket State:"
         << m_socket->state();
}

////////////////////////////////////////////////////////
/// Disconnect
////////////////////////////////////////////////////////

void EthernetDriver::disconnectDriver()
{
    if (m_heartbeatTimer)
        m_heartbeatTimer->stop();

    if (m_reconnectTimer)
        m_reconnectTimer->stop();

    if (m_socket &&
        m_socket->state() !=
        QAbstractSocket::UnconnectedState)
    {
        m_socket->disconnectFromHost();
    }

    m_connected = false;

    emit disconnected();
}

////////////////////////////////////////////////////////
/// Connected
////////////////////////////////////////////////////////

void EthernetDriver::onConnected()
{
    logMessage("TCP CONNECTED");
    qDebug() << "***** TCP CONNECTED *****";

    qDebug() << "[Ethernet] Connected";
    

    m_connected = true;

    m_reconnectTimer->stop();

    m_heartbeatTimer->start();

    emit connected();
}

////////////////////////////////////////////////////////
/// Disconnected
////////////////////////////////////////////////////////

void EthernetDriver::onDisconnected()
{
    qDebug() << "[Ethernet] Disconnected";

    m_connected = false;

    m_heartbeatTimer->stop();

    m_reconnectTimer->start();

    emit disconnected();

    emit connectionLost();
}

////////////////////////////////////////////////////////
/// Ready Read
////////////////////////////////////////////////////////

void EthernetDriver::onReadyRead()
{
    while (m_socket->bytesAvailable())
    {
        QByteArray data =
                m_socket->readAll();

        if (!data.isEmpty())
        {
            emit dataReceived(data);
        }
    }
}

////////////////////////////////////////////////////////
/// Send
////////////////////////////////////////////////////////

bool EthernetDriver::send(
        const QByteArray& data)
{
    if (!m_connected)
        return false;

    return m_socket->write(data) != -1;
}

////////////////////////////////////////////////////////
/// Heartbeat
////////////////////////////////////////////////////////

void EthernetDriver::sendHeartbeat()
{
    if (!m_connected)
        return;

    //////////////////////////////////////////////////////
    /// TODO
    /// Replace with Keyence heartbeat command
    //////////////////////////////////////////////////////

    m_socket->write("\r");
}

////////////////////////////////////////////////////////
/// Reconnect
////////////////////////////////////////////////////////

void EthernetDriver::reconnect()
{
    if (m_connected)
        return;

    qDebug() << "[Ethernet] Reconnecting...";

    connectDriver();
}

////////////////////////////////////////////////////////
/// Socket Error
////////////////////////////////////////////////////////

void EthernetDriver::onSocketError(
        QAbstractSocket::SocketError)
{
    qDebug() << "***** TCP ERROR *****";
    qDebug() << m_socket->errorString();

    m_connected = false;

    emit errorOccurred(
                m_socket->errorString());
}
////////////////////////////////////////////////////////
/// Information
////////////////////////////////////////////////////////

bool EthernetDriver::isConnected() const
{
    return m_connected;
}

QString EthernetDriver::ipAddress() const
{
    return m_ipAddress;
}

quint16 EthernetDriver::port() const
{
    return m_port;
}

}