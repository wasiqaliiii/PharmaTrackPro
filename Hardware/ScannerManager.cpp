#include "ScannerManager.h"
#include <QDebug>
namespace PharmaTrack
{

ScannerManager::ScannerManager(QObject* parent)
    : QObject(parent)
{
    connect(&m_serialManager,
            &SerialPortManager::dataReceived,
            this,
            &ScannerManager::processIncomingData);

    connect(&m_serialManager,
            &SerialPortManager::connected,
            this,
            &ScannerManager::connected);

    connect(&m_serialManager,
            &SerialPortManager::disconnected,
            this,
            &ScannerManager::disconnected);

    connect(&m_serialManager,
            &SerialPortManager::errorOccurred,
            this,
            &ScannerManager::errorOccurred);
}

QStringList ScannerManager::availablePorts() const
{
    return m_serialManager.availablePorts();
}

bool ScannerManager::connectScanner(const QString& port)
{
    return m_serialManager.openPort(port);
}

void ScannerManager::disconnectScanner()
{
    m_serialManager.closePort();
}

void ScannerManager::processIncomingData(const QByteArray& data)
{
    qDebug() << "Raw Data:" << data;

    QString qr = QString::fromUtf8(data).trimmed();

    qDebug() << "QR Code:" << qr;

    if (!qr.isEmpty())
        emit qrScanned(qr);
}
bool ScannerManager::isConnected() const
{
    return m_serialManager.isConnected();
}
}