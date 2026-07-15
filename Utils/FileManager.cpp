#include "FileManager.h"
#include "PathManager.h"

#include <QDir>
#include <QFile>

namespace PharmaTrack
{

//--------------------------------------------------
// File Operations
//--------------------------------------------------

bool FileManager::fileExists(const QString& path)
{
    return QFile::exists(path);
}

bool FileManager::deleteFile(const QString& path)
{
    if(!QFile::exists(path))
        return true;

    return QFile::remove(path);
}

bool FileManager::copyFile(const QString& source,
                           const QString& destination)
{
    if(!QFile::exists(source))
        return false;

    QFile::remove(destination);

    return QFile::copy(source,destination);
}

bool FileManager::moveFile(const QString& source,
                           const QString& destination)
{
    if(!QFile::exists(source))
        return false;

    QFile::remove(destination);

    return QFile(source).rename(destination);
}

//--------------------------------------------------
// Folder Operations
//--------------------------------------------------

bool FileManager::folderExists(const QString& path)
{
    return QDir(path).exists();
}

bool FileManager::createFolder(const QString& path)
{
    QDir dir;

    return dir.mkpath(path);
}

bool FileManager::deleteFolder(const QString& path)
{
    QDir dir(path);

    if(!dir.exists())
        return true;

    return dir.removeRecursively();
}

//--------------------------------------------------
// Batch Operations
//--------------------------------------------------

bool FileManager::createBatchFolder(const QString& batchId)
{
    return createFolder(
                PathManager::batchFolder(batchId));
}

bool FileManager::deleteBatchFolder(const QString& batchId)
{
    return deleteFolder(
                PathManager::batchFolder(batchId));
}

}