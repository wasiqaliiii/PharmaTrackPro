#include "DashboardWindow.h"

#include <QFrame>
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QTableWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QDateTime>

namespace PharmaTrack
{

DashboardWindow::DashboardWindow(QWidget *parent)
    : QWidget(parent),
      m_totalScansLabel(nullptr),
      m_acceptedLabel(nullptr),
      m_rejectedLabel(nullptr),
      m_remainingLabel(nullptr),
      m_scannerStatusLabel(nullptr),
      m_printerStatusLabel(nullptr),
      m_databaseStatusLabel(nullptr),
      m_plcStatusLabel(nullptr),
      m_clockLabel(nullptr),
      m_activityTable(nullptr),
      m_clockTimer(new QTimer(this))
{
    setupUi();
    applyTheme();

    connect(m_clockTimer,
            &QTimer::timeout,
            this,
            &DashboardWindow::updateClock);

    m_clockTimer->start(1000);

    updateClock();

    addActivity("Dashboard initialized");
    addActivity("System ready");
}

DashboardWindow::~DashboardWindow()
{
}

void DashboardWindow::setupUi()
{
    auto *mainLayout = new QVBoxLayout(this);

    mainLayout->setContentsMargins(30,30,30,30);
    mainLayout->setSpacing(20);

    //-------------------------------------------------------
    // Header
    //-------------------------------------------------------

    QLabel *title = new QLabel("Dashboard");

    title->setStyleSheet(
        "font-size:30px;"
        "font-weight:700;"
        "color:white;"
    );

    QLabel *subtitle = new QLabel(
        "Welcome to PharmaTrack Pro");

    subtitle->setStyleSheet(
        "font-size:14px;"
        "color:#94A3B8;"
    );

    mainLayout->addWidget(title);
    mainLayout->addWidget(subtitle);

    //-------------------------------------------------------
    // Statistic Cards
    //-------------------------------------------------------

    auto *cardLayout = new QGridLayout;

    cardLayout->setHorizontalSpacing(20);
    cardLayout->setVerticalSpacing(20);

    cardLayout->addWidget(
        createStatisticCard(
            "Total Scans",
            m_totalScansLabel,
            "#2563EB"),
        0,0);

    cardLayout->addWidget(
        createStatisticCard(
            "Accepted",
            m_acceptedLabel,
            "#22C55E"),
        0,1);

    cardLayout->addWidget(
        createStatisticCard(
            "Rejected",
            m_rejectedLabel,
            "#EF4444"),
        0,2);

    cardLayout->addWidget(
        createStatisticCard(
            "Remaining",
            m_remainingLabel,
            "#F59E0B"),
        0,3);

    mainLayout->addLayout(cardLayout);

    //-------------------------------------------------------
    // Middle Layout
    //-------------------------------------------------------

    auto *middleLayout = new QHBoxLayout;

    middleLayout->setSpacing(20);

    //-------------------------------------------------------
    // Device Status
    //-------------------------------------------------------

    auto *statusFrame = new QFrame;

    statusFrame->setObjectName("Card");

    auto *statusLayout = new QVBoxLayout(statusFrame);

    QLabel *statusTitle =
        new QLabel("Device Status");

    statusTitle->setStyleSheet(
        "font-size:20px;"
        "font-weight:600;"
        "color:white;"
    );

    statusLayout->addWidget(statusTitle);

    statusLayout->addSpacing(15);

    statusLayout->addWidget(
        createStatusCard(
            "Scanner",
            m_scannerStatusLabel));

    statusLayout->addWidget(
        createStatusCard(
            "Printer",
            m_printerStatusLabel));

    statusLayout->addWidget(
        createStatusCard(
            "Database",
            m_databaseStatusLabel));

    statusLayout->addWidget(
        createStatusCard(
            "PLC",
            m_plcStatusLabel));

    statusLayout->addStretch();

    middleLayout->addWidget(statusFrame,1);

    //-------------------------------------------------------
    // Recent Activity
    //-------------------------------------------------------

    auto *activityFrame = new QFrame;

    activityFrame->setObjectName("Card");

    auto *activityLayout =
        new QVBoxLayout(activityFrame);

    QLabel *activityTitle =
        new QLabel("Recent Activity");

    activityTitle->setStyleSheet(
        "font-size:20px;"
        "font-weight:600;"
        "color:white;"
    );

    activityLayout->addWidget(activityTitle);

    m_activityTable =
        new QTableWidget;

    m_activityTable->setColumnCount(2);

    QStringList headers;

    headers << "Time"
            << "Activity";

    m_activityTable->setHorizontalHeaderLabels(headers);

    m_activityTable->horizontalHeader()
            ->setStretchLastSection(true);

    m_activityTable->horizontalHeader()
            ->setSectionResizeMode(
                QHeaderView::ResizeToContents);

    m_activityTable->verticalHeader()
            ->hide();

    m_activityTable->setSelectionMode(
        QAbstractItemView::NoSelection);

    m_activityTable->setEditTriggers(
        QAbstractItemView::NoEditTriggers);

    m_activityTable->setAlternatingRowColors(true);

    activityLayout->addWidget(m_activityTable);

    middleLayout->addWidget(activityFrame,2);

    mainLayout->addLayout(middleLayout);

    //-------------------------------------------------------
    // Clock
    //-------------------------------------------------------

    auto *clockFrame = new QFrame;

    clockFrame->setObjectName("Card");

    auto *clockLayout =
        new QHBoxLayout(clockFrame);

    QLabel *clockTitle =
        new QLabel("Current Time");

    clockTitle->setStyleSheet(
        "font-size:18px;"
        "font-weight:600;"
        "color:white;"
    );

    m_clockLabel =
        new QLabel;

    m_clockLabel->setAlignment(
        Qt::AlignRight);

    m_clockLabel->setStyleSheet(
        "font-size:18px;"
        "font-weight:600;"
        "color:#22C55E;"
    );

    clockLayout->addWidget(clockTitle);

    clockLayout->addStretch();

    clockLayout->addWidget(m_clockLabel);

    mainLayout->addWidget(clockFrame);

    //-------------------------------------------------------
    // Default Values
    //-------------------------------------------------------

    setTotalScans(0);
    setAcceptedScans(0);
    setRejectedScans(0);
    setRemainingCodes(0);

    setScannerStatus(false);
    setPrinterStatus(false);
    setDatabaseStatus(false);
    setPLCStatus(false);
}


// ------------- Part 02 ---------------------


QFrame* DashboardWindow::createStatisticCard(const QString& title,
                                             QLabel*& valueLabel,
                                             const QString& color)
{
    QFrame* card = new QFrame;

    card->setObjectName("StatCard");

    auto* layout = new QVBoxLayout(card);

    layout->setContentsMargins(20,20,20,20);

    layout->setSpacing(10);

    QLabel* titleLabel = new QLabel(title);

    titleLabel->setStyleSheet(
        "font-size:14px;"
        "color:#94A3B8;"
        "font-weight:600;"
    );

    valueLabel = new QLabel("0");

    valueLabel->setAlignment(Qt::AlignCenter);

    valueLabel->setStyleSheet(QString(
        "font-size:36px;"
        "font-weight:700;"
        "color:%1;"
    ).arg(color));

    layout->addWidget(titleLabel);

    layout->addStretch();

    layout->addWidget(valueLabel);

    layout->addStretch();

    return card;
}

QFrame* DashboardWindow::createStatusCard(const QString& device,
                                          QLabel*& statusLabel)
{
    QFrame* card = new QFrame;

    auto* layout = new QHBoxLayout(card);

    layout->setContentsMargins(10,10,10,10);

    QLabel* deviceLabel = new QLabel(device);

    deviceLabel->setStyleSheet(
        "font-size:15px;"
        "font-weight:600;"
        "color:white;"
    );

    statusLabel = new QLabel;

    statusLabel->setMinimumWidth(90);

    statusLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(deviceLabel);

    layout->addStretch();

    layout->addWidget(statusLabel);

    return card;
}

void DashboardWindow::applyTheme()
{
    setStyleSheet(R"(

DashboardWindow
{
    background:#0F172A;
}

QFrame#Card
{
    background:#1E293B;
    border-radius:12px;
    border:1px solid #334155;
}

QFrame#StatCard
{
    background:#1E293B;
    border-radius:12px;
    border:1px solid #334155;
}

QFrame#StatCard:hover
{
    background:#26364A;
}

QTableWidget
{
    background:#1E293B;
    color:white;

    border:none;

    gridline-color:#334155;

    selection-background-color:#2563EB;

    alternate-background-color:#223045;
}

QHeaderView::section
{
    background:#334155;

    color:white;

    border:none;

    padding:8px;

    font-weight:600;
}

QScrollBar:vertical
{
    background:#1E293B;

    width:12px;

    border:none;
}

QScrollBar::handle:vertical
{
    background:#475569;

    border-radius:6px;
}

QScrollBar::handle:vertical:hover
{
    background:#64748B;
}

QScrollBar::add-line:vertical,
QScrollBar::sub-line:vertical
{
    height:0px;
}

QScrollBar:horizontal
{
    height:0px;
}

)");
}


/// -------------- Part 03 -------------------


void DashboardWindow::setTotalScans(int value)
{
    if (m_totalScansLabel)
        m_totalScansLabel->setText(QString::number(value));
}

void DashboardWindow::setAcceptedScans(int value)
{
    if (m_acceptedLabel)
        m_acceptedLabel->setText(QString::number(value));
}

void DashboardWindow::setRejectedScans(int value)
{
    if (m_rejectedLabel)
        m_rejectedLabel->setText(QString::number(value));
}

void DashboardWindow::setRemainingCodes(int value)
{
    if (m_remainingLabel)
        m_remainingLabel->setText(QString::number(value));
}

void DashboardWindow::setScannerStatus(bool connected)
{
    if (!m_scannerStatusLabel)
        return;

    if (connected)
    {
        m_scannerStatusLabel->setText("● ONLINE");
        m_scannerStatusLabel->setStyleSheet(
            "background:#22C55E;"
            "color:white;"
            "padding:6px 12px;"
            "border-radius:8px;"
            "font-weight:600;"
        );
    }
    else
    {
        m_scannerStatusLabel->setText("● OFFLINE");
        m_scannerStatusLabel->setStyleSheet(
            "background:#EF4444;"
            "color:white;"
            "padding:6px 12px;"
            "border-radius:8px;"
            "font-weight:600;"
        );
    }
}

void DashboardWindow::setPrinterStatus(bool connected)
{
    if (!m_printerStatusLabel)
        return;

    if (connected)
    {
        m_printerStatusLabel->setText("● ONLINE");
        m_printerStatusLabel->setStyleSheet(
            "background:#22C55E;"
            "color:white;"
            "padding:6px 12px;"
            "border-radius:8px;"
            "font-weight:600;"
        );
    }
    else
    {
        m_printerStatusLabel->setText("● OFFLINE");
        m_printerStatusLabel->setStyleSheet(
            "background:#EF4444;"
            "color:white;"
            "padding:6px 12px;"
            "border-radius:8px;"
            "font-weight:600;"
        );
    }
}

void DashboardWindow::setDatabaseStatus(bool connected)
{
    if (!m_databaseStatusLabel)
        return;

    if (connected)
    {
        m_databaseStatusLabel->setText("● ONLINE");
        m_databaseStatusLabel->setStyleSheet(
            "background:#22C55E;"
            "color:white;"
            "padding:6px 12px;"
            "border-radius:8px;"
            "font-weight:600;"
        );
    }
    else
    {
        m_databaseStatusLabel->setText("● OFFLINE");
        m_databaseStatusLabel->setStyleSheet(
            "background:#EF4444;"
            "color:white;"
            "padding:6px 12px;"
            "border-radius:8px;"
            "font-weight:600;"
        );
    }
}

void DashboardWindow::setPLCStatus(bool connected)
{
    if (!m_plcStatusLabel)
        return;

    if (connected)
    {
        m_plcStatusLabel->setText("● ONLINE");
        m_plcStatusLabel->setStyleSheet(
            "background:#22C55E;"
            "color:white;"
            "padding:6px 12px;"
            "border-radius:8px;"
            "font-weight:600;"
        );
    }
    else
    {
        m_plcStatusLabel->setText("● OFFLINE");
        m_plcStatusLabel->setStyleSheet(
            "background:#EF4444;"
            "color:white;"
            "padding:6px 12px;"
            "border-radius:8px;"
            "font-weight:600;"
        );
    }
}

void DashboardWindow::addActivity(const QString& activity)
{
    if (!m_activityTable)
        return;

    int row = m_activityTable->rowCount();

    m_activityTable->insertRow(row);

    QString time =
        QTime::currentTime().toString("hh:mm:ss");

    auto* timeItem =
        new QTableWidgetItem(time);

    auto* activityItem =
        new QTableWidgetItem(activity);

    timeItem->setForeground(Qt::white);
    activityItem->setForeground(Qt::white);

    m_activityTable->setItem(row,0,timeItem);
    m_activityTable->setItem(row,1,activityItem);

    m_activityTable->scrollToBottom();
}

void DashboardWindow::updateClock()
{
    if (!m_clockLabel)
        return;

    QString dateTime =
        QDateTime::currentDateTime()
        .toString("dddd, dd MMMM yyyy\nhh:mm:ss AP");

    m_clockLabel->setText(dateTime);
}

} // namespace PharmaTrack

