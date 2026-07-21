#pragma once

#include "ScannerDriver.h"

#include <QTcpSocket>
#include <QTimer>

namespace PharmaTrack
{

class EthernetDriver : public ScannerDriver
{
    Q_OBJECT

public:

    explicit EthernetDriver(
            QObject* parent = nullptr);

    ~EthernetDriver() override;

    //////////////////////////////////////////////////////
    /// Scanner Driver
    //////////////////////////////////////////////////////

    bool connectDriver() override;

    void disconnectDriver() override;

    bool isConnected() const override;

    bool send(
            const QByteArray& data) override;

    //////////////////////////////////////////////////////
    /// Ethernet
    //////////////////////////////////////////////////////

    void connectToScanner(
            const QString& ipAddress,
            quint16 port);

    QString ipAddress() const;

    quint16 port() const;

private slots:

    //////////////////////////////////////////////////////
    /// Socket
    //////////////////////////////////////////////////////

    void onConnected();

    void onDisconnected();

    void onReadyRead();

    void onSocketError(
            QAbstractSocket::SocketError error);

    //////////////////////////////////////////////////////
    /// Maintenance
    //////////////////////////////////////////////////////

    void sendHeartbeat();

    void reconnect();

private:

    //////////////////////////////////////////////////////
    /// Socket
    //////////////////////////////////////////////////////

    QTcpSocket* m_socket = nullptr;

    //////////////////////////////////////////////////////
    /// Timers
    //////////////////////////////////////////////////////

    QTimer* m_heartbeatTimer = nullptr;

    QTimer* m_reconnectTimer = nullptr;

    //////////////////////////////////////////////////////
    /// Connection
    //////////////////////////////////////////////////////

    QString m_ipAddress;

    quint16 m_port = 0;

    bool m_connected = false;
};

}