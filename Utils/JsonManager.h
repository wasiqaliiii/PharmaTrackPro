#pragma once

#include <QString>
#include <QJsonObject>
#include <QJsonArray>

namespace PharmaTrack
{

class Batch;

class JsonManager
{
public:

    //--------------------------------------------------
    // Generic
    //--------------------------------------------------

    static bool saveJson(const QString& file,
                         const QJsonObject& object);

    static bool loadJson(const QString& file,
                         QJsonObject& object);

    //--------------------------------------------------
    // Batch
    //--------------------------------------------------

    // static bool saveBatch(const Batch& batch);

    // static bool loadBatch(const QString& batchId,
    //                       QJsonObject& batchObject);

    //--------------------------------------------------
    // Registry
    //--------------------------------------------------

    static bool saveRegistry(const QJsonArray& registry);

    static bool loadRegistry(QJsonArray& registry);

};

}