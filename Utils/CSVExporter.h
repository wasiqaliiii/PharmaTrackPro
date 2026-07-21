#ifndef PHARMATRACK_CSVEXPORTER_H
#define PHARMATRACK_CSVEXPORTER_H

#include <QString>
#include <QList>

namespace PharmaTrack
{

class SerialNumber;

class CSVExporter
{
public:

    static bool exportFile(
            const QString &fileName,
            const QList<SerialNumber> &serials,
            QString &errorMessage);
};

}

#endif // PHARMATRACK_CSVEXPORTER_H