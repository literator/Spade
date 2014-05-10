#ifndef ONEFREQUENTITEMSCALCULATOR_H
#define ONEFREQUENTITEMSCALCULATOR_H

#include "types.h"

using namespace std;

class OneFrequentItemsCalculator
{
private:
    unsigned int _minSupport;
public:
    OneFrequentItemsCalculator(unsigned int minSupport);
    IdListItems oneFrequentItems(IdListItems &allItems);
};

#endif // ONEFREQUENTITEMSCALCULATOR_H
