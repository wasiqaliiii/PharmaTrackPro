#include "JsonManager.h"

#include "../Models/Batch.h"
#include "PathManager.h"

#include <QFile>
#include <QJsonDocument>

namespace PharmaTrack
{

//--------------------------------------------------
// Generic Save
//--------------------------------------------------

bool JsonManager::saveJson(const QString& file,
                           const QJsonObject& object)
{
    QFile jsonFile(file);

    if(!jsonFile.open(QIODevice::WriteOnly))
        return false;

    QJsonDocument document(object);

    jsonFile.write(document.toJson());

    jsonFile.close();

    return true;
}

//--------------------------------------------------
// Generic Load
//--------------------------------------------------

bool JsonManager::loadJson(const QString& file,
                           QJsonObject& object)
{
    QFile jsonFile(file);

    if(!jsonFile.open(QIODevice::ReadOnly))
        return false;

    QByteArray data =
            jsonFile.readAll();

    jsonFile.close();

    QJsonDocument document =
            QJsonDocument::fromJson(data);

    if(document.isNull())
        return false;

    object = document.object();

    return true;
}

//--------------------------------------------------
// Save Batch
//--------------------------------------------------

// bool JsonManager::saveBatch(const Batch& batch)
// {
//     QJsonObject object;

//     object["batchId"] = batch.batchId();

//     object["product"] = batch.productName();

//     object["quantity"] = batch.totalCodes();

//     object["created"] = batch.createdDate().toString(Qt::ISODate);

//     object["status"] = batch.status();

//     return saveJson(
//                 PathManager::batchFile(batch.batchId()),
//                 object);
// }

//--------------------------------------------------
// Load Batch
//--------------------------------------------------

// bool JsonManager::loadBatch(
//         const QString& batchId,
//         QJsonObject& batchObject)
// {
//     return loadJson(
//                 PathManager::batchFile(batchId),
//                 batchObject);
// }

//--------------------------------------------------
// Save Registry
//--------------------------------------------------

bool JsonManager::saveRegistry(
        const QJsonArray& registry)
{
    QFile file(PathManager::registryFile());

    if(!file.open(QIODevice::WriteOnly))
        return false;

    QJsonDocument document(registry);

    file.write(document.toJson());

    file.close();

    return true;
}

//--------------------------------------------------
// Load Registry
//--------------------------------------------------

bool JsonManager::loadRegistry(
        QJsonArray& registry)
{
    QFile file(PathManager::registryFile());

    if(!file.open(QIODevice::ReadOnly))
        return false;

    QByteArray data =
            file.readAll();

    file.close();

    QJsonDocument document =
            QJsonDocument::fromJson(data);

    if(!document.isArray())
        return false;

    registry = document.array();

    return true;
}

}