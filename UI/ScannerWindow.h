#pragma once

#include <QMainWindow>
#include <QGridLayout>
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE

class QLabel;
class QPushButton;
class QTableWidget;
class QGroupBox;
class QFrame;

QT_END_NAMESPACE

namespace PharmaTrack
{

class ScannerManager;
class ScannerService;

class ScannerWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit ScannerWindow(
            QWidget* parent = nullptr);

    ~ScannerWindow();

    //////////////////////////////////////////////////////
    /// Services
    //////////////////////////////////////////////////////

    void setScannerManager(
            ScannerManager* manager);

    void setScannerService(
            ScannerService* service);

private slots:

    //////////////////////////////////////////////////////
    /// Scanner
    //////////////////////////////////////////////////////

    void onConnected();

    void onDisconnected();

    void onConnectionLost();

    void onScanReceived(
            const QString& code);

    //////////////////////////////////////////////////////
    /// Validation
    //////////////////////////////////////////////////////

    void onBatchNotLoaded(
            const QString& code);

    void onCodeFound(
            const QString& code);

    void onCodeNotFound(
            const QString& code);

    void onDuplicateCode(
            const QString& code);

    //////////////////////////////////////////////////////
    /// Buttons
    //////////////////////////////////////////////////////

    void discoverScanner();

    void connectScanner();

    void disconnectScanner();

    void clearHistory();

private:

    //////////////////////////////////////////////////////
    /// UI
    //////////////////////////////////////////////////////

    void createUi();

    void createStatusPanel();

    void createCurrentScanPanel();

    void createHistoryPanel();

    void createBottomPanel();

    void createConnections();

    void applyStyle();

    //////////////////////////////////////////////////////
    /// Helpers
    //////////////////////////////////////////////////////

    void addHistoryItem(
        const QString& code,
        const QString& status,
        const QString& batch,
        const QString& remarks);
    void setConnectionStatus(
            const QString& status);

    void setActivityStatus(
            const QString& activity);

    void setValidationStatus(
            const QString& status);

private:

    //////////////////////////////////////////////////////
    /// Services
    //////////////////////////////////////////////////////

    ScannerManager* m_scannerManager = nullptr;

    ScannerService* m_scannerService = nullptr;
int m_lastHistoryRow = -1; 
    //////////////////////////////////////////////////////
    /// Main Panels
    //////////////////////////////////////////////////////

    QGroupBox* m_statusPanel = nullptr;

    QGroupBox* m_currentScanPanel = nullptr;

    QGroupBox* m_historyPanel = nullptr;

    QFrame* m_bottomPanel = nullptr;

    //////////////////////////////////////////////////////
    /// Status Panel
    //////////////////////////////////////////////////////

    QLabel* m_connectionLabel = nullptr;

    QLabel* m_activityLabel = nullptr;

    QLabel* m_driverLabel = nullptr;

    QLabel* m_scannerLabel = nullptr;

    QLabel* m_ipLabel = nullptr;

    QLabel* m_heartbeatLabel = nullptr;

    //////////////////////////////////////////////////////
    /// Current Scan
    //////////////////////////////////////////////////////

    QPlainTextEdit* m_qrCodeEdit = nullptr;

    QLabel* m_scanTimeLabel = nullptr;

    QLabel* m_validationLabel = nullptr;

    //////////////////////////////////////////////////////
    /// History
    //////////////////////////////////////////////////////

    QTableWidget* m_historyTable = nullptr;

    //////////////////////////////////////////////////////
    /// Buttons
    //////////////////////////////////////////////////////

    QPushButton* m_discoverButton = nullptr;

    QPushButton* m_connectButton = nullptr;

    QPushButton* m_disconnectButton = nullptr;

    QPushButton* m_clearHistoryButton = nullptr;
};

} // namespace PharmaTrack