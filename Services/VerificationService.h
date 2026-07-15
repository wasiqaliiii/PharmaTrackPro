#pragma once

#include <QObject>
#include <QHash>
#include <QVector>
#include <QString>

#include "../Models/SerialNumber.h"
#include "../Models/ScanLog.h"

namespace PharmaTrack
{

class VerificationService : public QObject
{
    Q_OBJECT

public:

    explicit VerificationService(QObject* parent = nullptr);

    //----------------------------------------------------
    // Production
    //----------------------------------------------------

    bool loadBatch(const QString& batchId);

    void clearProduction();

    bool isLoaded() const;

    QString currentBatch() const;

    //----------------------------------------------------
    // Verification
    //----------------------------------------------------

    ScanResult verifyCode(const QString& serialNumber);

    //----------------------------------------------------
    // Statistics
    //----------------------------------------------------

    int totalCodes() const;

    int acceptedCount() const;

    int rejectedCount() const;

    int duplicateCount() const;

    int remainingCount() const;

    //----------------------------------------------------
    // Logs
    //----------------------------------------------------

    const QVector<ScanLog>& logs() const;

signals:

    void productionLoaded(
            const QString& batchId,
            int totalCodes);

    void productionCleared();

    void codeVerified(
            const ScanLog& log);

    void statisticsChanged(
            int total,
            int accepted,
            int rejected,
            int duplicate,
            int remaining);

private:

    bool loadSerials(const QString& csvFile);

    void updateStatistics();

private:

    //----------------------------------------------------
    // Production
    //----------------------------------------------------

    QString m_currentBatch;

    bool m_loaded;

    //----------------------------------------------------
    // Serial Numbers
    //----------------------------------------------------

    QHash<QString, SerialNumber> m_serials;

    //----------------------------------------------------
    // Scan History
    //----------------------------------------------------

    QVector<ScanLog> m_logs;

    //----------------------------------------------------
    // Statistics
    //----------------------------------------------------

    int m_totalCodes;

    int m_accepted;

    int m_rejected;

    int m_duplicates;

};

}