#pragma once

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
