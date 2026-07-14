#include "MainWindow.h"

namespace PharmaTrack
{

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("PharmaTrack Pro");
    resize(1400, 800);
}

MainWindow::~MainWindow()
{
}

}