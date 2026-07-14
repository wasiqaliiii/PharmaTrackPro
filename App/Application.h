#pragma once

#include <QApplication>

namespace PharmaTrack
{

class Application
{
public:
    Application(int& argc, char* argv[]);
    int run();

private:
    QApplication m_app;
};

}