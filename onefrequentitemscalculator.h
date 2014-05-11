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
    IdListItemSets oneFrequentItems(IdListItemSets &allItems);
};

#endif // ONEFREQUENTITEMSCALCULATOR_H
