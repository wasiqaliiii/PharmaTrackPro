#pragma once

#include <QObject>
#include <QStringList>

#include "../Hardware/ScannerManager.h"
#include "VerificationService.h"

namespace PharmaTrack
{

enum class ScannerState
{
    Idle,
    BatchLoaded,
    ScannerConnected,
    Ready,
    Scanning
};

class ScannerService : public QObject
{
    Q_OBJECT

public:

    explicit ScannerService(QObject* parent = nullptr);

    //----------------------------------------------------
    // Batch
    //----------------------------------------------------

    bool loadBatch(const QString& batchId);

    void unloadBatch();

    bool hasBatchLoaded() const;

    QString currentBatch() const;

    VerificationService& verificationService();

    //----------------------------------------------------
    // Scanner
    //----------------------------------------------------

    QStringList availablePorts() const;

    bool connectScanner(const QString& port);

    void disconnectScanner();

    bool isScannerConnected() const;

    //----------------------------------------------------
    // Production
    //----------------------------------------------------

    bool startScanning();

    void stopScanning();

    bool isScanning() const;

    ScannerState state() const;

signals:

    //----------------------------------------------------
    // Scanner
    //----------------------------------------------------

    void scannerConnected();

    void scannerDisconnected();

    void scannerError(const QString& error);

    //----------------------------------------------------
    // Batch
    //----------------------------------------------------

    void batchLoaded(const QString& batchId);

    void batchUnloaded();

    //----------------------------------------------------
    // Production
    //----------------------------------------------------

    void scanStarted();

    void scanStopped();

    //----------------------------------------------------
    // Verification
    //----------------------------------------------------

    void qrScanned(const QString& serial,
                   ScanResult result);

    void codeVerified(const ScanLog& log);

    //----------------------------------------------------
    // Dashboard
    //----------------------------------------------------

    void statisticsChanged(
            int total,
            int accepted,
            int rejected,
            int duplicate,
            int remaining);

private slots:

    void processQr(const QString& qr);

private:

    void setState(ScannerState state);

private:

    //----------------------------------------------------
    // Hardware
    //----------------------------------------------------

    ScannerManager m_scanner;

    //----------------------------------------------------
    // Business
    //----------------------------------------------------

    VerificationService m_verification;

    //----------------------------------------------------
    // Current Batch
    //----------------------------------------------------

    QString m_currentBatch;

    //----------------------------------------------------
    // State
    //----------------------------------------------------

    ScannerState m_state;
};

}