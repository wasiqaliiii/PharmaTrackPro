#pragma once
#include "../Hardware/ScannerManager.h"
#include "../Services/ScannerService.h"
#include "../Services/ScannerConfigurationService.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE

class QListWidget;
class QListWidgetItem;
class QLabel;
class QStackedWidget;
class QWidget;

QT_END_NAMESPACE

namespace PharmaTrack
{

class DashboardWindow;
class ScannerWindow;
class GeneratorWindow;
class ReportsWindow;
class SettingsWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void changePage(QListWidgetItem* current,
                    QListWidgetItem* previous);

private:

    void setupUi();
    void createHeader();
    void createSidebar();
    void createPages();
    void applyTheme();

private:

    QWidget* m_centralWidget;

    QWidget* m_headerWidget;

    QWidget* m_sidebarWidget;

    QWidget* m_contentWidget;

    QLabel* m_titleLabel;

    QLabel* m_userLabel;

    QListWidget* m_navigation;

    QStackedWidget* m_stack;

    DashboardWindow* m_dashboardPage;

    ScannerWindow* m_scannerPage;

    GeneratorWindow* m_generatorPage;

    ReportsWindow* m_reportsPage;

    SettingsWindow* m_settingsPage;\
    ////////////////////////////////////////////////////////
/// Scanner Backend
////////////////////////////////////////////////////////

ScannerManager* m_scannerManager = nullptr;

ScannerService* m_scannerService = nullptr;

ScannerConfigurationService* m_configurationService = nullptr;

};

}