#include "ScanLog.h"

namespace PharmaTrack
{

ScanLog::ScanLog()
    : m_result(ScanResult::Invalid),
      m_scanTime(QDateTime::currentDateTime())
{
}

ScanLog::ScanLog(const QString& serialNumber,
                 ScanResult result)
    : m_serialNumber(serialNumber),
      m_result(result),
      m_scanTime(QDateTime::currentDateTime())
{
}

QString ScanLog::serialNumber() const
{
    return m_serialNumber;
}
QString ScanLog::batchId() const
{
    return m_batchId;
}

QString ScanLog::operatorName() const
{
    return m_operatorName;
}

ScanResult ScanLog::result() const
{
    return m_result;
}

QDateTime ScanLog::scanTime() const
{
    return m_scanTime;
}

void ScanLog::setSerialNumber(const QString& serialNumber)
{
    m_serialNumber = serialNumber;
}
void ScanLog::setBatchId(const QString& batchId)
{
    m_batchId = batchId;
}

void ScanLog::setOperatorName(const QString& operatorName)
{
    m_operatorName = operatorName;
}
void ScanLog::setResult(ScanResult result)
{
    m_result = result;
}

void ScanLog::setScanTime(const QDateTime& scanTime)
{
    m_scanTime = scanTime;
}

}