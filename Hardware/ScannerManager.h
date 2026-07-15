#pragma once

#include <QObject>
#include "SerialPortManager.h"

namespace PharmaTrack
{

class ScannerManager : public QObject
{
    Q_OBJECT

public:
    explicit ScannerManager(QObject* parent = nullptr);

    QStringList availablePorts() const;
    bool isConnected() const;
    bool connectScanner(const QString& port);

    void disconnectScanner();

signals:
    void qrScanned(const QString& qr);
    void connected();
    void disconnected();
    void errorOccurred(const QString& error);

private slots:
    void processIncomingData(const QByteArray& data);

private:
    SerialPortManager m_serialManager;
};

}