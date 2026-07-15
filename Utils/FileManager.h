#pragma once

#include <QString>

namespace PharmaTrack
{

class FileManager
{
public:

    //-------------------------------
    // File Operations
    //-------------------------------

    static bool fileExists(const QString& path);

    static bool deleteFile(const QString& path);

    static bool copyFile(const QString& source,
                         const QString& destination);

    static bool moveFile(const QString& source,
                         const QString& destination);

    //-------------------------------
    // Folder Operations
    //-------------------------------

    static bool folderExists(const QString& path);

    static bool createFolder(const QString& path);

    static bool deleteFolder(const QString& path);

    //-------------------------------
    // Batch Operations
    //-------------------------------

    static bool createBatchFolder(const QString& batchId);

    static bool deleteBatchFolder(const QString& batchId);
};

}