#pragma once

#include "../Types.h"
#include "../Model/ExtendedIdListItemSet.h"

using namespace std;

class FrequentItemsCalculator {
private:
    unsigned int _minSupport;

    ExtendedIdListItemSetVector temporalJoin(ExtendedIdListItemSet &first, ExtendedIdListItemSet &second);
    bool prune(ExtendedIdListItemSet idListItemSet, ExtendedIdListItemSetVector sequences);
    ExtendedIdListItemSetVector subsets(ExtendedIdListItemSet idListItemSet);
public:
    FrequentItemsCalculator(unsigned int minSupport);
    IdListItemSets oneFrequentItems(IdListItemSets &allItems);
    ExtendedIdListItemSetVector twoFrequentItems(IdListSequenceSets idListSequenceSets);
    void enumerateFrequentSequences(ExtendedIdListItemSetVector sequences);
    void sort(ExtendedIdListItemSetVector &list);
};
