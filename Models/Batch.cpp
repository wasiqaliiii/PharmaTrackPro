#include "Batch.h"

namespace PharmaTrack
{

Batch::Batch()
    : m_quantity(0),
      m_serialLength(15),
      m_generatedCount(0)
{
}

QString Batch::batchNumber() const
{
    return m_batchNumber;
}

void Batch::setBatchNumber(const QString &batchNumber)
{
    m_batchNumber = batchNumber.trimmed();
}

QString Batch::productName() const
{
    return m_productName;
}

void Batch::setProductName(const QString &productName)
{
    m_productName = productName.trimmed();
}

int Batch::quantity() const
{
    return m_quantity;
}

void Batch::setQuantity(int quantity)
{
    m_quantity = quantity;
}

QString Batch::prefix() const
{
    return m_prefix;
}

void Batch::setPrefix(const QString &prefix)
{
    m_prefix = prefix.trimmed().toUpper();
}

int Batch::serialLength() const
{
    return m_serialLength;
}

void Batch::setSerialLength(int length)
{
    m_serialLength = length;
}

int Batch::generatedCount() const
{
    return m_generatedCount;
}

void Batch::setGeneratedCount(int count)
{
    m_generatedCount = count;
}

QDateTime Batch::generatedAt() const
{
    return m_generatedAt;
}

void Batch::setGeneratedAt(const QDateTime &dateTime)
{
    m_generatedAt = dateTime;
}

}