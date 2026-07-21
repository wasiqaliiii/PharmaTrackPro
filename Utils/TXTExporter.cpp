#include "TXTExporter.h"

#include "../Models/SerialNumber.h"

#include <QFile>
#include <QTextStream>

namespace PharmaTrack
{

bool TXTExporter::exportFile(
        const QString &fileName,
        const QList<SerialNumber> &serials,
        QString &errorMessage)
{
    QFile file(fileName);

    if(!file.open(QIODevice::WriteOnly |
                  QIODevice::Text))
    {
        errorMessage =
                file.errorString();

        return false;
    }

    QTextStream stream(&file);

    for(const SerialNumber &serial : serials)
    {
        stream << serial.serial() << "\n";
    }

    file.close();

    return true;
}

}