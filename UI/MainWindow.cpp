#include "MainWindow.h"

#include "DashboardWindow.h"
#include "ScannerWindow.h"
#include "GeneratorWindow.h"
#include "ReportsWindow.h"
#include "SettingsWindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QListWidget>
#include <QLabel>
#include <QFrame>
#include <QWidget>

#include <QStatusBar>
#include <QListWidgetItem>

namespace PharmaTrack
{

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_centralWidget(nullptr),
      m_headerWidget(nullptr),
      m_sidebarWidget(nullptr),
      m_contentWidget(nullptr),
      m_titleLabel(nullptr),
      m_userLabel(nullptr),
      m_navigation(nullptr),
      m_stack(nullptr),
      m_dashboardPage(nullptr),
      m_scannerPage(nullptr),
      m_generatorPage(nullptr),
      m_reportsPage(nullptr),
      m_settingsPage(nullptr)
{
    resize(1600,900);

    setWindowTitle("PharmaTrack Pro");

    setupUi();

    applyTheme();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUi()
{
    m_centralWidget = new QWidget(this);

    setCentralWidget(m_centralWidget);

    auto* rootLayout = new QVBoxLayout(m_centralWidget);

    rootLayout->setContentsMargins(0,0,0,0);

    rootLayout->setSpacing(0);

    //-------------------------------------------------------
    // Header
    //-------------------------------------------------------

    createHeader();

    rootLayout->addWidget(m_headerWidget);

    //-------------------------------------------------------
    // Body
    //-------------------------------------------------------

    auto* bodyLayout = new QHBoxLayout;

    bodyLayout->setContentsMargins(0,0,0,0);

    bodyLayout->setSpacing(0);

    //-------------------------------------------------------
    // Sidebar
    //-------------------------------------------------------

    createSidebar();

    bodyLayout->addWidget(m_sidebarWidget);

    //-------------------------------------------------------
    // Content Area
    //-------------------------------------------------------

    m_contentWidget = new QWidget;

    auto* contentLayout =
        new QVBoxLayout(m_contentWidget);

    contentLayout->setContentsMargins(20,20,20,20);

    contentLayout->setSpacing(0);

    createPages();

    contentLayout->addWidget(m_stack);

    bodyLayout->addWidget(m_contentWidget);

    rootLayout->addLayout(bodyLayout);
}




/// -------------Part 02 -----------


void MainWindow::createHeader()
{
    m_headerWidget = new QFrame;

    m_headerWidget->setObjectName("Header");

    m_headerWidget->setFixedHeight(70);

    auto* layout = new QHBoxLayout(m_headerWidget);

    layout->setContentsMargins(25,15,25,15);

    layout->setSpacing(20);

    //-----------------------------------------------------
    // Application Title
    //-----------------------------------------------------

    m_titleLabel = new QLabel("PharmaTrack Pro");

    m_titleLabel->setStyleSheet(
        "font-size:26px;"
        "font-weight:700;"
        "color:white;"
    );

    layout->addWidget(m_titleLabel);

    layout->addStretch();

    //-----------------------------------------------------
    // Scanner Status
    //-----------------------------------------------------

    QLabel* scannerStatus = new QLabel("🟢 Scanner");

    scannerStatus->setObjectName("StatusIndicator");

    layout->addWidget(scannerStatus);

    //-----------------------------------------------------
    // Database Status
    //-----------------------------------------------------

    QLabel* databaseStatus = new QLabel("🟢 Database");

    databaseStatus->setObjectName("StatusIndicator");

    layout->addWidget(databaseStatus);

    //-----------------------------------------------------
    // Printer Status
    //-----------------------------------------------------

    QLabel* printerStatus = new QLabel("🔴 Printer");

    printerStatus->setObjectName("StatusIndicator");

    layout->addWidget(printerStatus);

    //-----------------------------------------------------
    // PLC Status
    //-----------------------------------------------------

    QLabel* plcStatus = new QLabel("🟡 PLC");

    plcStatus->setObjectName("StatusIndicator");

    layout->addWidget(plcStatus);

    layout->addSpacing(20);

    //-----------------------------------------------------
    // User
    //-----------------------------------------------------

    m_userLabel = new QLabel("Administrator");

    m_userLabel->setStyleSheet(
        "font-size:15px;"
        "font-weight:600;"
        "color:white;"
    );

    layout->addWidget(m_userLabel);
}

void MainWindow::createSidebar()
{
    m_sidebarWidget = new QFrame;

    m_sidebarWidget->setObjectName("Sidebar");

    m_sidebarWidget->setFixedWidth(240);

    auto* layout = new QVBoxLayout(m_sidebarWidget);

    layout->setContentsMargins(15,20,15,20);

    layout->setSpacing(15);

    //-----------------------------------------------------
    // Navigation Title
    //-----------------------------------------------------

    QLabel* navigationTitle = new QLabel("Navigation");

    navigationTitle->setStyleSheet(
        "font-size:18px;"
        "font-weight:700;"
        "color:white;"
    );

    layout->addWidget(navigationTitle);

    //-----------------------------------------------------
    // Navigation Menu
    //-----------------------------------------------------

    m_navigation = new QListWidget;

    m_navigation->setObjectName("NavigationList");

    m_navigation->setSpacing(8);

    m_navigation->setFixedWidth(200);

    m_navigation->addItem("🏠 Dashboard");
    m_navigation->addItem("📷 Scanner");
    m_navigation->addItem("🧬 Generator");
    m_navigation->addItem("📊 Reports");
    m_navigation->addItem("⚙ Settings");

    m_navigation->setCurrentRow(0);

    connect(
        m_navigation,
        &QListWidget::currentItemChanged,
        this,
        &MainWindow::changePage);

    layout->addWidget(m_navigation);

    layout->addStretch();

    //-----------------------------------------------------
    // Footer
    //-----------------------------------------------------

    QLabel* versionLabel = new QLabel("Version 1.0.0");

    versionLabel->setAlignment(Qt::AlignCenter);

    versionLabel->setStyleSheet(
        "color:#94A3B8;"
        "font-size:12px;"
    );

    layout->addWidget(versionLabel);
}

/////// ------ Part 03 ------------------

void MainWindow::createPages()
{
    //-----------------------------------------------------
    // Create Stack
    //-----------------------------------------------------

    m_stack = new QStackedWidget;

    //-----------------------------------------------------
    // Create Pages
    //-----------------------------------------------------

    m_dashboardPage = new DashboardWindow;

    m_scannerPage = new ScannerWindow;

    m_generatorPage = new GeneratorWindow;

    m_reportsPage = new ReportsWindow;

    m_settingsPage = new SettingsWindow;

    //-----------------------------------------------------
    // Add Pages
    //-----------------------------------------------------

    m_stack->addWidget(m_dashboardPage);

    m_stack->addWidget(m_scannerPage);

    m_stack->addWidget(m_generatorPage);

    m_stack->addWidget(m_reportsPage);

    m_stack->addWidget(m_settingsPage);

    //-----------------------------------------------------
    // Default Page
    //-----------------------------------------------------

    m_stack->setCurrentIndex(0);
}

void MainWindow::changePage(QListWidgetItem* current,
                            QListWidgetItem* previous)
{
    Q_UNUSED(previous);

    if (!current)
        return;

    int index = m_navigation->row(current);

    if (index >= 0 && index < m_stack->count())
    {
        m_stack->setCurrentIndex(index);
    }
}

// --------- Part 04 ---------

void MainWindow::applyTheme()
{
    setStyleSheet(R"(

QMainWindow
{
    background-color: #0F172A;
}

QWidget
{
    background-color: #0F172A;
    color: white;
    font-family: "Segoe UI";
    font-size: 13px;
}

QFrame#Header
{
    background-color: #1E293B;
    border-bottom: 1px solid #334155;
}

QFrame#Sidebar
{
    background-color: #111827;
    border-right: 1px solid #334155;
}

QLabel
{
    color: white;
}

QLabel#StatusIndicator
{
    background-color: #334155;
    padding: 6px 12px;
    border-radius: 10px;
    color: white;
    font-weight: 600;
}

QListWidget#NavigationList
{
    background: transparent;
    border: none;
    outline: none;
    color: white;
    font-size: 15px;
}

QListWidget#NavigationList::item
{
    height: 48px;
    padding-left: 15px;
    border-radius: 10px;
    margin-top: 3px;
    margin-bottom: 3px;
}

QListWidget#NavigationList::item:selected
{
    background-color: #2563EB;
    color: white;
}

QListWidget#NavigationList::item:hover
{
    background-color: #334155;
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

QStackedWidget
{
    border: none;
}

)");

    statusBar()->hide();
}

}