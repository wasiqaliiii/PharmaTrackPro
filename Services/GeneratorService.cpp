#include "GeneratorService.h"

#include "../Utils/RandomGenerator.h"
#include "../Models/GenerationResult.h"

#include <QDateTime>
#include <QElapsedTimer>

namespace PharmaTrack
{

GeneratorService::GeneratorService(QObject *parent)
    : QObject(parent)
{
}

////////////////////////////////////////////////////////
/// Validation
////////////////////////////////////////////////////////

bool GeneratorService::validateBatch(
        const Batch &batch,
        QString &errorMessage) const
{
    if(batch.batchNumber().trimmed().isEmpty())
    {
        errorMessage = "Batch number is required.";
        return false;
    }

    if(batch.productName().trimmed().isEmpty())
    {
        errorMessage = "Product name is required.";
        return false;
    }

    if(batch.quantity() <= 0)
    {
        errorMessage = "Quantity must be greater than zero.";
        return false;
    }

    if(batch.serialLength() != 15 &&
       batch.serialLength() != 21)
    {
        errorMessage =
                "Serial length must be either 15 or 21.";

        return false;
    }

    if(batch.prefix().length() >=
            batch.serialLength())
    {
        errorMessage =
                "Prefix is longer than the selected serial length.";

        return false;
    }

    return true;
}

////////////////////////////////////////////////////////
/// Generate One Unique Serial
////////////////////////////////////////////////////////

QString GeneratorService::generateUniqueSerial(
        const QString &prefix,
        int totalLength,
        QSet<QString> &generatedSet)
{
    QString serial;

    const int randomLength =
            totalLength - prefix.length();

    do
    {
        serial =
                prefix +
                RandomGenerator::generate(randomLength);

    }
    while(generatedSet.contains(serial));

    generatedSet.insert(serial);

    return serial;
}

////////////////////////////////////////////////////////
/// Generate Batch
////////////////////////////////////////////////////////

bool GeneratorService::generate(
        const Batch &batch,
        GenerationResult &result,
        QString &errorMessage)
{
    result.serials.clear();
    result.generatedCount = 0;
    result.generationSeconds = 0.0;
    result.generationSpeed = 0.0;

    if(!validateBatch(batch, errorMessage))
        return false;

    result.serials.reserve(batch.quantity());

    emit generationStarted();

    QElapsedTimer timer;
    timer.start();

    QSet<QString> generatedSet;

    const QString prefix =
            batch.prefix().trimmed().toUpper();

    const QDateTime generatedTime =
            QDateTime::currentDateTime();

    int lastProgress = -1;

    for(int i = 0;
        i < batch.quantity();
        ++i)
    {
        SerialNumber record;

        QString serial =
                generateUniqueSerial(
                    prefix,
                    batch.serialLength(),
                    generatedSet);

        record.setSerial(serial);

        record.setBatchNumber(
                    batch.batchNumber());

        record.setProductName(
                    batch.productName());

        record.setPrefix(prefix);

        record.setSerialLength(
                    batch.serialLength());

        record.setGeneratedAt(
                    generatedTime);

        result.serials.append(record);

        int progress =
                ((i + 1) * 100)
                / batch.quantity();

        if(progress != lastProgress)
        {
            lastProgress = progress;
            emit progressChanged(progress);
        }
    }

    result.generatedCount =
            result.serials.size();

    result.generationSeconds =
            timer.elapsed() / 1000.0;

    if(result.generationSeconds > 0.0)
    {
        result.generationSpeed =
                result.generatedCount /
                result.generationSeconds;
    }
    else
    {
        result.generationSpeed = 0.0;
    }

    emit generationFinished();

    return true;
}

}