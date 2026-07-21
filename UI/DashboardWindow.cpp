#include "DashboardWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QFrame>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include <QTimer>
#include <QDateTime>

namespace PharmaTrack
{

DashboardWindow::DashboardWindow(QWidget *parent)
    : QWidget(parent),
      m_scrollArea(nullptr),
      m_container(nullptr),
      m_mainLayout(nullptr),

      m_totalScansLabel(nullptr),
      m_acceptedLabel(nullptr),
      m_rejectedLabel(nullptr),
      m_remainingLabel(nullptr),

      m_scannerStatusLabel(nullptr),
      m_printerStatusLabel(nullptr),
      m_databaseStatusLabel(nullptr),
      m_plcStatusLabel(nullptr),

      m_scannerNameLabel(nullptr),
      m_scannerPortLabel(nullptr),
      m_scannerConfigurationLabel(nullptr),
      m_scannerCommunicationLabel(nullptr),
      m_lastScanLabel(nullptr),

      m_batchLabel(nullptr),
      m_productionStateLabel(nullptr),
      m_operatorLabel(nullptr),

      m_clockLabel(nullptr),
      m_clockTimer(nullptr),

      m_activityTable(nullptr)
{
    setupUi();

    applyTheme();

    m_clockTimer = new QTimer(this);

    connect(m_clockTimer,
            &QTimer::timeout,
            this,
            &DashboardWindow::updateClock);

    m_clockTimer->start(1000);

    updateClock();
}

DashboardWindow::~DashboardWindow()
{
}

////////////////////////////////////////////////////////
/// Setup UI
////////////////////////////////////////////////////////

void DashboardWindow::setupUi()
{
    //--------------------------------------------------
    // Root Layout
    //--------------------------------------------------

    auto* rootLayout =
            new QVBoxLayout(this);

    rootLayout->setContentsMargins(0,0,0,0);

    //--------------------------------------------------
    // Scroll Area
    //--------------------------------------------------

    m_scrollArea =
            new QScrollArea;

    m_scrollArea->setWidgetResizable(true);

    m_scrollArea->setFrameShape(QFrame::NoFrame);

    rootLayout->addWidget(m_scrollArea);

    //--------------------------------------------------
    // Container
    //--------------------------------------------------

    m_container =
            new QWidget;

    m_scrollArea->setWidget(m_container);

    //--------------------------------------------------
    // Main Layout
    //--------------------------------------------------

    m_mainLayout =
            new QVBoxLayout(m_container);

    m_mainLayout->setContentsMargins(
                25,
                25,
                25,
                25);

    m_mainLayout->setSpacing(20);

    //////////////////////////////////////////////////////
    /// Title
    //////////////////////////////////////////////////////

    QLabel* title =
            new QLabel("Production Dashboard");

    title->setStyleSheet(
                "font-size:28px;"
                "font-weight:700;"
                "color:white;");

    m_mainLayout->addWidget(title);

    //////////////////////////////////////////////////////
    /// Statistics
    //////////////////////////////////////////////////////

    auto* statisticsLayout =
            new QHBoxLayout;

    statisticsLayout->setSpacing(15);

    statisticsLayout->addWidget(
                createStatisticCard(
                    "Total Scans",
                    m_totalScansLabel,
                    "#2563EB"));

    statisticsLayout->addWidget(
                createStatisticCard(
                    "Accepted",
                    m_acceptedLabel,
                    "#16A34A"));

    statisticsLayout->addWidget(
                createStatisticCard(
                    "Rejected",
                    m_rejectedLabel,
                    "#DC2626"));

    statisticsLayout->addWidget(
                createStatisticCard(
                    "Remaining",
                    m_remainingLabel,
                    "#F59E0B"));

    m_mainLayout->addLayout(
                statisticsLayout);

    //////////////////////////////////////////////////////
    /// Information Section
    //////////////////////////////////////////////////////

    auto* informationLayout =
            new QHBoxLayout;

    informationLayout->setSpacing(20);

    //////////////////////////////////////////////////////
    /// Scanner Information
    //////////////////////////////////////////////////////

    QFrame* scannerFrame =
            new QFrame;

    scannerFrame->setObjectName("Card");

    auto* scannerLayout =
            new QGridLayout(scannerFrame);

    scannerLayout->setHorizontalSpacing(15);

    scannerLayout->setVerticalSpacing(12);

    scannerLayout->addWidget(
                new QLabel("Scanner"),
                0,0);

    m_scannerNameLabel =
            new QLabel("--");

    scannerLayout->addWidget(
                m_scannerNameLabel,
                0,1);

    scannerLayout->addWidget(
                new QLabel("Port"),
                1,0);

    m_scannerPortLabel =
            new QLabel("--");

    scannerLayout->addWidget(
                m_scannerPortLabel,
                1,1);

    scannerLayout->addWidget(
                new QLabel("Configuration"),
                2,0);

    m_scannerConfigurationLabel =
            new QLabel("--");

    scannerLayout->addWidget(
                m_scannerConfigurationLabel,
                2,1);

    scannerLayout->addWidget(
                new QLabel("Communication"),
                3,0);

    m_scannerCommunicationLabel =
            new QLabel("Waiting");

    scannerLayout->addWidget(
                m_scannerCommunicationLabel,
                3,1);

    scannerLayout->addWidget(
                new QLabel("Last Scan"),
                4,0);

    m_lastScanLabel =
            new QLabel("--");

    scannerLayout->addWidget(
                m_lastScanLabel,
                4,1);

    informationLayout->addWidget(
                scannerFrame);
                    //////////////////////////////////////////////////////
    /// Production Information
    //////////////////////////////////////////////////////

    QFrame* productionFrame =
            new QFrame;

    productionFrame->setObjectName("Card");

    auto* productionLayout =
            new QGridLayout(productionFrame);

    productionLayout->setHorizontalSpacing(15);

    productionLayout->setVerticalSpacing(12);

    productionLayout->addWidget(
                new QLabel("Current Batch"),
                0,0);

    m_batchLabel =
            new QLabel("--");

    productionLayout->addWidget(
                m_batchLabel,
                0,1);

    productionLayout->addWidget(
                new QLabel("Production"),
                1,0);

    m_productionStateLabel =
            new QLabel("Idle");

    productionLayout->addWidget(
                m_productionStateLabel,
                1,1);

    productionLayout->addWidget(
                new QLabel("Operator"),
                2,0);

    m_operatorLabel =
            new QLabel("Administrator");

    productionLayout->addWidget(
                m_operatorLabel,
                2,1);

    productionLayout->addWidget(
                new QLabel("Clock"),
                3,0);

    m_clockLabel =
            new QLabel;

    productionLayout->addWidget(
                m_clockLabel,
                3,1);

    informationLayout->addWidget(
                productionFrame);

    m_mainLayout->addLayout(
                informationLayout);

    //////////////////////////////////////////////////////
    /// Device Status
    //////////////////////////////////////////////////////

    QLabel* deviceTitle =
            new QLabel("Device Status");

    deviceTitle->setStyleSheet(
                "font-size:22px;"
                "font-weight:700;"
                "color:white;");

    m_mainLayout->addWidget(
                deviceTitle);

    auto* statusLayout =
            new QHBoxLayout;

    statusLayout->setSpacing(15);

    statusLayout->addWidget(
                createStatusCard(
                    "Scanner",
                    m_scannerStatusLabel));

    statusLayout->addWidget(
                createStatusCard(
                    "Database",
                    m_databaseStatusLabel));

    statusLayout->addWidget(
                createStatusCard(
                    "Printer",
                    m_printerStatusLabel));

    statusLayout->addWidget(
                createStatusCard(
                    "PLC",
                    m_plcStatusLabel));

    m_mainLayout->addLayout(
                statusLayout);

    //////////////////////////////////////////////////////
    /// Activity
    //////////////////////////////////////////////////////

    QLabel* activityTitle =
            new QLabel("Recent Activity");

    activityTitle->setStyleSheet(
                "font-size:22px;"
                "font-weight:700;"
                "color:white;");

    m_mainLayout->addWidget(
                activityTitle);

    m_activityTable =
            new QTableWidget;

    m_activityTable->setColumnCount(2);

    m_activityTable->setHorizontalHeaderLabels(
                QStringList()
                << "Time"
                << "Activity");

    m_activityTable->horizontalHeader()->
            setStretchLastSection(true);

    m_activityTable->verticalHeader()->
            setVisible(false);

    m_activityTable->setSelectionMode(
                QAbstractItemView::NoSelection);

    m_activityTable->setEditTriggers(
                QAbstractItemView::NoEditTriggers);

    m_activityTable->setAlternatingRowColors(true);

    m_activityTable->setMinimumHeight(300);

    m_mainLayout->addWidget(
                m_activityTable);

    //////////////////////////////////////////////////////
    /// Default Values
    //////////////////////////////////////////////////////

    setTotalScans(0);

    setAcceptedScans(0);

    setRejectedScans(0);

    setRemainingCodes(0);

    setScannerStatus(false);

    setDatabaseStatus(true);

    setPrinterStatus(false);

    setPLCStatus(false);
}
////////////////////////////////////////////////////////
/// Statistic Card
////////////////////////////////////////////////////////

QFrame* DashboardWindow::createStatisticCard(
        const QString& title,
        QLabel*& valueLabel,
        const QString& color)
{
    QFrame* frame = new QFrame;

    frame->setObjectName("Card");

    auto* layout = new QVBoxLayout(frame);

    QLabel* titleLabel = new QLabel(title);

    titleLabel->setAlignment(Qt::AlignCenter);

    titleLabel->setStyleSheet(
                "font-size:14px;"
                "color:#CBD5E1;"
                "font-weight:600;");

    valueLabel = new QLabel("0");

    valueLabel->setAlignment(Qt::AlignCenter);

    valueLabel->setStyleSheet(
                QString(
                    "font-size:32px;"
                    "font-weight:700;"
                    "color:%1;")
                .arg(color));

    layout->addWidget(titleLabel);

    layout->addWidget(valueLabel);

    return frame;
}

////////////////////////////////////////////////////////
/// Status Card
////////////////////////////////////////////////////////

QFrame* DashboardWindow::createStatusCard(
        const QString& device,
        QLabel*& statusLabel)
{
    QFrame* frame = new QFrame;

    frame->setObjectName("Card");

    auto* layout = new QVBoxLayout(frame);

    QLabel* title =
            new QLabel(device);

    title->setAlignment(Qt::AlignCenter);

    title->setStyleSheet(
                "font-size:16px;"
                "font-weight:600;");

    statusLabel =
            new QLabel("Offline");

    statusLabel->setAlignment(Qt::AlignCenter);

    statusLabel->setStyleSheet(
                "font-size:18px;"
                "font-weight:700;"
                "color:#EF4444;");

    layout->addWidget(title);

    layout->addWidget(statusLabel);

    return frame;
}

////////////////////////////////////////////////////////
/// Theme
////////////////////////////////////////////////////////

void DashboardWindow::applyTheme()
{
    setStyleSheet(R"(

QFrame#Card
{
    background:#1E293B;
    border:1px solid #334155;
    border-radius:12px;
}

QTableWidget
{
    background:#1E293B;
    color:white;
    border:1px solid #334155;
    border-radius:10px;
    gridline-color:#334155;
}

QHeaderView::section
{
    background:#0F172A;
    color:white;
    border:none;
    padding:8px;
    font-weight:600;
}

QScrollArea
{
    border:none;
}

)");
}

////////////////////////////////////////////////////////
/// Statistics
////////////////////////////////////////////////////////

void DashboardWindow::setTotalScans(int value)
{
    m_totalScansLabel->setNum(value);
}

void DashboardWindow::setAcceptedScans(int value)
{
    m_acceptedLabel->setNum(value);
}

void DashboardWindow::setRejectedScans(int value)
{
    m_rejectedLabel->setNum(value);
}

void DashboardWindow::setRemainingCodes(int value)
{
    m_remainingLabel->setNum(value);
}

////////////////////////////////////////////////////////
/// Device Status
////////////////////////////////////////////////////////

void DashboardWindow::setScannerStatus(bool connected)
{
    m_scannerStatusLabel->setText(
                connected ?
                "🟢 Online" :
                "🔴 Offline");
}

void DashboardWindow::setPrinterStatus(bool connected)
{
    m_printerStatusLabel->setText(
                connected ?
                "🟢 Online" :
                "🔴 Offline");
}

void DashboardWindow::setDatabaseStatus(bool connected)
{
    m_databaseStatusLabel->setText(
                connected ?
                "🟢 Online" :
                "🔴 Offline");
}

void DashboardWindow::setPLCStatus(bool connected)
{
    m_plcStatusLabel->setText(
                connected ?
                "🟢 Online" :
                "🔴 Offline");
}

////////////////////////////////////////////////////////
/// Scanner Information
////////////////////////////////////////////////////////

void DashboardWindow::setScannerName(
        const QString& name)
{
    m_scannerNameLabel->setText(name);
}

void DashboardWindow::setScannerPort(
        const QString& port)
{
    m_scannerPortLabel->setText(port);
}

void DashboardWindow::setScannerConfiguration(
        const QString& configuration)
{
    m_scannerConfigurationLabel->setText(configuration);
}

void DashboardWindow::setScannerCommunication(
        const QString& communication)
{
    m_scannerCommunicationLabel->setText(communication);
}

void DashboardWindow::setLastScan(
        const QString& code)
{
    m_lastScanLabel->setText(code);
}

////////////////////////////////////////////////////////
/// Production
////////////////////////////////////////////////////////

void DashboardWindow::setCurrentBatch(
        const QString& batch)
{
    m_batchLabel->setText(batch);
}

void DashboardWindow::setProductionState(
        const QString& state)
{
    m_productionStateLabel->setText(state);
}

void DashboardWindow::setOperator(
        const QString& name)
{
    m_operatorLabel->setText(name);
}

////////////////////////////////////////////////////////
/// Activity
////////////////////////////////////////////////////////

void DashboardWindow::addActivity(
        const QString& activity)
{
    int row =
            m_activityTable->rowCount();

    m_activityTable->insertRow(row);

    m_activityTable->setItem(
                row,
                0,
                new QTableWidgetItem(
                    QTime::currentTime().toString("hh:mm:ss")));

    m_activityTable->setItem(
                row,
                1,
                new QTableWidgetItem(activity));

    m_activityTable->scrollToBottom();
}

////////////////////////////////////////////////////////
/// Clock
////////////////////////////////////////////////////////

void DashboardWindow::updateClock()
{
    m_clockLabel->setText(
                QDateTime::currentDateTime()
                .toString("dd MMM yyyy  hh:mm:ss AP"));
}}