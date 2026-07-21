#ifndef PHARMATRACK_TXTEXPORTER_H
#define PHARMATRACK_TXTEXPORTER_H

#include <QString>
#include <QList>

namespace PharmaTrack
{

class SerialNumber;

class TXTExporter
{
public:

    static bool exportFile(
            const QString &fileName,
            const QList<SerialNumber> &serials,
            QString &errorMessage);
};

}

#endif