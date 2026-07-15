#include "ScannerWindow.h"

#include "../Services/ScannerService.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>

namespace PharmaTrack
{

ScannerWindow::ScannerWindow(QWidget* parent)
    : QWidget(parent),
      m_mainLayout(nullptr),

      m_batchFrame(nullptr),
      m_batchCombo(nullptr),
      m_loadBatchButton(nullptr),
      m_batchStatusLabel(nullptr),

      m_scannerFrame(nullptr),
      m_portCombo(nullptr),
      m_refreshPortsButton(nullptr),
      m_connectButton(nullptr),
      m_disconnectButton(nullptr),
      m_startScanningButton(nullptr),
      m_scannerStatusLabel(nullptr),

      m_resultFrame(nullptr),
      m_lastCodeLabel(nullptr),
      m_resultLabel(nullptr),

      m_statisticsFrame(nullptr),
      m_totalLabel(nullptr),
      m_acceptedLabel(nullptr),
      m_rejectedLabel(nullptr),
      m_duplicateLabel(nullptr),
      m_remainingLabel(nullptr),

      m_activityFrame(nullptr),
      m_activityTable(nullptr),

      m_scannerService(nullptr)
{
    setupUi();

    applyTheme();

    m_scannerService = new ScannerService(this);

    loadAvailableBatches();

    refreshPorts();
}

ScannerWindow::~ScannerWindow()
{
}

void ScannerWindow::setupUi()
{
    m_mainLayout = new QVBoxLayout(this);

    m_mainLayout->setContentsMargins(20,20,20,20);

    m_mainLayout->setSpacing(20);

    createBatchSection();

    createScannerSection();

    createResultSection();

    createStatisticsSection();

    createActivitySection();

    m_mainLayout->addStretch();
}

/// --------------part 02 ----------------- 

void ScannerWindow::createBatchSection()
{
    //----------------------------------------------------
    // Main Frame
    //----------------------------------------------------

    m_batchFrame = new QFrame;

    m_batchFrame->setObjectName("BatchFrame");

    auto* layout = new QVBoxLayout(m_batchFrame);

    layout->setContentsMargins(20,20,20,20);

    layout->setSpacing(15);

    //----------------------------------------------------
    // Title
    //----------------------------------------------------

    QLabel* title = new QLabel("Production Batch");

    title->setObjectName("SectionTitle");

    layout->addWidget(title);

    //----------------------------------------------------
    // Controls
    //----------------------------------------------------

    auto* controlLayout = new QHBoxLayout;

    controlLayout->setSpacing(15);

    m_batchCombo = new QComboBox;

    m_batchCombo->setMinimumHeight(40);

    m_batchCombo->setMinimumWidth(300);

    m_batchCombo->setPlaceholderText(
                "Select Production Batch");

    m_loadBatchButton =
            new QPushButton("Load Batch");

    m_loadBatchButton->setMinimumHeight(40);

    m_loadBatchButton->setMinimumWidth(150);

    controlLayout->addWidget(m_batchCombo);

    controlLayout->addWidget(m_loadBatchButton);

    controlLayout->addStretch();

    layout->addLayout(controlLayout);

    //----------------------------------------------------
    // Batch Information
    //----------------------------------------------------

    auto* infoLayout = new QGridLayout;

    infoLayout->setHorizontalSpacing(40);

    infoLayout->setVerticalSpacing(12);

    infoLayout->addWidget(
        new QLabel("Batch Status"),
        0,
        0);

    m_batchStatusLabel =
            new QLabel("🔴 No Batch Loaded");

    m_batchStatusLabel->setObjectName(
                "StatusLabel");

    infoLayout->addWidget(
        m_batchStatusLabel,
        0,
        1);

    layout->addLayout(infoLayout);

    //----------------------------------------------------
    // Events
    //----------------------------------------------------

    connect(
        m_loadBatchButton,
        &QPushButton::clicked,
        this,
        &ScannerWindow::loadBatch);

    //----------------------------------------------------
    // Add To Main Layout
    //----------------------------------------------------

    m_mainLayout->addWidget(m_batchFrame);
}

// -------------- part 03 ----------------

void ScannerWindow::createScannerSection()
{
    //----------------------------------------------------
    // Main Frame
    //----------------------------------------------------

    m_scannerFrame = new QFrame;

    m_scannerFrame->setObjectName("ScannerFrame");

    auto* layout = new QVBoxLayout(m_scannerFrame);

    layout->setContentsMargins(20,20,20,20);

    layout->setSpacing(15);

    //----------------------------------------------------
    // Title
    //----------------------------------------------------

    QLabel* title = new QLabel("Scanner Connection");

    title->setObjectName("SectionTitle");

    layout->addWidget(title);

    //----------------------------------------------------
    // Controls
    //----------------------------------------------------

    auto* controlLayout = new QHBoxLayout;

    controlLayout->setSpacing(10);

    m_portCombo = new QComboBox;

    m_portCombo->setMinimumWidth(180);

    m_portCombo->setMinimumHeight(40);

    m_refreshPortsButton =
            new QPushButton("Refresh");

    m_refreshPortsButton->setMinimumHeight(40);

    m_connectButton =
            new QPushButton("Connect");

    m_connectButton->setMinimumHeight(40);

    m_disconnectButton =
            new QPushButton("Disconnect");

    m_disconnectButton->setMinimumHeight(40);

    m_startScanningButton =
            new QPushButton("Start Scanning");

    m_startScanningButton->setMinimumHeight(40);

    // Disabled until scanner is connected
    m_startScanningButton->setEnabled(false);

    controlLayout->addWidget(
                new QLabel("COM Port"));

    controlLayout->addWidget(m_portCombo);

    controlLayout->addWidget(m_refreshPortsButton);

    controlLayout->addWidget(m_connectButton);

    controlLayout->addWidget(m_disconnectButton);

    controlLayout->addWidget(m_startScanningButton);

    controlLayout->addStretch();

    layout->addLayout(controlLayout);

    //----------------------------------------------------
    // Scanner Status
    //----------------------------------------------------

    auto* statusLayout = new QGridLayout;

    statusLayout->setHorizontalSpacing(40);

    statusLayout->setVerticalSpacing(12);

    statusLayout->addWidget(
                new QLabel("Scanner Status"),
                0,
                0);

    m_scannerStatusLabel =
            new QLabel("🔴 Disconnected");

    m_scannerStatusLabel->setObjectName(
                "StatusLabel");

    statusLayout->addWidget(
                m_scannerStatusLabel,
                0,
                1);

    layout->addLayout(statusLayout);

    //----------------------------------------------------
    // Events
    //----------------------------------------------------

    connect(
                m_refreshPortsButton,
                &QPushButton::clicked,
                this,
                &ScannerWindow::refreshPorts);

    connect(
                m_connectButton,
                &QPushButton::clicked,
                this,
                &ScannerWindow::connectScanner);

    connect(
                m_disconnectButton,
                &QPushButton::clicked,
                this,
                &ScannerWindow::disconnectScanner);

    connect(
                m_startScanningButton,
                &QPushButton::clicked,
                this,
                &ScannerWindow::startScanning);

    //----------------------------------------------------
    // Add To Main Layout
    //----------------------------------------------------

    m_mainLayout->addWidget(m_scannerFrame);
}
  // ------ pART 04 
void ScannerWindow::createResultSection()
{
    //----------------------------------------------------
    // Main Frame
    //----------------------------------------------------

    m_resultFrame = new QFrame;

    m_resultFrame->setObjectName("ResultFrame");

    auto* layout = new QVBoxLayout(m_resultFrame);

    layout->setContentsMargins(20,20,20,20);

    layout->setSpacing(20);

    //----------------------------------------------------
    // Title
    //----------------------------------------------------

    QLabel* title = new QLabel("Live Scan Result");

    title->setObjectName("SectionTitle");

    layout->addWidget(title);

    //----------------------------------------------------
    // Last Scanned Code
    //----------------------------------------------------

    QLabel* lastCodeTitle =
            new QLabel("Last Scanned Serial Number");

    lastCodeTitle->setObjectName("FieldTitle");

    layout->addWidget(lastCodeTitle);

    m_lastCodeLabel = new QLabel("------");

    m_lastCodeLabel->setObjectName("LastCodeLabel");

    m_lastCodeLabel->setAlignment(Qt::AlignCenter);

    m_lastCodeLabel->setMinimumHeight(70);

    layout->addWidget(m_lastCodeLabel);

    //----------------------------------------------------
    // Verification Result
    //----------------------------------------------------

    QLabel* resultTitle =
            new QLabel("Verification Result");

    resultTitle->setObjectName("FieldTitle");

    layout->addWidget(resultTitle);

    m_resultLabel = new QLabel("Waiting for Scanner...");

    m_resultLabel->setObjectName("ResultLabel");

    m_resultLabel->setAlignment(Qt::AlignCenter);

    m_resultLabel->setMinimumHeight(80);

    layout->addWidget(m_resultLabel);

    //----------------------------------------------------
    // Information Panel
    //----------------------------------------------------

    auto* infoLayout = new QGridLayout;

    infoLayout->setHorizontalSpacing(40);

    infoLayout->setVerticalSpacing(12);

    //----------------------------------------------------
    // Time
    //----------------------------------------------------

    infoLayout->addWidget(
                new QLabel("Last Scan Time"),
                0,
                0);

    QLabel* lastScanTime =
            new QLabel("--:--:--");

    lastScanTime->setObjectName("InfoLabel");

    infoLayout->addWidget(
                lastScanTime,
                0,
                1);

    //----------------------------------------------------
    // Total Scans
    //----------------------------------------------------

    infoLayout->addWidget(
                new QLabel("Session Scans"),
                1,
                0);

    QLabel* sessionScans =
            new QLabel("0");

    sessionScans->setObjectName("InfoLabel");

    infoLayout->addWidget(
                sessionScans,
                1,
                1);

    layout->addLayout(infoLayout);

    //----------------------------------------------------
    // Add To Main Layout
    //----------------------------------------------------

    m_mainLayout->addWidget(m_resultFrame);
}


// ------------- part 05 ----------  

void ScannerWindow::createStatisticsSection()
{
    //----------------------------------------------------
    // Main Frame
    //----------------------------------------------------

    m_statisticsFrame = new QFrame;

    m_statisticsFrame->setObjectName("StatisticsFrame");

    auto* layout = new QGridLayout(m_statisticsFrame);

    layout->setContentsMargins(20,20,20,20);

    layout->setHorizontalSpacing(20);

    layout->setVerticalSpacing(20);

    //----------------------------------------------------
    // Total Codes
    //----------------------------------------------------

    auto* totalFrame = new QFrame;

    totalFrame->setObjectName("StatisticCard");

    auto* totalLayout = new QVBoxLayout(totalFrame);

    QLabel* totalTitle = new QLabel("Total Codes");

    totalTitle->setObjectName("StatisticTitle");

    m_totalLabel = new QLabel("0");

    m_totalLabel->setObjectName("StatisticValue");

    m_totalLabel->setAlignment(Qt::AlignCenter);

    totalLayout->addWidget(totalTitle);

    totalLayout->addWidget(m_totalLabel);

    //----------------------------------------------------
    // Accepted
    //----------------------------------------------------

    auto* acceptedFrame = new QFrame;

    acceptedFrame->setObjectName("StatisticCard");

    auto* acceptedLayout = new QVBoxLayout(acceptedFrame);

    QLabel* acceptedTitle = new QLabel("Accepted");

    acceptedTitle->setObjectName("StatisticTitle");

    m_acceptedLabel = new QLabel("0");

    m_acceptedLabel->setObjectName("AcceptedValue");

    m_acceptedLabel->setAlignment(Qt::AlignCenter);

    acceptedLayout->addWidget(acceptedTitle);

    acceptedLayout->addWidget(m_acceptedLabel);

    //----------------------------------------------------
    // Rejected
    //----------------------------------------------------

    auto* rejectedFrame = new QFrame;

    rejectedFrame->setObjectName("StatisticCard");

    auto* rejectedLayout = new QVBoxLayout(rejectedFrame);

    QLabel* rejectedTitle = new QLabel("Rejected");

    rejectedTitle->setObjectName("StatisticTitle");

    m_rejectedLabel = new QLabel("0");

    m_rejectedLabel->setObjectName("RejectedValue");

    m_rejectedLabel->setAlignment(Qt::AlignCenter);

    rejectedLayout->addWidget(rejectedTitle);

    rejectedLayout->addWidget(m_rejectedLabel);

    //----------------------------------------------------
    // Duplicate
    //----------------------------------------------------

    auto* duplicateFrame = new QFrame;

    duplicateFrame->setObjectName("StatisticCard");

    auto* duplicateLayout = new QVBoxLayout(duplicateFrame);

    QLabel* duplicateTitle = new QLabel("Duplicate");

    duplicateTitle->setObjectName("StatisticTitle");

    m_duplicateLabel = new QLabel("0");

    m_duplicateLabel->setObjectName("DuplicateValue");

    m_duplicateLabel->setAlignment(Qt::AlignCenter);

    duplicateLayout->addWidget(duplicateTitle);

    duplicateLayout->addWidget(m_duplicateLabel);

    //----------------------------------------------------
    // Remaining
    //----------------------------------------------------

    auto* remainingFrame = new QFrame;

    remainingFrame->setObjectName("StatisticCard");

    auto* remainingLayout = new QVBoxLayout(remainingFrame);

    QLabel* remainingTitle = new QLabel("Remaining");

    remainingTitle->setObjectName("StatisticTitle");

    m_remainingLabel = new QLabel("0");

    m_remainingLabel->setObjectName("RemainingValue");

    m_remainingLabel->setAlignment(Qt::AlignCenter);

    remainingLayout->addWidget(remainingTitle);

    remainingLayout->addWidget(m_remainingLabel);

    //----------------------------------------------------
    // Add Cards
    //----------------------------------------------------

    layout->addWidget(totalFrame,0,0);

    layout->addWidget(acceptedFrame,0,1);

    layout->addWidget(rejectedFrame,0,2);

    layout->addWidget(duplicateFrame,0,3);

    layout->addWidget(remainingFrame,0,4);

    //----------------------------------------------------
    // Add To Main Layout
    //----------------------------------------------------

    m_mainLayout->addWidget(m_statisticsFrame);
}

