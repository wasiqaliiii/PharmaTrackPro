#pragma once

#include <QString>
#include <QDateTime>

namespace PharmaTrack
{

enum class ScanResult
{
    Valid,
    Invalid,
    Duplicate
};

class ScanLog
{
public:

    ScanLog();

    ScanLog(const QString& serialNumber,
            ScanResult result);

    QString serialNumber() const;

QString batchId() const;

QString operatorName() const;

ScanResult result() const;

QDateTime scanTime() const;

    void setSerialNumber(const QString& serialNumber);

void setBatchId(const QString& batchId);

void setOperatorName(const QString& operatorName);

void setResult(ScanResult result);

void setScanTime(const QDateTime& scanTime);

private:

    QString m_serialNumber;

    QString m_batchId;

    QString m_operatorName;

    ScanResult m_result;

    QDateTime m_scanTime;
};

}