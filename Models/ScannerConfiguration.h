#pragma once

#include <QString>

#include "ScannerInfo.h"

namespace PharmaTrack
{

class ScannerConfiguration
{
public:

    ScannerConfiguration();

    //////////////////////////////////////////////////////
    /// Communication
    //////////////////////////////////////////////////////

    ScannerConnectionType connectionType() const;

    QString ipAddress() const;

    quint16 port() const;

    QString comPort() const;

    //////////////////////////////////////////////////////
    /// Network
    //////////////////////////////////////////////////////

    int timeout() const;

    int reconnectInterval() const;

    int heartbeatInterval() const;

    //////////////////////////////////////////////////////
    /// Features
    //////////////////////////////////////////////////////

    bool autoConnect() const;

    bool livePreviewEnabled() const;

    bool sdkEnabled() const;

    //////////////////////////////////////////////////////
    /// Setters
    //////////////////////////////////////////////////////

    void setConnectionType(
            ScannerConnectionType type);

    void setIpAddress(
            const QString& ip);

    void setPort(
            quint16 port);

    void setComPort(
            const QString& port);

    void setTimeout(
            int timeout);

    void setReconnectInterval(
            int interval);

    void setHeartbeatInterval(
            int interval);

    void setAutoConnect(
            bool enabled);

    void setLivePreviewEnabled(
            bool enabled);

    void setSdkEnabled(
            bool enabled);

private:

    //////////////////////////////////////////////////////
    /// Communication
    //////////////////////////////////////////////////////

    ScannerConnectionType m_connectionType =
            ScannerConnectionType::Unknown;

    QString m_ipAddress;

    quint16 m_port = 0;

    QString m_comPort;

    //////////////////////////////////////////////////////
    /// Network
    //////////////////////////////////////////////////////

    int m_timeout = 3000;

    int m_reconnectInterval = 1000;

    int m_heartbeatInterval = 1000;

    //////////////////////////////////////////////////////
    /// Features
    //////////////////////////////////////////////////////

    bool m_autoConnect = true;

    bool m_livePreviewEnabled = true;

    bool m_sdkEnabled = true;
};

}