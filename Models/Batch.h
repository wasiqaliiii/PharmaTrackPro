#ifndef PHARMATRACK_BATCH_H
#define PHARMATRACK_BATCH_H

#include <QString>
#include <QDateTime>

namespace PharmaTrack
{

class Batch
{
public:
    Batch();

    QString batchNumber() const;
    void setBatchNumber(const QString &batchNumber);

    QString productName() const;
    void setProductName(const QString &productName);

    int quantity() const;
    void setQuantity(int quantity);

    QString prefix() const;
    void setPrefix(const QString &prefix);

    int serialLength() const;
    void setSerialLength(int length);

    int generatedCount() const;
    void setGeneratedCount(int count);

    QDateTime generatedAt() const;
    void setGeneratedAt(const QDateTime &dateTime);

private:
    QString m_batchNumber;
    QString m_productName;
    int m_quantity;
    QString m_prefix;
    int m_serialLength;
    int m_generatedCount;
    QDateTime m_generatedAt;
};

}

#endif // PHARMATRACK_BATCH_H