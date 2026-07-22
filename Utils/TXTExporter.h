#ifndef PHARMATRACK_TXTEXPORTER_H
#define PHARMATRACK_TXTEXPORTER_H

#include <QString>
#include <QList>
#include "../Models/Batch.h"
#include "../Models/SerialNumber.h"
namespace PharmaTrack
{



class TXTExporter
{
public:

    static bool exportFile(
    const QString &fileName,
    const Batch &batch,
    const QList<SerialNumber> &serials,
    QString &errorMessage);
};

}

#endif