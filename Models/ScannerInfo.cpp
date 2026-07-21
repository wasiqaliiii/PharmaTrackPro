#include "ScannerInfo.h"

namespace PharmaTrack
{
    namespace
{
int endpointPriority(ScannerConnectionType type)
{
    switch (type)
    {
    case ScannerConnectionType::SDK:
        return 100;

    case ScannerConnectionType::Ethernet:
        return 90;

    case ScannerConnectionType::USB:
        return 70;

    case ScannerConnectionType::Serial:
        return 50;

    default:
        return 0;
    }
}
}

////////////////////////////////////////////////////////
/// Constructor
////////////////////////////////////////////////////////

ScannerInfo::ScannerInfo()
{
}

////////////////////////////////////////////////////////
/// General
////////////////////////////////////////////////////////

QString ScannerInfo::displayName() const
{
    return m_displayName;
}

QString ScannerInfo::manufacturer() const
{
    return m_manufacturer;
}

QString ScannerInfo::model() const
{
    return m_model;
}

QString ScannerInfo::description() const
{
    return m_description;
}

QString ScannerInfo::serialNumber() const
{
    return m_serialNumber;
}

////////////////////////////////////////////////////////
/// Capabilities
////////////////////////////////////////////////////////

bool ScannerInfo::sdkSupported() const
{
    return m_sdkSupported;
}

bool ScannerInfo::livePreviewSupported() const
{
    return m_livePreviewSupported;
}

bool ScannerInfo::configurationSupported() const
{
    return m_configurationSupported;
}

////////////////////////////////////////////////////////
/// State
////////////////////////////////////////////////////////

bool ScannerInfo::connected() const
{
    return m_connected;
}

bool ScannerInfo::configured() const
{
    return m_configured;
}

bool ScannerInfo::communicating() const
{
    return m_communicating;
}

bool ScannerInfo::verified() const
{
    return m_verified;
}

QString ScannerInfo::state() const
{
    return m_state;
}

QString ScannerInfo::lastError() const
{
    return m_lastError;
}

QDateTime ScannerInfo::lastScanTime() const
{
    return m_lastScanTime;
}

////////////////////////////////////////////////////////
/// Endpoints
////////////////////////////////////////////////////////

QList<ScannerEndpoint> ScannerInfo::endpoints() const
{
    return m_endpoints;
}

ScannerEndpoint ScannerInfo::preferredEndpoint() const
{
    ScannerEndpoint best;

    int highestPriority = -1;

    for (const ScannerEndpoint& endpoint : m_endpoints)
    {
        if (!endpoint.available)
            continue;

        if (endpoint.priority > highestPriority)
        {
            highestPriority = endpoint.priority;
            best = endpoint;
        }
    }

    return best;
}

////////////////////////////////////////////////////////
/// Setters
////////////////////////////////////////////////////////

void ScannerInfo::setDisplayName(const QString& value)
{
    m_displayName = value;
}

void ScannerInfo::setManufacturer(const QString& value)
{
    m_manufacturer = value;
}

void ScannerInfo::setModel(const QString& value)
{
    m_model = value;
}

void ScannerInfo::setDescription(const QString& value)
{
    m_description = value;
}

void ScannerInfo::setSerialNumber(const QString& value)
{
    m_serialNumber = value;
}

void ScannerInfo::setSdkSupported(bool value)
{
    m_sdkSupported = value;
}

void ScannerInfo::setLivePreviewSupported(bool value)
{
    m_livePreviewSupported = value;
}

void ScannerInfo::setConfigurationSupported(bool value)
{
    m_configurationSupported = value;
}

void ScannerInfo::setConnected(bool value)
{
    m_connected = value;
}

void ScannerInfo::setConfigured(bool value)
{
    m_configured = value;
}

void ScannerInfo::setCommunicating(bool value)
{
    m_communicating = value;
}

void ScannerInfo::setVerified(bool value)
{
    m_verified = value;
}

void ScannerInfo::setState(const QString& value)
{
    m_state = value;
}

void ScannerInfo::setLastError(const QString& value)
{
    m_lastError = value;
}

void ScannerInfo::setLastScanTime(const QDateTime& value)
{
    m_lastScanTime = value;
}

////////////////////////////////////////////////////////
/// Endpoints
////////////////////////////////////////////////////////

////////////////////////////////////////////////////////
/// Endpoints
////////////////////////////////////////////////////////

void ScannerInfo::addEndpoint(
        const ScannerEndpoint& endpoint)
{
    ScannerEndpoint newEndpoint = endpoint;

    newEndpoint.priority =
            endpointPriority(newEndpoint.type);

    m_endpoints.append(newEndpoint);
}

void ScannerInfo::clearEndpoints()
{
    m_endpoints.clear();
}

}