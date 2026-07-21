#ifndef PHARMATRACK_RANDOMGENERATOR_H
#define PHARMATRACK_RANDOMGENERATOR_H

#include <QString>

namespace PharmaTrack
{

class RandomGenerator
{
public:
    RandomGenerator() = delete;

    // Generates a random alphanumeric string
    static QString generate(int length);

    // Returns the approved character set
    static QString characterSet();

};

}

#endif // PHARMATRACK_RANDOMGENERATOR_H