#pragma once

#include "../Types.h"
#include "../Model/ExtendedIdListItemSet.h"

using namespace std;

class FrequentItemsCalculator {
private:
    unsigned int _minSupport;

    ExtendedIdListItemSetList temporalJoin(ExtendedIdListItemSet &first, ExtendedIdListItemSet &second);
public:
    FrequentItemsCalculator(unsigned int minSupport);
    IdListItemSets oneFrequentItems(IdListItemSets &allItems);
    ExtendedIdListItemSetList twoFrequentItems(IdListSequenceSets idListSequenceSets);
    void enumerateFrequentSequences(ExtendedIdListItemSetList sequences);
    void sort(ExtendedIdListItemSetList &list);
};
