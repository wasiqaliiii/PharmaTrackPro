#pragma once

#include <QString>
#include <QDateTime>
#include <QList>

namespace PharmaTrack
{

////////////////////////////////////////////////////////
/// Connection Type
////////////////////////////////////////////////////////

enum class ScannerConnectionType
{
    Unknown,

    SDK,

    Ethernet,

    USB,

    Serial
};

////////////////////////////////////////////////////////
/// Endpoint
////////////////////////////////////////////////////////

class ScannerEndpoint
{
public:

    ScannerConnectionType type =
            ScannerConnectionType::Unknown;

    QString ipAddress;

    quint16 port = 0;

    QString comPort;

    bool available = false;

    int priority = 0;
};

////////////////////////////////////////////////////////
/// Scanner Information
////////////////////////////////////////////////////////

class ScannerInfo
{
public:

    ScannerInfo();

    //////////////////////////////////////////////////////
    /// General
    //////////////////////////////////////////////////////

    QString displayName() const;
    QString manufacturer() const;
    QString model() const;
    QString description() const;
    QString serialNumber() const;

    //////////////////////////////////////////////////////
    /// Capabilities
    //////////////////////////////////////////////////////

    bool sdkSupported() const;
    bool livePreviewSupported() const;
    bool configurationSupported() const;

    //////////////////////////////////////////////////////
    /// State
    //////////////////////////////////////////////////////

    bool connected() const;
    bool configured() const;
    bool communicating() const;
    bool verified() const;

    QString state() const;

    QString lastError() const;

    QDateTime lastScanTime() const;

    //////////////////////////////////////////////////////
    /// Endpoints
    //////////////////////////////////////////////////////

    QList<ScannerEndpoint> endpoints() const;

    ScannerEndpoint preferredEndpoint() const;

    //////////////////////////////////////////////////////
    /// Setters
    //////////////////////////////////////////////////////

    void setDisplayName(const QString&);
    void setManufacturer(const QString&);
    void setModel(const QString&);
    void setDescription(const QString&);
    void setSerialNumber(const QString&);

    void setSdkSupported(bool);
    void setLivePreviewSupported(bool);
    void setConfigurationSupported(bool);

    void setConnected(bool);
    void setConfigured(bool);
    void setCommunicating(bool);
    void setVerified(bool);

    void setState(const QString&);

    void setLastError(const QString&);

    void setLastScanTime(const QDateTime&);

    void addEndpoint(
            const ScannerEndpoint& endpoint);

    void clearEndpoints();

private:

    QString m_displayName;

    QString m_manufacturer;

    QString m_model;

    QString m_description;

    QString m_serialNumber;

    bool m_sdkSupported = false;

    bool m_livePreviewSupported = false;

    bool m_configurationSupported = false;

    bool m_connected = false;

    bool m_configured = false;

    bool m_communicating = false;

    bool m_verified = false;

    QString m_state;

    QString m_lastError;

    QDateTime m_lastScanTime;

    QList<ScannerEndpoint> m_endpoints;
};

}