#include "onefrequentitemscalculator.h"
#include <vector>
#include <algorithm>
#include "idlistitem.h"

OneFrequentItemsCalculator::OneFrequentItemsCalculator(unsigned int minSupport) : _minSupport(minSupport) {}

IdListItemSets OneFrequentItemsCalculator::oneFrequentItems(IdListItemSets &allItems)
{
    vector<SequenceID> checkedSequencesIDs;
    IdListItemSets oneFrequentItems;

    for(IdListItemSetPtr itemPtr : allItems)
    {
        IdListPairs pairs = itemPtr->pairs();
        for(IdListPair &pair : pairs)
        {
            bool sequenceIDFound = find_if(begin(checkedSequencesIDs),
                                           end(checkedSequencesIDs),
                                           [&](const SequenceID sequenceID) { return sequenceID == pair.first; })
                    != end(checkedSequencesIDs);
            if(!sequenceIDFound)
            {
                itemPtr->support++;
            }
        }
        if(itemPtr->support >= _minSupport) {
            auto itemPtrCopy = itemPtr;
            oneFrequentItems.push_back(itemPtrCopy);
        }
        checkedSequencesIDs.clear();
    }

    return oneFrequentItems;
}


