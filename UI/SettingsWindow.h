#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE

class QLabel;

QT_END_NAMESPACE

namespace PharmaTrack
{

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

private:
    void setupUi();

private:
    QLabel* m_title;
    QLabel* m_subtitle;
};

}