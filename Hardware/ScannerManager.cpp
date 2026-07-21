#include "ScannerManager.h"

#include <QDebug>

namespace PharmaTrack
{

////////////////////////////////////////////////////////
/// Constructor
////////////////////////////////////////////////////////

ScannerManager::ScannerManager(QObject* parent)
    : QObject(parent),
      m_ethernetDriver(new EthernetDriver(this)),
      m_serialDriver(new SerialDriver(this)),
      m_activeDriver(nullptr)
{
}

////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////

ScannerManager::~ScannerManager()
{
    disconnectScanner();
}

////////////////////////////////////////////////////////
/// Connect Scanner
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
/// Connect Scanner
////////////////////////////////////////////////////////

bool ScannerManager::connectScanner(
        const QString& ipAddress,
        quint16 port)
{
    //////////////////////////////////////////////////////
    /// Disconnect Current Driver
    //////////////////////////////////////////////////////

    disconnectScanner();

    //////////////////////////////////////////////////////
    /// Configure Ethernet Driver
    //////////////////////////////////////////////////////

    m_ethernetDriver->connectToScanner(
                ipAddress,
                port);

    m_activeDriver = m_ethernetDriver;

    connectDriverSignals();

    if (m_activeDriver->connectDriver())
    {
       static int count = 0;

qDebug() << "[ScannerManager] connectScanner called:"
         << ++count
         << ipAddress
         << port;
        return true;
    }

    //////////////////////////////////////////////////////
    /// Ethernet Failed
    //////////////////////////////////////////////////////

    m_activeDriver->disconnectDriver();

    disconnectDriverSignals();

    m_activeDriver = nullptr;

    //////////////////////////////////////////////////////
    /// Try Serial Driver
    //////////////////////////////////////////////////////

    m_activeDriver = m_serialDriver;

    connectDriverSignals();

    if (m_activeDriver->connectDriver())
    {
        qDebug()
                << "[ScannerManager]"
                << "Serial Scanner Connected";

        return true;
    }

    //////////////////////////////////////////////////////
    /// Serial Failed
    //////////////////////////////////////////////////////

    m_activeDriver->disconnectDriver();

    disconnectDriverSignals();

    m_activeDriver = nullptr;

    qDebug()
            << "[ScannerManager]"
            << "No scanner available.";

    return false;
}
////////////////////////////////////////////////////////
/// Disconnect Scanner
////////////////////////////////////////////////////////

void ScannerManager::disconnectScanner()
{
    if (!m_activeDriver)
    {
        return;
    }

    disconnectDriverSignals();

    m_activeDriver->disconnectDriver();

    m_activeDriver = nullptr;
}

////////////////////////////////////////////////////////
/// Connected
////////////////////////////////////////////////////////

bool ScannerManager::isConnected() const
{
    if (!m_activeDriver)
    {
        return false;
    }

    return m_activeDriver->isConnected();
}

////////////////////////////////////////////////////////
/// Send
////////////////////////////////////////////////////////

bool ScannerManager::send(
        const QByteArray& data)
{
    if (!m_activeDriver)
    {
        return false;
    }

    return m_activeDriver->send(data);
}

////////////////////////////////////////////////////////
/// Active Driver
////////////////////////////////////////////////////////

ScannerDriver*
ScannerManager::activeDriver() const
{
    return m_activeDriver;
}

////////////////////////////////////////////////////////
/// Connect Driver Signals
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
/// Connect Driver Signals
////////////////////////////////////////////////////////

void ScannerManager::connectDriverSignals()
{
    if (!m_activeDriver)
    {
        return;
    }

    connect(m_activeDriver,
            &ScannerDriver::connected,
            this,
            &ScannerManager::onConnected,
            Qt::UniqueConnection);

    connect(m_activeDriver,
            &ScannerDriver::disconnected,
            this,
            &ScannerManager::onDisconnected,
            Qt::UniqueConnection);

    connect(m_activeDriver,
            &ScannerDriver::connectionLost,
            this,
            &ScannerManager::onConnectionLost,
            Qt::UniqueConnection);

    connect(m_activeDriver,
            &ScannerDriver::dataReceived,
            this,
            &ScannerManager::onDataReceived,
            Qt::UniqueConnection);

    connect(m_activeDriver,
            &ScannerDriver::errorOccurred,
            this,
            &ScannerManager::onErrorOccurred,
            Qt::UniqueConnection);
}
////////////////////////////////////////////////////////
/// Disconnect Driver Signals
////////////////////////////////////////////////////////

void ScannerManager::disconnectDriverSignals()
{
    if (!m_activeDriver)
    {
        return;
    }

    disconnect(m_activeDriver,
               nullptr,
               this,
               nullptr);
}

////////////////////////////////////////////////////////
/// Connected
////////////////////////////////////////////////////////

void ScannerManager::onConnected()
{
    qDebug()
            << "[ScannerManager] Connected";

    emit connected();
}

////////////////////////////////////////////////////////
/// Disconnected
////////////////////////////////////////////////////////

void ScannerManager::onDisconnected()
{
    qDebug()
            << "[ScannerManager] Disconnected";

    emit disconnected();
}

////////////////////////////////////////////////////////
/// Connection Lost
////////////////////////////////////////////////////////

void ScannerManager::onConnectionLost()
{
    qDebug()
            << "[ScannerManager] Connection Lost";

    emit connectionLost();
}

////////////////////////////////////////////////////////
/// Data Received
////////////////////////////////////////////////////////

void ScannerManager::onDataReceived(
        const QByteArray& data)
{
    //////////////////////////////////////////////////////
    /// Forward Raw Scanner Data
    //////////////////////////////////////////////////////

    emit dataReceived(data);
}

////////////////////////////////////////////////////////
/// Error
////////////////////////////////////////////////////////

void ScannerManager::onErrorOccurred(
        const QString& error)
{
    qDebug()
            << "[ScannerManager]"
            << error;

    emit errorOccurred(error);
}

} // namespace PharmaTrack



