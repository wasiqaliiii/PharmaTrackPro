#ifndef PHARMATRACK_GENERATORSERVICE_H
#define PHARMATRACK_GENERATORSERVICE_H

#include <QObject>
#include <QList>
#include <QSet>
#include "../Models/GenerationResult.h"

#include "../Models/Batch.h"
#include "../Models/SerialNumber.h"

namespace PharmaTrack
{

class GeneratorService : public QObject
{
    Q_OBJECT

public:
    explicit GeneratorService(QObject *parent = nullptr);

    bool generate(
    const Batch &batch,
    GenerationResult &result,
    QString &errorMessage);
    bool validateBatch(const Batch &batch,
                       QString &errorMessage) const;

signals:

    void generationStarted();

    void progressChanged(int percentage);

    void generationFinished();

private:

    QString generateUniqueSerial(
            const QString &prefix,
            int totalLength,
            QSet<QString> &generatedSet);

};

}

#endif // PHARMATRACK_GENERATORSERVICE_H