 // ----- Part 06 -------------

 void ScannerWindow::createActivitySection()
{
    //----------------------------------------------------
    // Main Frame
    //----------------------------------------------------

    m_activityFrame = new QFrame;

    m_activityFrame->setObjectName("ActivityFrame");

    auto* layout = new QVBoxLayout(m_activityFrame);

    layout->setContentsMargins(20,20,20,20);

    layout->setSpacing(15);

    //----------------------------------------------------
    // Title
    //----------------------------------------------------

    QLabel* title = new QLabel("Live Scan Activity");

    title->setObjectName("SectionTitle");

    layout->addWidget(title);

    //----------------------------------------------------
    // Activity Table
    //----------------------------------------------------

    m_activityTable = new QTableWidget;

    m_activityTable->setColumnCount(4);

    m_activityTable->setHorizontalHeaderLabels(
    {
        "Time",
        "Serial Number",
        "Result",
        "Message"
    });

    m_activityTable->horizontalHeader()->setStretchLastSection(true);

    m_activityTable->horizontalHeader()->setSectionResizeMode(
                QHeaderView::Stretch);

    m_activityTable->verticalHeader()->setVisible(false);

    m_activityTable->setAlternatingRowColors(true);

    m_activityTable->setSelectionBehavior(
                QAbstractItemView::SelectRows);

    m_activityTable->setSelectionMode(
                QAbstractItemView::SingleSelection);

    m_activityTable->setEditTriggers(
                QAbstractItemView::NoEditTriggers);

    m_activityTable->setFocusPolicy(Qt::NoFocus);

    m_activityTable->setSortingEnabled(false);

    m_activityTable->setShowGrid(false);

    m_activityTable->setMinimumHeight(300);

    layout->addWidget(m_activityTable);

    //----------------------------------------------------
    // Add To Main Layout
    //----------------------------------------------------

    m_mainLayout->addWidget(m_activityFrame);
}

// ------------- Part 07 ---------------- 

void ScannerWindow::applyTheme()
{
    setStyleSheet(R"(

QWidget
{
    background-color: #0F172A;
    color: white;
    font-family: "Segoe UI";
    font-size: 13px;
}

QFrame#BatchFrame,
QFrame#ScannerFrame,
QFrame#ResultFrame,
QFrame#StatisticsFrame,
QFrame#ActivityFrame
{
    background-color: #1E293B;
    border: 1px solid #334155;
    border-radius: 12px;
}

QLabel#SectionTitle
{
    font-size: 20px;
    font-weight: 700;
    color: white;
}

QLabel#FieldTitle
{
    font-size: 14px;
    font-weight: 600;
    color: #CBD5E1;
}

QLabel#StatusLabel
{
    font-size: 15px;
    font-weight: bold;
    color: #F8FAFC;
}

QLabel#LastCodeLabel
{
    font-size: 26px;
    font-weight: bold;

    background-color: #0F172A;

    border: 2px solid #2563EB;

    border-radius: 10px;

    padding: 15px;
}

QLabel#ResultLabel
{
    font-size: 32px;

    font-weight: bold;

    background-color: #1E293B;

    border-radius: 10px;

    padding: 20px;
}

QLabel#StatisticTitle
{
    font-size: 13px;

    color: #CBD5E1;
}

QLabel#StatisticValue
{
    font-size: 28px;

    font-weight: bold;

    color: white;
}

QLabel#AcceptedValue
{
    font-size: 28px;

    font-weight: bold;

    color: #22C55E;
}

QLabel#RejectedValue
{
    font-size: 28px;

    font-weight: bold;

    color: #EF4444;
}

QLabel#DuplicateValue
{
    font-size: 28px;

    font-weight: bold;

    color: #F59E0B;
}

QLabel#RemainingValue
{
    font-size: 28px;

    font-weight: bold;

    color: #8B5CF6;
}

QFrame#StatisticCard
{
    background-color: #111827;

    border: 1px solid #334155;

    border-radius: 10px;

    padding: 10px;
}

QPushButton
{
    background-color: #2563EB;

    color: white;

    border: none;

    border-radius: 8px;

    padding: 10px 20px;

    font-weight: bold;
}

QPushButton:hover
{
    background-color: #1D4ED8;
}

QPushButton:pressed
{
    background-color: #1E40AF;
}

QPushButton:disabled
{
    background-color: #334155;

    color: #94A3B8;
}

QComboBox
{
    background-color: #111827;

    color: white;

    border: 1px solid #334155;

    border-radius: 8px;

    padding: 8px;
}

QComboBox::drop-down
{
    border: none;
}

QTableWidget
{
    background-color: #111827;

    alternate-background-color: #1E293B;

    border: 1px solid #334155;

    gridline-color: #334155;

    color: white;
}

QHeaderView::section
{
    background-color: #1E293B;

    color: white;

    padding: 8px;

    border: none;

    font-weight: bold;
}

QTableCornerButton::section
{
    background-color: #1E293B;
}

QScrollBar:vertical
{
    background: transparent;

    width: 10px;
}

QScrollBar::handle:vertical
{
    background: #475569;

    border-radius: 5px;
}

QScrollBar::handle:vertical:hover
{
    background: #64748B;
}

QScrollBar::add-line:vertical,
QScrollBar::sub-line:vertical
{
    height: 0px;
}

)");
}
////////////////////////////////////////////////////////
/// Load Available Batches
////////////////////////////////////////////////////////

void ScannerWindow::loadAvailableBatches()
{
    if(!m_batchCombo)
        return;

    m_batchCombo->clear();

    // Temporary batches for testing
    // Later these will be loaded from registry.json

    m_batchCombo->addItem("B260714001");
    m_batchCombo->addItem("B260714002");
    m_batchCombo->addItem("B260714003");
}

////////////////////////////////////////////////////////
/// Refresh COM Ports
////////////////////////////////////////////////////////

void ScannerWindow::refreshPorts()
{
    if(!m_scannerService)
        return;

    m_portCombo->clear();

    QStringList ports =
            m_scannerService->availablePorts();

    m_portCombo->addItems(ports);
}

////////////////////////////////////////////////////////
/// Load Batch
////////////////////////////////////////////////////////

void ScannerWindow::loadBatch()
{
    if(!m_scannerService)
        return;

    QString batch =
            m_batchCombo->currentText();

    if(batch.isEmpty())
        return;

    if(m_scannerService->loadBatch(batch))
    {
        m_batchStatusLabel->setText(
                    "🟢 " + batch + " Loaded");
    }
}

////////////////////////////////////////////////////////
/// Connect Scanner
////////////////////////////////////////////////////////

void ScannerWindow::connectScanner()
{
    if(!m_scannerService)
        return;

    QString port =
            m_portCombo->currentText();

    if(port.isEmpty())
        return;

    if(m_scannerService->connectScanner(port))
    {
        m_scannerStatusLabel->setText(
                    "🟢 Connected");

        m_startScanningButton->setEnabled(true);
    }
}

////////////////////////////////////////////////////////
/// Disconnect Scanner
////////////////////////////////////////////////////////

void ScannerWindow::disconnectScanner()
{
    if(!m_scannerService)
        return;

    m_scannerService->disconnectScanner();

    m_scannerStatusLabel->setText(
                "🔴 Disconnected");

    m_startScanningButton->setEnabled(false);
}

////////////////////////////////////////////////////////
/// Start Scanning
////////////////////////////////////////////////////////

void ScannerWindow::startScanning()
{
    if(!m_scannerService)
        return;

    if(m_scannerService->startScanning())
    {
        m_resultLabel->setText(
                    "Waiting for Scanner...");
    }
}


}



