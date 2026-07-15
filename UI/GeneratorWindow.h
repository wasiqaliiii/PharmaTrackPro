#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE

class QLabel;

QT_END_NAMESPACE

namespace PharmaTrack
{

class GeneratorWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GeneratorWindow(QWidget *parent = nullptr);
    ~GeneratorWindow();

private:
    void setupUi();

private:
    QLabel* m_title;
    QLabel* m_subtitle;
};

}