#include "ScannerConfiguration.h"

namespace PharmaTrack
{

////////////////////////////////////////////////////////
/// Constructor
////////////////////////////////////////////////////////

ScannerConfiguration::ScannerConfiguration()
{
}

////////////////////////////////////////////////////////
/// Communication
////////////////////////////////////////////////////////

ScannerConnectionType
ScannerConfiguration::connectionType() const
{
    return m_connectionType;
}

QString ScannerConfiguration::ipAddress() const
{
    return m_ipAddress;
}

quint16 ScannerConfiguration::port() const
{
    return m_port;
}

QString ScannerConfiguration::comPort() const
{
    return m_comPort;
}

////////////////////////////////////////////////////////
/// Network
////////////////////////////////////////////////////////

int ScannerConfiguration::timeout() const
{
    return m_timeout;
}

int ScannerConfiguration::reconnectInterval() const
{
    return m_reconnectInterval;
}

int ScannerConfiguration::heartbeatInterval() const
{
    return m_heartbeatInterval;
}

////////////////////////////////////////////////////////
/// Features
////////////////////////////////////////////////////////

bool ScannerConfiguration::autoConnect() const
{
    return m_autoConnect;
}

bool ScannerConfiguration::livePreviewEnabled() const
{
    return m_livePreviewEnabled;
}

bool ScannerConfiguration::sdkEnabled() const
{
    return m_sdkEnabled;
}

////////////////////////////////////////////////////////
/// Setters
////////////////////////////////////////////////////////

void ScannerConfiguration::setConnectionType(
        ScannerConnectionType type)
{
    m_connectionType = type;
}

void ScannerConfiguration::setIpAddress(
        const QString& ip)
{
    m_ipAddress = ip;
}

void ScannerConfiguration::setPort(
        quint16 port)
{
    m_port = port;
}

void ScannerConfiguration::setComPort(
        const QString& port)
{
    m_comPort = port;
}

void ScannerConfiguration::setTimeout(
        int timeout)
{
    m_timeout = timeout;
}

void ScannerConfiguration::setReconnectInterval(
        int interval)
{
    m_reconnectInterval = interval;
}

void ScannerConfiguration::setHeartbeatInterval(
        int interval)
{
    m_heartbeatInterval = interval;
}

void ScannerConfiguration::setAutoConnect(
        bool enabled)
{
    m_autoConnect = enabled;
}

void ScannerConfiguration::setLivePreviewEnabled(
        bool enabled)
{
    m_livePreviewEnabled = enabled;
}

void ScannerConfiguration::setSdkEnabled(
        bool enabled)
{
    m_sdkEnabled = enabled;
}

}