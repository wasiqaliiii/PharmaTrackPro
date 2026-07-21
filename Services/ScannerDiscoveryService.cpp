#include "ScannerDiscoveryService.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>

namespace PharmaTrack
{

////////////////////////////////////////////////////////
/// Constructor
////////////////////////////////////////////////////////

ScannerDiscoveryService::ScannerDiscoveryService(
        QObject* parent)
    : QObject(parent),
      m_discoveryTimer(new QTimer(this))
{
    //////////////////////////////////////////////////////
    /// Discovery Timer
    //////////////////////////////////////////////////////

    m_discoveryTimer->setInterval(10);

    connect(m_discoveryTimer,
            &QTimer::timeout,
            this,
            &ScannerDiscoveryService::discoverNext);
}

////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////

ScannerDiscoveryService::~ScannerDiscoveryService()
{
    stopDiscovery();
}

////////////////////////////////////////////////////////
/// Start Discovery
////////////////////////////////////////////////////////

void ScannerDiscoveryService::startDiscovery(
        const QHostAddress& subnetAddress,
        int prefixLength,
        quint16 scannerPort)
{
    if (m_discovering)
    {
        return;
    }

    clearResults();

    m_subnetAddress = subnetAddress;
    m_prefixLength = prefixLength;
    m_scannerPort = scannerPort;

    //////////////////////////////////////////////////////
    /// Calculate Address Range
    //////////////////////////////////////////////////////

    quint32 subnet =
            ipToUInt(subnetAddress);

    quint32 mask =
            prefixLength == 0
            ? 0
            : (0xFFFFFFFF << (32 - prefixLength));

    m_startAddress =
            subnet & mask;

    m_endAddress =
            m_startAddress | (~mask);

    //////////////////////////////////////////////////////
    /// Skip Network Address
    //////////////////////////////////////////////////////

    ++m_startAddress;

    //////////////////////////////////////////////////////
    /// Skip Broadcast Address
    //////////////////////////////////////////////////////

    --m_endAddress;

    m_currentAddress =
            m_startAddress;

    m_discovering = true;

    emit discoveryStarted();

    qDebug()
            << "[ScannerDiscovery] Started";
    
    m_discoveryTimer->start();
}

////////////////////////////////////////////////////////
/// Stop Discovery
////////////////////////////////////////////////////////

void ScannerDiscoveryService::stopDiscovery()
{
    if (!m_discovering)
    {
        return;
    }

    m_discoveryTimer->stop();

    m_discovering = false;

    emit discoveryFinished();

    qDebug()
            << "[ScannerDiscovery] Finished";
}

////////////////////////////////////////////////////////
/// Discovering
////////////////////////////////////////////////////////

bool ScannerDiscoveryService::isDiscovering() const
{
    return m_discovering;
}

////////////////////////////////////////////////////////
/// Results
////////////////////////////////////////////////////////

const QList<ScannerInfo>&
ScannerDiscoveryService::discoveredScanners() const
{
    return m_scanners;
}

////////////////////////////////////////////////////////
/// Discover Next
////////////////////////////////////////////////////////

void ScannerDiscoveryService::discoverNext()
{
    if (!m_discovering)
    {
        return;
    }

    //////////////////////////////////////////////////////
    /// Finished
    //////////////////////////////////////////////////////

    if (m_currentAddress > m_endAddress)
    {
        stopDiscovery();
        return;
    }

    //////////////////////////////////////////////////////
    /// Current Address
    //////////////////////////////////////////////////////

    QHostAddress address =
            uintToIp(m_currentAddress);

    //////////////////////////////////////////////////////
    /// Progress
    //////////////////////////////////////////////////////

    int total =
            static_cast<int>(
                m_endAddress - m_startAddress + 1);

    int current =
            static_cast<int>(
                m_currentAddress - m_startAddress + 1);

    emit progressChanged(
                current,
                total);

    //////////////////////////////////////////////////////
    /// Check Scanner
    //////////////////////////////////////////////////////

    if (isScannerAvailable(address))
    {
        ScannerInfo scanner;

//////////////////////////////////////////////////
/// Basic Information
//////////////////////////////////////////////////

scanner.setDisplayName(
            QString("Scanner %1")
            .arg(m_scanners.count() + 1));

scanner.setManufacturer(
            "Unknown");

scanner.setModel(
            "Ethernet Scanner");

scanner.setConnected(
            false);

scanner.setConfigured(
            false);

scanner.setCommunicating(
            true);

scanner.setVerified(
            true);

scanner.setState(
            "Discovered");

//////////////////////////////////////////////////
/// Endpoint
//////////////////////////////////////////////////

ScannerEndpoint endpoint;

endpoint.type =
        ScannerConnectionType::Ethernet;

endpoint.ipAddress =
        address.toString();

endpoint.port =
        m_scannerPort;

endpoint.available =
        true;

endpoint.priority =
        100;

scanner.addEndpoint(
            endpoint);

        addScanner(scanner);

        emit scannerDiscovered(scanner);

        qDebug()
                << "[ScannerDiscovery] Scanner Found:"
                << address.toString();
    }

    ++m_currentAddress;
}

////////////////////////////////////////////////////////
/// Scanner Available
////////////////////////////////////////////////////////

bool ScannerDiscoveryService::isScannerAvailable(
        const QHostAddress& address)
{
    QTcpSocket socket;

    socket.connectToHost(
                address,
                m_scannerPort);

    if (!socket.waitForConnected(250))
    {
        return false;
    }

    socket.disconnectFromHost();

    return true;
}
////////////////////////////////////////////////////////
/// Clear Results
////////////////////////////////////////////////////////

void ScannerDiscoveryService::clearResults()
{
    m_scanners.clear();
}

////////////////////////////////////////////////////////
/// Add Scanner
////////////////////////////////////////////////////////

void ScannerDiscoveryService::addScanner(
        const ScannerInfo& scanner)
{
    //////////////////////////////////////////////////////
    /// Prevent Duplicate Entries
    //////////////////////////////////////////////////////

    for (const ScannerInfo& item : m_scanners)
    {
        ScannerEndpoint existing =
        item.preferredEndpoint();

ScannerEndpoint incoming =
        scanner.preferredEndpoint();

if (existing.ipAddress ==
        incoming.ipAddress)
{
    return;
}
    }

    m_scanners.append(scanner);
}

////////////////////////////////////////////////////////
/// IP Address -> Integer
////////////////////////////////////////////////////////

quint32 ScannerDiscoveryService::ipToUInt(
        const QHostAddress& address) const
{
    return address.toIPv4Address();
}

////////////////////////////////////////////////////////
/// Integer -> IP Address
////////////////////////////////////////////////////////

QHostAddress ScannerDiscoveryService::uintToIp(
        quint32 value) const
{
    return QHostAddress(value);
}

} // namespace PharmaTrack