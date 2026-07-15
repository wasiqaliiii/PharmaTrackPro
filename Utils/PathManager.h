#pragma once

#include <QString>

namespace PharmaTrack
{

class PathManager
{
public:

    static QString applicationPath();

    static QString resourcesPath();

    static QString productionPath();

    static QString reportsPath();

    static QString exportsPath();

    static QString templatesPath();

    static QString configPath();

    static QString databasePath();

    static QString logsPath();

    static QString backupPath();

    //---------------------------------------

    static QString batchFolder(
            const QString& batchId);

    static QString serialFile(
            const QString& batchId);

    static QString batchFile(
            const QString& batchId);

    static QString scanLogFile(
            const QString& batchId);

    static QString registryFile();
};

}