#include "ScannerConfigurationService.h"

#include "../Hardware/ScannerManager.h"

#include <QDebug>

namespace PharmaTrack
{

////////////////////////////////////////////////////////
/// Constructor
////////////////////////////////////////////////////////

ScannerConfigurationService::ScannerConfigurationService(
        QObject* parent)
    : QObject(parent),
      m_scannerManager(nullptr),
      m_configured(false)
{
}

////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////

ScannerConfigurationService::~ScannerConfigurationService()
{
}

////////////////////////////////////////////////////////
/// Scanner Manager
////////////////////////////////////////////////////////

void ScannerConfigurationService::setScannerManager(
        ScannerManager* manager)
{
    m_scannerManager = manager;
}

////////////////////////////////////////////////////////
/// Information
////////////////////////////////////////////////////////

bool ScannerConfigurationService::isConfigured() const
{
    return m_configured;
}

////////////////////////////////////////////////////////
/// Configuration
////////////////////////////////////////////////////////

const ScannerConfiguration&
ScannerConfigurationService::configuration() const
{
    return m_configuration;
}

////////////////////////////////////////////////////////
/// Configure Scanner
////////////////////////////////////////////////////////

bool ScannerConfigurationService::configureScanner(
        const ScannerInfo& scanner)
{
    emit configurationStarted();

    //////////////////////////////////////////////////////
    /// Build Configuration
    //////////////////////////////////////////////////////

ScannerEndpoint endpoint =
        scanner.preferredEndpoint();

m_configuration.setConnectionType(
            endpoint.type);

m_configuration.setIpAddress(
            endpoint.ipAddress);

m_configuration.setPort(
            endpoint.port);

m_configuration.setComPort(
            endpoint.comPort);
    //////////////////////////////////////////////////////
    /// Validate
    //////////////////////////////////////////////////////

    if (!validateConfiguration(
                m_configuration))
    {
        emit configurationFailed(
                    "Invalid scanner configuration.");

        return false;
    }

    //////////////////////////////////////////////////////
    /// Apply Configuration
    //////////////////////////////////////////////////////

    if (!applyConfiguration(
                m_configuration))
    {
        emit configurationFailed(
                    "Unable to apply scanner configuration.");

        return false;
    }

    m_configured = true;

    emit scannerConfigured(scanner);

    emit configurationCompleted();

    qDebug()
            << "[ScannerConfiguration]"
            << "Scanner configured:"
            << scanner.displayName();

    return true;
}

////////////////////////////////////////////////////////
/// Apply Configuration
////////////////////////////////////////////////////////

bool ScannerConfigurationService::applyConfiguration(
        const ScannerConfiguration& configuration)
{
    if (m_scannerManager == nullptr)
    {
        emit configurationFailed(
                    "Scanner Manager not available.");

        return false;
    }

    //////////////////////////////////////////////////////
    /// Store Configuration
    //////////////////////////////////////////////////////

    m_configuration = configuration;

    //////////////////////////////////////////////////////
    /// Connect Scanner
    //////////////////////////////////////////////////////

    m_scannerManager->connectScanner(
                configuration.ipAddress(),
                configuration.port());

    return true;
}
////////////////////////////////////////////////////////
/// Disconnect Scanner
////////////////////////////////////////////////////////

void ScannerConfigurationService::disconnectScanner()
{
    if (m_scannerManager == nullptr)
    {
        return;
    }

    //////////////////////////////////////////////////////
    /// Disconnect
    //////////////////////////////////////////////////////

    m_scannerManager->disconnectScanner();

    //////////////////////////////////////////////////////
    /// Reset State
    //////////////////////////////////////////////////////

    m_configuration = ScannerConfiguration();

    m_configured = false;

    emit scannerDisconnected();

    qDebug()
    << "[ScannerConfiguration]"
    << "Scanner disconnected.";
}

////////////////////////////////////////////////////////
/// Validate Configuration
////////////////////////////////////////////////////////

bool ScannerConfigurationService::validateConfiguration(
        const ScannerConfiguration& configuration)
{
    //////////////////////////////////////////////////////
    /// IP Address
    //////////////////////////////////////////////////////

    if (configuration.ipAddress().trimmed().isEmpty())
    {
        return false;
    }

    //////////////////////////////////////////////////////
    /// Port
    //////////////////////////////////////////////////////

    if (configuration.port() == 0)
    {
        return false;
    }

    return true;
}

}