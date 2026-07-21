#include "ScannerWindow.h"
#include <QTimer>
#include "../Hardware/ScannerManager.h"
#include "../Services/ScannerService.h"
#include <QPlainTextEdit>
#include <QDateTime>
#include <QFont>
#include <QFrame>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>

namespace PharmaTrack
{

////////////////////////////////////////////////////////
/// Constructor
////////////////////////////////////////////////////////

ScannerWindow::ScannerWindow(
        QWidget* parent)
    : QMainWindow(parent)
{
    //////////////////////////////////////////////////////
    /// Window
    //////////////////////////////////////////////////////

    setWindowTitle(
                "PharmaTrack Pro - Scanner");

    resize(1400, 850);

    //////////////////////////////////////////////////////
    /// Build UI
    //////////////////////////////////////////////////////

    createUi();

    createConnections();

    applyStyle();
}

////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////

ScannerWindow::~ScannerWindow()
{
}

////////////////////////////////////////////////////////
/// Scanner Manager
////////////////////////////////////////////////////////

void ScannerWindow::setScannerManager(
        ScannerManager* manager)
{
    m_scannerManager = manager;

    createConnections();
}
////////////////////////////////////////////////////////
/// Scanner Service
////////////////////////////////////////////////////////

void ScannerWindow::setScannerService(
        ScannerService* service)
{
    m_scannerService = service;

    createConnections();
}

////////////////////////////////////////////////////////
/// Create UI
////////////////////////////////////////////////////////

void ScannerWindow::createUi()
{
    //////////////////////////////////////////////////////
    /// Central Widget
    //////////////////////////////////////////////////////

    QWidget* centralWidget =
            new QWidget(this);

    setCentralWidget(
                centralWidget);

    //////////////////////////////////////////////////////
    /// Main Layout
    //////////////////////////////////////////////////////

    QVBoxLayout* mainLayout =
            new QVBoxLayout(
                centralWidget);

    mainLayout->setContentsMargins(
                15,
                15,
                15,
                15);

    mainLayout->setSpacing(15);

    //////////////////////////////////////////////////////
    /// Top Layout
    //////////////////////////////////////////////////////

    QHBoxLayout* topLayout =
            new QHBoxLayout;

    topLayout->setSpacing(15);

    //////////////////////////////////////////////////////
    /// Create Panels
    //////////////////////////////////////////////////////

    createStatusPanel();

    createCurrentScanPanel();

    //////////////////////////////////////////////////////
    /// Add Panels
    //////////////////////////////////////////////////////

    topLayout->addWidget(
                m_statusPanel);

    topLayout->addWidget(
                m_currentScanPanel,
                1);

    //////////////////////////////////////////////////////
    /// Remaining Panels
    //////////////////////////////////////////////////////

    createHistoryPanel();

    createBottomPanel();

    //////////////////////////////////////////////////////
    /// Window Layout
    //////////////////////////////////////////////////////

    mainLayout->addLayout(
                topLayout);

    mainLayout->addWidget(
                m_historyPanel,
                1);

    mainLayout->addWidget(
                m_bottomPanel);
}
////////////////////////////////////////////////////////
/// Create Status Panel
////////////////////////////////////////////////////////

void ScannerWindow::createStatusPanel()
{
    //////////////////////////////////////////////////////
    /// Group
    //////////////////////////////////////////////////////

    m_statusPanel =
            new QGroupBox("Scanner Status");

    m_statusPanel->setMinimumWidth(360);

    QGridLayout* layout =
            new QGridLayout(m_statusPanel);

    layout->setContentsMargins(
                15,
                20,
                15,
                20);

    layout->setHorizontalSpacing(15);
    layout->setVerticalSpacing(15);

    //////////////////////////////////////////////////////
    /// Fonts
    //////////////////////////////////////////////////////

    QFont titleFont;

    titleFont.setPointSize(11);
    titleFont.setBold(true);

    QFont valueFont;

    valueFont.setPointSize(11);

    //////////////////////////////////////////////////////
    /// Connection
    //////////////////////////////////////////////////////

    QLabel* connectionTitle =
            new QLabel("Connection");

    connectionTitle->setFont(titleFont);

    m_connectionLabel =
            new QLabel("Disconnected");

    m_connectionLabel->setFont(valueFont);

    layout->addWidget(
                connectionTitle,
                0,
                0);

    layout->addWidget(
                m_connectionLabel,
                0,
                1);

    //////////////////////////////////////////////////////
    /// Activity
    //////////////////////////////////////////////////////

    QLabel* activityTitle =
            new QLabel("Activity");

    activityTitle->setFont(titleFont);

    m_activityLabel =
            new QLabel("Idle");

    m_activityLabel->setFont(valueFont);

    layout->addWidget(
                activityTitle,
                1,
                0);

    layout->addWidget(
                m_activityLabel,
                1,
                1);

    //////////////////////////////////////////////////////
    /// Driver
    //////////////////////////////////////////////////////

    QLabel* driverTitle =
            new QLabel("Driver");

    driverTitle->setFont(titleFont);

    m_driverLabel =
            new QLabel("Ethernet");

    m_driverLabel->setFont(valueFont);

    layout->addWidget(
                driverTitle,
                2,
                0);

    layout->addWidget(
                m_driverLabel,
                2,
                1);

    //////////////////////////////////////////////////////
    /// Scanner
    //////////////////////////////////////////////////////

    QLabel* scannerTitle =
            new QLabel("Scanner");

    scannerTitle->setFont(titleFont);

    m_scannerLabel =
            new QLabel("-");

    m_scannerLabel->setFont(valueFont);

    layout->addWidget(
                scannerTitle,
                3,
                0);

    layout->addWidget(
                m_scannerLabel,
                3,
                1);

    //////////////////////////////////////////////////////
    /// IP Address
    //////////////////////////////////////////////////////

    QLabel* ipTitle =
            new QLabel("IP Address");

    ipTitle->setFont(titleFont);

    m_ipLabel =
            new QLabel("-");

    m_ipLabel->setFont(valueFont);

    layout->addWidget(
                ipTitle,
                4,
                0);

    layout->addWidget(
                m_ipLabel,
                4,
                1);

    //////////////////////////////////////////////////////
    /// Last Heartbeat
    //////////////////////////////////////////////////////

    QLabel* heartbeatTitle =
            new QLabel("Last Heartbeat");

    heartbeatTitle->setFont(titleFont);

    m_heartbeatLabel =
            new QLabel("--:--:--");

    m_heartbeatLabel->setFont(valueFont);

    layout->addWidget(
                heartbeatTitle,
                5,
                0);

    layout->addWidget(
                m_heartbeatLabel,
                5,
                1);

    //////////////////////////////////////////////////////
    /// Layout
    //////////////////////////////////////////////////////

    layout->setColumnStretch(
                1,
                1);

    layout->setRowStretch(
                6,
                1);
}

/// Create Current Scan Panel
////////////////////////////////////////////////////////

void ScannerWindow::createCurrentScanPanel()
{
    //////////////////////////////////////////////////////
    /// Panel
    //////////////////////////////////////////////////////

    m_currentScanPanel =
            new QGroupBox("Current Scan");

    QVBoxLayout* mainLayout =
            new QVBoxLayout(
                m_currentScanPanel);

    mainLayout->setContentsMargins(
                20,
                20,
                20,
                20);

    mainLayout->setSpacing(20);

    //////////////////////////////////////////////////////
    /// Fonts
    //////////////////////////////////////////////////////

    QFont titleFont;
    titleFont.setPointSize(11);
    titleFont.setBold(true);

    QFont qrFont;
    qrFont.setPointSize(18);
    qrFont.setBold(true);

    //////////////////////////////////////////////////////
    /// QR Title
    //////////////////////////////////////////////////////

    QLabel* qrTitle =
            new QLabel("QR Code");

    qrTitle->setFont(titleFont);

    mainLayout->addWidget(qrTitle);

    //////////////////////////////////////////////////////
    /// QR Display
    //////////////////////////////////////////////////////

    m_qrCodeEdit =
            new QPlainTextEdit;

    m_qrCodeEdit->setReadOnly(true);

    m_qrCodeEdit->setPlainText(
                "Waiting for scanner...");

    m_qrCodeEdit->setFont(qrFont);

    m_qrCodeEdit->setMinimumHeight(130);

    m_qrCodeEdit->setMaximumHeight(150);

    m_qrCodeEdit->setLineWrapMode(
                QPlainTextEdit::WidgetWidth);

    mainLayout->addWidget(
                m_qrCodeEdit);

    //////////////////////////////////////////////////////
    /// Information Layout
    //////////////////////////////////////////////////////

    QGridLayout* infoLayout =
            new QGridLayout;

    infoLayout->setHorizontalSpacing(20);

    infoLayout->setVerticalSpacing(15);

    //////////////////////////////////////////////////////
    /// Time
    //////////////////////////////////////////////////////

    QLabel* timeTitle =
            new QLabel("Scan Time");

    timeTitle->setFont(titleFont);

    m_scanTimeLabel =
            new QLabel("--:--:--.---");

    infoLayout->addWidget(
                timeTitle,
                0,
                0);

    infoLayout->addWidget(
                m_scanTimeLabel,
                0,
                1);

    //////////////////////////////////////////////////////
    /// Validation
    //////////////////////////////////////////////////////

    QLabel* validationTitle =
            new QLabel("Validation");

    validationTitle->setFont(titleFont);

    QFont validationFont;
    validationFont.setPointSize(12);
    validationFont.setBold(true);

    m_validationLabel =
            new QLabel("Waiting...");

    m_validationLabel->setFont(
                validationFont);

    infoLayout->addWidget(
                validationTitle,
                1,
                0);

    infoLayout->addWidget(
                m_validationLabel,
                1,
                1);

    infoLayout->setColumnStretch(
                1,
                1);

    mainLayout->addLayout(
                infoLayout);

    mainLayout->addStretch();
}

////////////////////////////////////////////////////////
/// Create History Panel
////////////////////////////////////////////////////////

void ScannerWindow::createHistoryPanel()
{
    //////////////////////////////////////////////////////
    /// Panel
    //////////////////////////////////////////////////////

    m_historyPanel =
            new QGroupBox("Live Scan History");

    QVBoxLayout* layout =
            new QVBoxLayout(
                m_historyPanel);

    layout->setContentsMargins(
                15,
                20,
                15,
                15);

    layout->setSpacing(10);

    //////////////////////////////////////////////////////
    /// History Table
    //////////////////////////////////////////////////////

    m_historyTable =
            new QTableWidget;

    m_historyTable->setColumnCount(5);

    QStringList headers;

    headers
            << "Time"
            << "QR Code"
            << "Status"
            << "Batch"
            << "Remarks";

    m_historyTable->setHorizontalHeaderLabels(
                headers);

    //////////////////////////////////////////////////////
    /// Selection
    //////////////////////////////////////////////////////

    m_historyTable->setSelectionBehavior(
                QAbstractItemView::SelectRows);

    m_historyTable->setSelectionMode(
                QAbstractItemView::SingleSelection);

    m_historyTable->setEditTriggers(
                QAbstractItemView::NoEditTriggers);

    m_historyTable->setAlternatingRowColors(
                true);

    m_historyTable->setSortingEnabled(
                false);

    m_historyTable->setWordWrap(
                false);

    m_historyTable->setShowGrid(
                true);

    m_historyTable->verticalHeader()->setVisible(
                false);

    //////////////////////////////////////////////////////
    /// Header
    //////////////////////////////////////////////////////

    QHeaderView* header =
            m_historyTable->horizontalHeader();

    header->setStretchLastSection(
                true);

    header->setSectionResizeMode(
                0,
                QHeaderView::ResizeToContents);

    header->setSectionResizeMode(
                1,
                QHeaderView::Stretch);

    header->setSectionResizeMode(
                2,
                QHeaderView::ResizeToContents);

    header->setSectionResizeMode(
                3,
                QHeaderView::ResizeToContents);

    header->setSectionResizeMode(
                4,
                QHeaderView::Stretch);

    //////////////////////////////////////////////////////
    /// Rows
    //////////////////////////////////////////////////////

    m_historyTable->setRowCount(0);

    layout->addWidget(
                m_historyTable);
}

////////////////////////////////////////////////////////
/// Create Bottom Panel
////////////////////////////////////////////////////////

void ScannerWindow::createBottomPanel()
{
    //////////////////////////////////////////////////////
    /// Bottom Frame
    //////////////////////////////////////////////////////

    m_bottomPanel =
            new QFrame;

    m_bottomPanel->setFrameShape(
                QFrame::StyledPanel);

    QHBoxLayout* layout =
            new QHBoxLayout(
                m_bottomPanel);

    layout->setContentsMargins(
                10,
                10,
                10,
                10);

    layout->setSpacing(15);

    //////////////////////////////////////////////////////
    /// Discover
    //////////////////////////////////////////////////////

    m_discoverButton =
            new QPushButton("Discover");

    m_discoverButton->setMinimumHeight(40);

    layout->addWidget(
                m_discoverButton);

    //////////////////////////////////////////////////////
    /// Connect
    //////////////////////////////////////////////////////

    m_connectButton =
            new QPushButton("Connect");

    m_connectButton->setMinimumHeight(40);

    layout->addWidget(
                m_connectButton);

    //////////////////////////////////////////////////////
    /// Disconnect
    //////////////////////////////////////////////////////

    m_disconnectButton =
            new QPushButton("Disconnect");

    m_disconnectButton->setMinimumHeight(40);

    layout->addWidget(
                m_disconnectButton);

    //////////////////////////////////////////////////////
    /// Stretch
    //////////////////////////////////////////////////////

    layout->addStretch();

    //////////////////////////////////////////////////////
    /// Clear History
    //////////////////////////////////////////////////////

    m_clearHistoryButton =
            new QPushButton("Clear History");

    m_clearHistoryButton->setMinimumHeight(40);

    layout->addWidget(
                m_clearHistoryButton);
}

////////////////////////////////////////////////////////
/// Create Connections
////////////////////////////////////////////////////////

void ScannerWindow::createConnections()
{
    //////////////////////////////////////////////////////
    /// Scanner Manager
    //////////////////////////////////////////////////////

    if (m_scannerManager)
    {
        connect(m_scannerManager,
                &ScannerManager::connected,
                this,
                &ScannerWindow::onConnected,
                Qt::UniqueConnection);

        connect(m_scannerManager,
                &ScannerManager::disconnected,
                this,
                &ScannerWindow::onDisconnected,
                Qt::UniqueConnection);

        connect(m_scannerManager,
                &ScannerManager::connectionLost,
                this,
                &ScannerWindow::onConnectionLost,
                Qt::UniqueConnection);
    }

    //////////////////////////////////////////////////////
    /// Scanner Service
    //////////////////////////////////////////////////////

    if (m_scannerService)
    {
        connect(m_scannerService,
                &ScannerService::scanReceived,
                this,
                &ScannerWindow::onScanReceived,
                Qt::UniqueConnection);

        connect(m_scannerService,
                &ScannerService::batchNotLoaded,
                this,
                &ScannerWindow::onBatchNotLoaded,
                Qt::UniqueConnection);

        connect(m_scannerService,
                &ScannerService::codeFound,
                this,
                &ScannerWindow::onCodeFound,
                Qt::UniqueConnection);

        connect(m_scannerService,
                &ScannerService::codeNotFound,
                this,
                &ScannerWindow::onCodeNotFound,
                Qt::UniqueConnection);

        connect(m_scannerService,
                &ScannerService::duplicateCode,
                this,
                &ScannerWindow::onDuplicateCode,
                Qt::UniqueConnection);
    }

    //////////////////////////////////////////////////////
    /// Buttons
    //////////////////////////////////////////////////////

    connect(m_discoverButton,
            &QPushButton::clicked,
            this,
            &ScannerWindow::discoverScanner);

    connect(m_connectButton,
            &QPushButton::clicked,
            this,
            &ScannerWindow::connectScanner);

    connect(m_disconnectButton,
            &QPushButton::clicked,
            this,
            &ScannerWindow::disconnectScanner);

    connect(m_clearHistoryButton,
            &QPushButton::clicked,
            this,
            &ScannerWindow::clearHistory);
}

////////////////////////////////////////////////////////
/// Connected
////////////////////////////////////////////////////////

void ScannerWindow::onConnected()
{
    setConnectionStatus("Connected");

    setActivityStatus("Idle");

    m_heartbeatLabel->setText(
                QDateTime::currentDateTime()
                .toString("hh:mm:ss.zzz"));
}

////////////////////////////////////////////////////////
/// Disconnected
////////////////////////////////////////////////////////

void ScannerWindow::onDisconnected()
{
    setConnectionStatus("Disconnected");

    setActivityStatus("Idle");
}

////////////////////////////////////////////////////////
/// Connection Lost
////////////////////////////////////////////////////////

void ScannerWindow::onConnectionLost()
{
    setConnectionStatus("Reconnecting...");

    setActivityStatus("Idle");
}

////////////////////////////////////////////////////////
/// Scan Received
////////////////////////////////////////////////////////

void ScannerWindow::onScanReceived(
        const QString& code)
{
    //////////////////////////////////////////////////////
    /// Show Scan Immediately
    //////////////////////////////////////////////////////

    m_qrCodeEdit->setPlainText(code);

    //////////////////////////////////////////////////////
    /// Time
    //////////////////////////////////////////////////////

    QString time =
            QDateTime::currentDateTime()
            .toString("hh:mm:ss.zzz");

    m_scanTimeLabel->setText(time);

    //////////////////////////////////////////////////////
    /// Scanner Activity
    //////////////////////////////////////////////////////

    setActivityStatus("Scanning");

    //////////////////////////////////////////////////////
    /// Waiting For Validation
    //////////////////////////////////////////////////////

    setValidationStatus("Waiting...");

    //////////////////////////////////////////////////////
    /// History
    //////////////////////////////////////////////////////

    addHistoryItem(
                code,
                "Waiting...",
                "-",
                "Pending Validation");

    //////////////////////////////////////////////////////
    /// Heartbeat
    //////////////////////////////////////////////////////

    m_heartbeatLabel->setText(time);

    //////////////////////////////////////////////////////
    /// Scanner Returns Idle
    //////////////////////////////////////////////////////

    setActivityStatus("Idle");
}

////////////////////////////////////////////////////////
/// No Batch Loaded
////////////////////////////////////////////////////////

void ScannerWindow::onBatchNotLoaded(
        const QString& code)
{
    Q_UNUSED(code)

    setValidationStatus("NO BATCH LOADED");

    if (m_lastHistoryRow >= 0)
    {
        m_historyTable->item(
                    m_lastHistoryRow,
                    2)->setText("NO BATCH");

        m_historyTable->item(
                    m_lastHistoryRow,
                    3)->setText("-");

        m_historyTable->item(
                    m_lastHistoryRow,
                    4)->setText("No Batch Loaded");
    }
}
////////////////////////////////////////////////////////
/// Code Found
////////////////////////////////////////////////////////

void ScannerWindow::onCodeFound(
        const QString& code)
{
    Q_UNUSED(code)

    setValidationStatus("VALID");

    if (m_lastHistoryRow >= 0)
    {
        m_historyTable->item(
                    m_lastHistoryRow,
                    2)->setText("VALID");

        m_historyTable->item(
                    m_lastHistoryRow,
                    3)->setText("Current Batch");

        m_historyTable->item(
                    m_lastHistoryRow,
                    4)->setText("Accepted");
    }
}
////////////////////////////////////////////////////////
/// Code Not Found
////////////////////////////////////////////////////////

void ScannerWindow::onCodeNotFound(
        const QString& code)
{
    Q_UNUSED(code)

    setValidationStatus("INVALID");

    if (m_lastHistoryRow >= 0)
    {
        m_historyTable->item(
                    m_lastHistoryRow,
                    2)->setText("INVALID");

        m_historyTable->item(
                    m_lastHistoryRow,
                    3)->setText("Current Batch");

        m_historyTable->item(
                    m_lastHistoryRow,
                    4)->setText("Not Found");
    }
}
////////////////////////////////////////////////////////
/// Duplicate
////////////////////////////////////////////////////////

void ScannerWindow::onDuplicateCode(
        const QString& code)
{
    Q_UNUSED(code)

    setValidationStatus("DUPLICATE");

    if (m_lastHistoryRow >= 0)
    {
        m_historyTable->item(
                    m_lastHistoryRow,
                    2)->setText("DUPLICATE");

        m_historyTable->item(
                    m_lastHistoryRow,
                    3)->setText("Current Batch");

        m_historyTable->item(
                    m_lastHistoryRow,
                    4)->setText("Already Scanned");
    }
}

void ScannerWindow::addHistoryItem(
        const QString& code,
        const QString& status,
        const QString& batch,
        const QString& remarks)
{
    int row = m_historyTable->rowCount();

    m_historyTable->insertRow(row);

    QString time =
            QDateTime::currentDateTime()
            .toString("hh:mm:ss.zzz");

    m_historyTable->setItem(
                row,
                0,
                new QTableWidgetItem(time));

    m_historyTable->setItem(
                row,
                1,
                new QTableWidgetItem(code));

    m_historyTable->setItem(
                row,
                2,
                new QTableWidgetItem(status));

    m_historyTable->setItem(
                row,
                3,
                new QTableWidgetItem(batch));

    m_historyTable->setItem(
                row,
                4,
                new QTableWidgetItem(remarks));

    m_historyTable->scrollToBottom();
}

////////////////////////////////////////////////////////
/// Connection Status
////////////////////////////////////////////////////////

void ScannerWindow::setConnectionStatus(
        const QString& status)
{
    m_connectionLabel->setText(status);
}

////////////////////////////////////////////////////////
/// Activity Status
////////////////////////////////////////////////////////

void ScannerWindow::setActivityStatus(
        const QString& activity)
{
    m_activityLabel->setText(activity);
}

////////////////////////////////////////////////////////
/// Validation Status
////////////////////////////////////////////////////////

void ScannerWindow::setValidationStatus(
        const QString& status)
{
    m_validationLabel->setText(status);
}

////////////////////////////////////////////////////////
/// Discover Scanner
////////////////////////////////////////////////////////

void ScannerWindow::discoverScanner()
{
    setConnectionStatus("Scanner Found");

    m_scannerLabel->setText("Keyence SR-1000");

    m_ipLabel->setText("192.168.100.100");
}
////////////////////////////////////////////////////////
/// Connect Scanner
////////////////////////////////////////////////////////

void ScannerWindow::connectScanner()
{
    if (!m_scannerManager)
    {
        return;
    }

    setConnectionStatus("Connecting...");

    bool ok = m_scannerManager->connectScanner(
                    "192.168.100.100",
                    9004);

    if (!ok)
    {
        setConnectionStatus("Connection Failed");
    }
}
/// Disconnect Scanner
////////////////////////////////////////////////////////

void ScannerWindow::disconnectScanner()
{
    if (!m_scannerManager)
    {
        return;
    }

    m_scannerManager->disconnectScanner();
}

////////////////////////////////////////////////////////
/// Clear History
////////////////////////////////////////////////////////

void ScannerWindow::clearHistory()
{
    m_historyTable->setRowCount(0);

    m_qrCodeEdit->clear();

    m_qrCodeEdit->setPlainText(
                "Waiting for scanner...");

    m_scanTimeLabel->setText(
                "--:--:--.---");

    m_validationLabel->setText(
                "Waiting...");
}
////////////////////////////////////////////////////////
/// Apply Style
////////////////////////////////////////////////////////

void PharmaTrack::ScannerWindow::applyStyle()
{
}
}