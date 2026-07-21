#include "SerialNumber.h"

namespace PharmaTrack
{

SerialNumber::SerialNumber()
    : m_serialLength(0),
      m_scanned(false),
      m_status(SerialStatus::Pending)
{
}

SerialNumber::SerialNumber(const QString &serial)
    : m_serial(serial),
      m_serialLength(0),
      m_scanned(false),
      m_status(SerialStatus::Pending)
{
}

QString SerialNumber::serial() const
{
    return m_serial;
}

void SerialNumber::setSerial(const QString &serial)
{
    m_serial = serial.toUpper().trimmed();
}

QString SerialNumber::batchNumber() const
{
    return m_batchNumber;
}

void SerialNumber::setBatchNumber(const QString &batchNumber)
{
    m_batchNumber = batchNumber.trimmed();
}

QString SerialNumber::productName() const
{
    return m_productName;
}

void SerialNumber::setProductName(const QString &productName)
{
    m_productName = productName.trimmed();
}

QString SerialNumber::prefix() const
{
    return m_prefix;
}

void SerialNumber::setPrefix(const QString &prefix)
{
    m_prefix = prefix.toUpper().trimmed();
}

int SerialNumber::serialLength() const
{
    return m_serialLength;
}

void SerialNumber::setSerialLength(int length)
{
    m_serialLength = length;
}

QDateTime SerialNumber::generatedAt() const
{
    return m_generatedAt;
}

void SerialNumber::setGeneratedAt(const QDateTime &dateTime)
{
    m_generatedAt = dateTime;
}
bool SerialNumber::isScanned() const
{
    return m_scanned;
}

void SerialNumber::markScanned(SerialStatus status)
{
    m_scanned = true;
    m_status = status;
}

SerialStatus SerialNumber::status() const
{
    return m_status;
}


}