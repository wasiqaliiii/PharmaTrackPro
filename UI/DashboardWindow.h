#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE

class QLabel;
class QFrame;
class QTableWidget;
class QTimer;
class QVBoxLayout;
class QGridLayout;
class QScrollArea;

QT_END_NAMESPACE

namespace PharmaTrack
{

class DashboardWindow : public QWidget
{
    Q_OBJECT

public:

    explicit DashboardWindow(QWidget* parent = nullptr);

    ~DashboardWindow();

    ////////////////////////////////////////////////////////
    /// Statistics
    ////////////////////////////////////////////////////////

    void setTotalScans(int value);

    void setAcceptedScans(int value);

    void setRejectedScans(int value);

    void setRemainingCodes(int value);

    ////////////////////////////////////////////////////////
    /// Device Status
    ////////////////////////////////////////////////////////

    void setScannerStatus(bool connected);

    void setPrinterStatus(bool connected);

    void setDatabaseStatus(bool connected);

    void setPLCStatus(bool connected);

    ////////////////////////////////////////////////////////
    /// Scanner Information
    ////////////////////////////////////////////////////////

    void setScannerName(const QString& name);

    void setScannerPort(const QString& port);

    void setScannerConfiguration(
            const QString& configuration);

    void setScannerCommunication(
            const QString& communication);

    void setLastScan(
            const QString& code);

    ////////////////////////////////////////////////////////
    /// Production
    ////////////////////////////////////////////////////////

    void setCurrentBatch(
            const QString& batch);

    void setProductionState(
            const QString& state);

    void setOperator(
            const QString& name);

    ////////////////////////////////////////////////////////
    /// Activity
    ////////////////////////////////////////////////////////

    void addActivity(
            const QString& activity);

private slots:

    void updateClock();

private:

    ////////////////////////////////////////////////////////
    /// UI
    ////////////////////////////////////////////////////////

    void setupUi();

    void applyTheme();

    ////////////////////////////////////////////////////////
    /// Helpers
    ////////////////////////////////////////////////////////

    QFrame* createStatisticCard(
            const QString& title,
            QLabel*& valueLabel,
            const QString& color);

    QFrame* createStatusCard(
            const QString& device,
            QLabel*& statusLabel);

private:

    ////////////////////////////////////////////////////////
    /// Root Layout
    ////////////////////////////////////////////////////////

    QScrollArea* m_scrollArea;

    QWidget* m_container;

    QVBoxLayout* m_mainLayout;

    ////////////////////////////////////////////////////////
    /// Statistics
    ////////////////////////////////////////////////////////

    QLabel* m_totalScansLabel;

    QLabel* m_acceptedLabel;

    QLabel* m_rejectedLabel;

    QLabel* m_remainingLabel;

    ////////////////////////////////////////////////////////
    /// Device Status
    ////////////////////////////////////////////////////////

    QLabel* m_scannerStatusLabel;

    QLabel* m_printerStatusLabel;

    QLabel* m_databaseStatusLabel;

    QLabel* m_plcStatusLabel;

    ////////////////////////////////////////////////////////
    /// Scanner Information
    ////////////////////////////////////////////////////////

    QLabel* m_scannerNameLabel;

    QLabel* m_scannerPortLabel;

    QLabel* m_scannerConfigurationLabel;

    QLabel* m_scannerCommunicationLabel;

    QLabel* m_lastScanLabel;

    ////////////////////////////////////////////////////////
    /// Production Information
    ////////////////////////////////////////////////////////

    QLabel* m_batchLabel;

    QLabel* m_productionStateLabel;

    QLabel* m_operatorLabel;

    ////////////////////////////////////////////////////////
    /// Clock
    ////////////////////////////////////////////////////////

    QLabel* m_clockLabel;

    QTimer* m_clockTimer;

    ////////////////////////////////////////////////////////
    /// Activity
    ////////////////////////////////////////////////////////

    QTableWidget* m_activityTable;
};

}