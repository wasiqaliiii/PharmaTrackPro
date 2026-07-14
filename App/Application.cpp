#include "Application.h"
#include "../UI/MainWindow.h"

namespace PharmaTrack
{

Application::Application(int& argc, char* argv[])
    : m_app(argc, argv)
{
}

int Application::run()
{
    PharmaTrack::MainWindow window;

    window.show();

    return m_app.exec();
}

}