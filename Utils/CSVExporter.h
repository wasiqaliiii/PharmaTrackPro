#ifndef PHARMATRACK_CSVEXPORTER_H
#define PHARMATRACK_CSVEXPORTER_H

#include <QString>
#include <QList>
#include "../Models/Batch.h"
#include "../Models/SerialNumber.h"
namespace PharmaTrack
{



class CSVExporter
{
public:

    static bool exportFile(
    const QString &fileName,
    const Batch &batch,
    const QList<SerialNumber> &serials,
    QString &errorMessage);
};

}

#endif // PHARMATRACK_CSVEXPORTER_H