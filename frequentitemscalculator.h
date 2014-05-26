#pragma once

#include "types.h"
#include "itemset.h"
#include "ExtendedIdListItemSet.h"
#include <vector>

using namespace std;

class FrequentItemsCalculator {
private:
    unsigned int _minSupport;

    bool itemExistsInInnerSets(ExtendedIdListItemSet idListItemSet, vector<ExtendedIdListItemSet> innerSets);
public:
    FrequentItemsCalculator(unsigned int minSupport);
    IdListItemSets oneFrequentItems(IdListItemSets &allItems);
    vector<ExtendedIdListItemSet> twoFrequentItems(IdListSequenceSets idListSequenceSets);
    void enumerateFrequentSequences(vector<ExtendedIdListItemSet> sequences);
    void sort(vector<ExtendedIdListItemSet> &list);
};
