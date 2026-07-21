#ifndef PHARMATRACK_SERIALNUMBER_H
#define PHARMATRACK_SERIALNUMBER_H

#include <QString>
#include <QDateTime>

namespace PharmaTrack
{
enum class SerialStatus
{
    Pending,
    Valid,
    Duplicate,
    Invalid
};
class SerialNumber
{
public:
    SerialNumber();
SerialNumber(const QString &serial);
    QString serial() const;
    void setSerial(const QString &serial);

    QString batchNumber() const;
    void setBatchNumber(const QString &batchNumber);

    QString productName() const;
    void setProductName(const QString &productName);

    QString prefix() const;
    void setPrefix(const QString &prefix);

    int serialLength() const;
    void setSerialLength(int length);

    QDateTime generatedAt() const;
    void setGeneratedAt(const QDateTime &dateTime);
    bool isScanned() const;

void markScanned(SerialStatus status);

SerialStatus status() const;

private:
    QString m_serial;
    QString m_batchNumber;
    QString m_productName;
    QString m_prefix;
    int m_serialLength;
    QDateTime m_generatedAt;
    bool m_scanned;

SerialStatus m_status;
};

}

#endif // PHARMATRACK_SERIALNUMBER_H