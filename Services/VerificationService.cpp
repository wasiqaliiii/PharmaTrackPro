#include "VerificationService.h"

#include "../Utils/PathManager.h"

#include <QFile>
#include <QTextStream>

namespace PharmaTrack
{

VerificationService::VerificationService(QObject *parent)
    : QObject(parent),
      m_loaded(false),
      m_totalCodes(0),
      m_accepted(0),
      m_rejected(0),
      m_duplicates(0)
{
}
bool VerificationService::loadBatch(const QString& batchId)
{
    clearProduction();

    m_currentBatch = batchId;

    QString csvFile =
            PathManager::serialFile(batchId);

    if(!loadSerials(csvFile))
        return false;

    m_loaded = true;
    m_logs.clear();

    emit productionLoaded(
                batchId,
                m_totalCodes);

   updateStatistics();

    return true;
}
bool VerificationService::loadSerials(const QString& csvFile)
{
    QFile file(csvFile);

    if(!file.open(QIODevice::ReadOnly |
                  QIODevice::Text))
    {
        return false;
    }

    QTextStream stream(&file);

    bool headerSkipped = false;

    while(!stream.atEnd())
    {
        QString line = stream.readLine().trimmed();

        if(line.isEmpty())
            continue;

        if(!headerSkipped)
        {
            headerSkipped = true;
            continue;
        }

        QString serial =
                line.section(',',0,0).trimmed();

        if(serial.isEmpty())
            continue;

        SerialNumber number(serial);

        m_serials.insert(serial, number);
    }

    file.close();

    m_totalCodes = m_serials.size();

    return true;
}

ScanResult VerificationService::verifyCode(const QString& serialNumber)
{
    if(!m_loaded)
        return ScanResult::Invalid;

    //------------------------------------------
    // Not Found
    //------------------------------------------

    if(!m_serials.contains(serialNumber))
{
    m_rejected++;

    ScanLog log(
                serialNumber,
                ScanResult::Invalid);

    log.setBatchId(m_currentBatch);

    log.setOperatorName("Administrator");

    m_logs.append(log);

    emit codeVerified(log);

    updateStatistics();

    return ScanResult::Invalid;
}

    //------------------------------------------
    // Duplicate
    //------------------------------------------

    SerialNumber& serial =
            m_serials[serialNumber];

    if(serial.isScanned())
{
    m_duplicates++;

    ScanLog log(
                serialNumber,
                ScanResult::Duplicate);

    log.setBatchId(m_currentBatch);

    log.setOperatorName("Administrator");

    m_logs.append(log);

    emit codeVerified(log);

    updateStatistics();

    return ScanResult::Duplicate;
}

    //------------------------------------------
    // Valid
    //------------------------------------------

    serial.markScanned(SerialStatus::Valid);

    m_accepted++;

ScanLog log(
    serialNumber,
    ScanResult::Valid);

log.setBatchId(m_currentBatch);

log.setOperatorName("Administrator");

m_logs.append(log);

emit codeVerified(log);

    updateStatistics();

    return ScanResult::Valid;
}

void VerificationService::clearProduction()
{
    m_loaded = false;

    m_currentBatch.clear();

    m_serials.clear();

    m_logs.clear();

    m_totalCodes = 0;

    m_accepted = 0;

    m_rejected = 0;

    m_duplicates = 0;

    emit productionCleared();
}

bool VerificationService::isLoaded() const
{
    return m_loaded;
}

QString VerificationService::currentBatch() const
{
    return m_currentBatch;
}

int VerificationService::totalCodes() const
{
    return m_totalCodes;
}

int VerificationService::acceptedCount() const
{
    return m_accepted;
}

int VerificationService::rejectedCount() const
{
    return m_rejected;
}

int VerificationService::duplicateCount() const
{
    return m_duplicates;
}

int VerificationService::remainingCount() const
{
    return m_totalCodes - m_accepted;
}

const QVector<ScanLog>& VerificationService::logs() const
{
    return m_logs;
}
void VerificationService::updateStatistics()
{
    emit statisticsChanged(
                totalCodes(),
                acceptedCount(),
                rejectedCount(),
                duplicateCount(),
                remainingCount());
}
} 