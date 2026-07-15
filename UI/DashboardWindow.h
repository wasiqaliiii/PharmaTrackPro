#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QFrame;
class QTableWidget;
class QTimer;
QT_END_NAMESPACE

namespace PharmaTrack
{

class DashboardWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardWindow(QWidget *parent = nullptr);
    ~DashboardWindow();

    void setTotalScans(int value);
    void setAcceptedScans(int value);
    void setRejectedScans(int value);
    void setRemainingCodes(int value);

    void setScannerStatus(bool connected);
    void setPrinterStatus(bool connected);
    void setDatabaseStatus(bool connected);
    void setPLCStatus(bool connected);

    void addActivity(const QString& activity);

private slots:
    void updateClock();

private:
    void setupUi();
    void applyTheme();

    QFrame* createStatisticCard(const QString& title,
                                QLabel*& valueLabel,
                                const QString& color);

    QFrame* createStatusCard(const QString& device,
                             QLabel*& statusLabel);

private:

    QLabel* m_totalScansLabel;
    QLabel* m_acceptedLabel;
    QLabel* m_rejectedLabel;
    QLabel* m_remainingLabel;

    QLabel* m_scannerStatusLabel;
    QLabel* m_printerStatusLabel;
    QLabel* m_databaseStatusLabel;
    QLabel* m_plcStatusLabel;

    QLabel* m_clockLabel;

    QTableWidget* m_activityTable;

    QTimer* m_clockTimer;
};

}