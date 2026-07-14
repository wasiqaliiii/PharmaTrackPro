#pragma once

#include <QMainWindow>

namespace PharmaTrack
{

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

}