#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE

class QLabel;

QT_END_NAMESPACE

namespace PharmaTrack
{

class ReportsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ReportsWindow(QWidget *parent = nullptr);
    ~ReportsWindow();

private:
    void setupUi();

private:
    QLabel* m_title;
    QLabel* m_subtitle;
};

}