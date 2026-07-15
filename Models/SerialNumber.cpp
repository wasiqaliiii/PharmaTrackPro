#include "SerialNumber.h"

namespace PharmaTrack
{

SerialNumber::SerialNumber()
    : m_scanned(false),
      m_status(SerialStatus::NotScanned)
{
}

SerialNumber::SerialNumber(const QString& serialNumber)
    : m_serialNumber(serialNumber),
      m_scanned(false),
      m_status(SerialStatus::NotScanned)
{
}

QString SerialNumber::serialNumber() const
{
    return m_serialNumber;
}

QString SerialNumber::batchNumber() const
{
    return m_batchNumber;
}

QString SerialNumber::productCode() const
{
    return m_productCode;
}

bool SerialNumber::isScanned() const
{
    return m_scanned;
}

SerialStatus SerialNumber::status() const
{
    return m_status;
}

const QDateTime& SerialNumber::scanTime() const
{
    return m_scanTime;
}

void SerialNumber::setSerialNumber(const QString& serialNumber)
{
    m_serialNumber = serialNumber;
}

void SerialNumber::setBatchNumber(const QString& batchNumber)
{
    m_batchNumber = batchNumber;
}

void SerialNumber::setProductCode(const QString& productCode)
{
    m_productCode = productCode;
}

void SerialNumber::setScanned(bool scanned)
{
    m_scanned = scanned;
}

void SerialNumber::setStatus(SerialStatus status)
{
    m_status = status;
}

void SerialNumber::setScanTime(const QDateTime& scanTime)
{
    m_scanTime = scanTime;
}

void SerialNumber::markScanned(SerialStatus status)
{
    m_scanned = true;
    m_status = status;
    m_scanTime = QDateTime::currentDateTime();
}

}