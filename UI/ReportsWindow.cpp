#include "ReportsWindow.h"

#include <QVBoxLayout>
#include <QLabel>

namespace PharmaTrack
{

ReportsWindow::ReportsWindow(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

ReportsWindow::~ReportsWindow()
{
}

void ReportsWindow::setupUi()
{
    auto* layout = new QVBoxLayout(this);

    layout->setContentsMargins(40,40,40,40);
    layout->setSpacing(15);

    m_title = new QLabel("Reports");

    m_title->setStyleSheet(
        "font-size:30px;"
        "font-weight:700;"
        "color:white;"
    );

    m_subtitle = new QLabel(
        "Production reports and analytics module is under development.");

    m_subtitle->setStyleSheet(
        "font-size:15px;"
        "color:#94A3B8;"
    );

    layout->addWidget(m_title);
    layout->addWidget(m_subtitle);

    layout->addStretch();
}

}