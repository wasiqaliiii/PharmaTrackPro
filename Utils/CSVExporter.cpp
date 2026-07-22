#include "CSVExporter.h"

#include "../Models/Batch.h"
#include "../Models/SerialNumber.h"

#include <QFile>
#include <QTextStream>

namespace PharmaTrack
{

bool CSVExporter::exportFile(
        const QString &fileName,
        const Batch &batch,
        const QList<SerialNumber> &serials,
        QString &errorMessage)
{
    QFile file(fileName);

    if(!file.open(QIODevice::WriteOnly |
                  QIODevice::Text))
    {
        errorMessage = file.errorString();
        return false;
    }

    QTextStream stream(&file);

    // Batch Information
    stream << "Batch Number," << batch.batchNumber() << "\n";
    stream << "Product Name," << batch.productName() << "\n";
    stream << "Quantity," << batch.quantity() << "\n";
    stream << "Serial Length," << batch.serialLength() << "\n";
    stream << "Prefix," << batch.prefix() << "\n";
stream << "Generated At,"
       << batch.generatedAt().toString("yyyy-MM-dd hh:mm:ss")
       << "\n\n";

    stream << "\n";

    // Serial Numbers
    stream << "Serial Number\n";

    for(const SerialNumber &serial : serials)
    {
        stream << serial.serial() << "\n";
    }

    file.close();

    return true;
}

}