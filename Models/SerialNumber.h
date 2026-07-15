#pragma once

#include <QString>
#include <QDateTime>

namespace PharmaTrack
{

enum class SerialStatus
{
    NotScanned,
    Valid,
    Invalid,
    Duplicate
};

class SerialNumber
{
public:

    SerialNumber();

    explicit SerialNumber(const QString& serialNumber);

    // Getters

    QString serialNumber() const;

    QString batchNumber() const;

    QString productCode() const;

    bool isScanned() const;

    SerialStatus status() const;

    const QDateTime& scanTime() const;

    // Setters

    void setSerialNumber(const QString& serialNumber);

    void setBatchNumber(const QString& batchNumber);

    void setProductCode(const QString& productCode);

    void setScanned(bool scanned);

    void setStatus(SerialStatus status);

    void setScanTime(const QDateTime& scanTime);

    // Helper

    void markScanned(SerialStatus status);

private:

    QString m_serialNumber;

    QString m_batchNumber;

    QString m_productCode;

    bool m_scanned;

    SerialStatus m_status;

    QDateTime m_scanTime;
};

}