cmake_minimum_required(VERSION 3.21)

project(PharmaTrackPro VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    Sql
    SerialPort
    Network
)

qt_standard_project_setup()

include_directories(
    ${PROJECT_SOURCE_DIR}/App
    ${PROJECT_SOURCE_DIR}/Config
    ${PROJECT_SOURCE_DIR}/Core
    ${PROJECT_SOURCE_DIR}/Database
    ${PROJECT_SOURCE_DIR}/Hardware
    ${PROJECT_SOURCE_DIR}/Logs
    ${PROJECT_SOURCE_DIR}/Models
    ${PROJECT_SOURCE_DIR}/Reports
    ${PROJECT_SOURCE_DIR}/Resources
    ${PROJECT_SOURCE_DIR}/Services
    ${PROJECT_SOURCE_DIR}/UI
    ${PROJECT_SOURCE_DIR}/Utils
)

set(SOURCES

    # App
    App/main.cpp
    App/Application.cpp

    # UI
    UI/MainWindow.cpp
    UI/DashboardWindow.cpp
    UI/ScannerWindow.cpp
    UI/GeneratorWindow.cpp
    UI/ReportsWindow.cpp
    UI/SettingsWindow.cpp

    # Hardware
    Hardware/SerialPortManager.cpp
    Hardware/ScannerManager.cpp

    # Services
    Services/ScannerService.cpp
    Services/VerificationService.cpp

    # Models
    Models/SerialNumber.cpp
    Models/ScanLog.cpp
    Models/Batch.cpp
    Models/Product.cpp
    Models/User.cpp
    Models/Report.cpp

    # Utils
    Utils/PathManager.cpp
    Utils/FileManager.cpp
    Utils/JsonManager.cpp
)

set(HEADERS

    # App
    App/Application.h

    # UI
    UI/MainWindow.h
    UI/DashboardWindow.h
    UI/ScannerWindow.h
    UI/GeneratorWindow.h
    UI/ReportsWindow.h
    UI/SettingsWindow.h

    # Hardware
    Hardware/SerialPortManager.h
    Hardware/ScannerManager.h

    # Services
    Services/ScannerService.h
    Services/VerificationService.h

    # Models
    Models/SerialNumber.h
    Models/ScanLog.h
    Models/Batch.h
    Models/Product.h
    Models/User.h
    Models/Report.h

    # Utils
    Utils/PathManager.h
    Utils/FileManager.h
    Utils/JsonManager.h
)

set(UIS
    UI/MainWindow.ui
)

qt_add_executable(PharmaTrackPro
    ${SOURCES}
    ${HEADERS}
    ${UIS}
)

target_link_libraries(PharmaTrackPro PRIVATE
    Qt6::Widgets
    Qt6::Sql
    Qt6::SerialPort
    Qt6::Network
)

set_target_properties(PharmaTrackPro PROPERTIES
    WIN32_EXECUTABLE TRUE
)