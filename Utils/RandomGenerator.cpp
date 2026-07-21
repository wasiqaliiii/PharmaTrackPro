 #include "RandomGenerator.h"

#include <QRandomGenerator>

namespace PharmaTrack
{

QString RandomGenerator::characterSet()
{
    static const QString characters =
            QStringLiteral("ABCDEFGHJKMNPQRSTUVWXYZ23456789");

    return characters;
}

QString RandomGenerator::generate(int length)
{
    if (length <= 0)
        return QString();

    const QString chars = characterSet();

    QString result;
    result.reserve(length);

    for (int i = 0; i < length; ++i)
    {
        int index = QRandomGenerator::global()->bounded(chars.length());
        result.append(chars.at(index));
    }

    return result;
}

}