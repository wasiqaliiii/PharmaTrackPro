#include "PathManager.h"

#include <QCoreApplication>

namespace PharmaTrack
{

QString PathManager::applicationPath()
{
    return QCoreApplication::applicationDirPath();
}

QString PathManager::resourcesPath()
{
    return applicationPath() + "/Resources";
}

QString PathManager::productionPath()
{
    return resourcesPath() + "/Production";
}

QString PathManager::reportsPath()
{
    return resourcesPath() + "/Reports";
}

QString PathManager::exportsPath()
{
    return resourcesPath() + "/Exports";
}

QString PathManager::templatesPath()
{
    return resourcesPath() + "/Templates";
}

QString PathManager::configPath()
{
    return resourcesPath() + "/Config";
}

QString PathManager::databasePath()
{
    return applicationPath() + "/Database";
}

QString PathManager::logsPath()
{
    return applicationPath() + "/Logs";
}

QString PathManager::backupPath()
{
    return applicationPath() + "/Backups";
}

QString PathManager::batchFolder(const QString& batchId)
{
    return productionPath() + "/" + batchId;
}

QString PathManager::serialFile(const QString& batchId)
{
    return batchFolder(batchId) + "/serials.csv";
}

QString PathManager::batchFile(const QString& batchId)
{
    return batchFolder(batchId) + "/batch.json";
}

QString PathManager::scanLogFile(const QString& batchId)
{
    return batchFolder(batchId) + "/scanlog.csv";
}

QString PathManager::registryFile()
{
    return productionPath() + "/registry.json";
}

}