#include "ScannerService.h"

namespace PharmaTrack
{

ScannerService::ScannerService(QObject *parent)
    : QObject(parent),
      m_state(ScannerState::Idle)
{
    //--------------------------------------------------
    // Scanner Signals
    //--------------------------------------------------

    connect(&m_scanner,
            &ScannerManager::connected,
            this,
            &ScannerService::scannerConnected);

    connect(&m_scanner,
            &ScannerManager::disconnected,
            this,
            &ScannerService::scannerDisconnected);

    connect(&m_scanner,
            &ScannerManager::errorOccurred,
            this,
            &ScannerService::scannerError);

    connect(&m_scanner,
            &ScannerManager::qrScanned,
            this,
            &ScannerService::processQr);

    //--------------------------------------------------
    // Verification Signals
    //--------------------------------------------------

    connect(&m_verification,
            &VerificationService::statisticsChanged,
            this,
            &ScannerService::statisticsChanged);

    connect(&m_verification,
            &VerificationService::codeVerified,
            this,
            &ScannerService::codeVerified);
}

////////////////////////////////////////////////////////
/// State Management
////////////////////////////////////////////////////////

void ScannerService::setState(ScannerState state)
{
    m_state = state;
}

ScannerState ScannerService::state() const
{
    return m_state;
}

////////////////////////////////////////////////////////
/// Verification
////////////////////////////////////////////////////////

VerificationService& ScannerService::verificationService()
{
    return m_verification;
}

////////////////////////////////////////////////////////
/// Current Batch
////////////////////////////////////////////////////////

QString ScannerService::currentBatch() const
{
    return m_currentBatch;
}

bool ScannerService::hasBatchLoaded() const
{
    return !m_currentBatch.isEmpty();
}

////////////////////////////////////////////////////////
/// Scanner
////////////////////////////////////////////////////////

QStringList ScannerService::availablePorts() const
{
    return m_scanner.availablePorts();
}

bool ScannerService::isScannerConnected() const
{
    return m_scanner.isConnected();
}

bool ScannerService::isScanning() const
{
    return m_state == ScannerState::Scanning;
}

// part 02 

////////////////////////////////////////////////////////
/// Batch Management
////////////////////////////////////////////////////////

bool ScannerService::loadBatch(const QString& batchId)
{
    //--------------------------------------------------
    // Prevent Loading While Scanning
    //--------------------------------------------------

    if(state() == ScannerState::Scanning)
        return false;

    //--------------------------------------------------
    // Load Production Batch
    //--------------------------------------------------

    if(!m_verification.loadBatch(batchId))
        return false;

    //--------------------------------------------------
    // Save Current Batch
    //--------------------------------------------------

    m_currentBatch = batchId;

    //--------------------------------------------------
    // Update State
    //--------------------------------------------------

    if(isScannerConnected())
        setState(ScannerState::Ready);
    else
        setState(ScannerState::BatchLoaded);

    //--------------------------------------------------
    // Notify UI
    //--------------------------------------------------

    emit batchLoaded(batchId);

    return true;
}

void ScannerService::unloadBatch()
{
    //--------------------------------------------------
    // Stop Production
    //--------------------------------------------------

    stopScanning();

    //--------------------------------------------------
    // Disconnect Scanner
    //--------------------------------------------------

    disconnectScanner();

    //--------------------------------------------------
    // Clear Verification Data
    //--------------------------------------------------

    m_verification.clearProduction();

    //--------------------------------------------------
    // Reset Batch
    //--------------------------------------------------

    m_currentBatch.clear();

    //--------------------------------------------------
    // Reset State
    //--------------------------------------------------

    setState(ScannerState::Idle);

    //--------------------------------------------------
    // Notify UI
    //--------------------------------------------------

    emit batchUnloaded();
}

////////////////////////////////////////////////////////
/// Scanner Connection
////////////////////////////////////////////////////////

bool ScannerService::connectScanner(const QString& port)
{
    //--------------------------------------------------
    // Connect Scanner
    //--------------------------------------------------

    if(!m_scanner.connectScanner(port))
        return false;

    //--------------------------------------------------
    // Update State
    //--------------------------------------------------

    if(hasBatchLoaded())
        setState(ScannerState::Ready);
    else
        setState(ScannerState::ScannerConnected);

    return true;
}

void ScannerService::disconnectScanner()
{
    //--------------------------------------------------
    // Stop Scanning First
    //--------------------------------------------------

    stopScanning();

    //--------------------------------------------------
    // Disconnect Hardware
    //--------------------------------------------------

    m_scanner.disconnectScanner();

    //--------------------------------------------------
    // Update State
    //--------------------------------------------------

    if(hasBatchLoaded())
        setState(ScannerState::BatchLoaded);
    else
        setState(ScannerState::Idle);
}

////////////////////////////////////////////////////////
/// Production Control
////////////////////////////////////////////////////////

bool ScannerService::startScanning()
{
    //--------------------------------------------------
    // Scanner Must Be Ready
    //--------------------------------------------------

    if(state() != ScannerState::Ready)
        return false;

    //--------------------------------------------------
    // Start Production
    //--------------------------------------------------

    setState(ScannerState::Scanning);

    emit scanStarted();

    return true;
}

void ScannerService::stopScanning()
{
    //--------------------------------------------------
    // Already Stopped
    //--------------------------------------------------

    if(state() != ScannerState::Scanning)
        return;

    //--------------------------------------------------
    // Return To Ready State
    //--------------------------------------------------

    setState(ScannerState::Ready);

    emit scanStopped();
}

// --------- part 03 ----------

////////////////////////////////////////////////////////
/// QR Processing
////////////////////////////////////////////////////////

void ScannerService::processQr(const QString& qr)
{
    //--------------------------------------------------
    // Scanner Must Be Running
    //--------------------------------------------------

    if(state() != ScannerState::Scanning)
        return;

    //--------------------------------------------------
    // Verify QR Code
    //--------------------------------------------------

    ScanResult result =
            m_verification.verifyCode(qr);

    //--------------------------------------------------
    // Notify UI
    //--------------------------------------------------

    emit qrScanned(qr, result);
}

}