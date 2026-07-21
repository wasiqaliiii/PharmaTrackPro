#ifndef PHARMATRACK_GENERATIONRESULT_H
#define PHARMATRACK_GENERATIONRESULT_H

#include <QList>

#include "SerialNumber.h"

namespace PharmaTrack
{


class GenerationResult
{
public:
    GenerationResult();

    QList<SerialNumber> serials;

    int generatedCount;

    double generationSeconds;

    double generationSpeed;
};

}

#endif // PHARMATRACK_GENERATIONRESULT_H