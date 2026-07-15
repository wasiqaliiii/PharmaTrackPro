#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE

class QComboBox;
class QPushButton;
class QLabel;
class QTableWidget;
class QFrame;
class QVBoxLayout;

QT_END_NAMESPACE

namespace PharmaTrack
{

class ScannerService;

class ScannerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ScannerWindow(QWidget* parent = nullptr);
    ~ScannerWindow();

private slots:

    void loadBatch();

    void refreshPorts();

    void connectScanner();

    void disconnectScanner();

    void startScanning();

private:

    void setupUi();

    void createBatchSection();

    void createScannerSection();

    void createResultSection();

    void createStatisticsSection();

    void createActivitySection();

    void applyTheme();

    void loadAvailableBatches();

private:

    //--------------------------------------------------
    // Layout
    //--------------------------------------------------

    QVBoxLayout* m_mainLayout;

    //--------------------------------------------------
    // Batch Section
    //--------------------------------------------------

    QFrame* m_batchFrame;

    QComboBox* m_batchCombo;

    QPushButton* m_loadBatchButton;

    QLabel* m_batchStatusLabel;

    //--------------------------------------------------
    // Scanner Section
    //--------------------------------------------------

    QFrame* m_scannerFrame;

    QComboBox* m_portCombo;

    QPushButton* m_refreshPortsButton;

    QPushButton* m_connectButton;

    QPushButton* m_disconnectButton;

    QPushButton* m_startScanningButton;

    QLabel* m_scannerStatusLabel;

    //--------------------------------------------------
    // Result Section
    //--------------------------------------------------

    QFrame* m_resultFrame;

    QLabel* m_lastCodeLabel;

    QLabel* m_resultLabel;

    //--------------------------------------------------
    // Statistics Section
    //--------------------------------------------------

    QFrame* m_statisticsFrame;

    QLabel* m_totalLabel;

    QLabel* m_acceptedLabel;

    QLabel* m_rejectedLabel;

    QLabel* m_duplicateLabel;

    QLabel* m_remainingLabel;

    //--------------------------------------------------
    // Activity Section
    //--------------------------------------------------

    QFrame* m_activityFrame;

    QTableWidget* m_activityTable;

    //--------------------------------------------------
    // Services
    //--------------------------------------------------

    ScannerService* m_scannerService;
};

}