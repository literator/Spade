#include "frequentitemscalculator.h"
#include "idlistitem.h"
#include "IdListSequenceSet.h"

FrequentItemsCalculator::FrequentItemsCalculator(unsigned int minSupport) : _minSupport(minSupport) {
}

IdListItemSets FrequentItemsCalculator::oneFrequentItems(IdListItemSets &allItems) {
    vector<SequenceID> checkedSequencesIDs;
    IdListItemSets oneFrequentItems;

    for (IdListItemSetPtr itemPtr : allItems) {
        SequenceEventPairs pairs = itemPtr->pairs();
        for (SequenceEventPair &pair : pairs) {
            bool sequenceIDFound = find_if(begin(checkedSequencesIDs),
                    end(checkedSequencesIDs),
                    [&](const SequenceID sequenceID) {return sequenceID == pair.first;})
                    != end(checkedSequencesIDs);
            if (!sequenceIDFound) {
                checkedSequencesIDs.push_back(pair.first);
                itemPtr->support++;
            }
        }
        if (itemPtr->support >= _minSupport) {
            auto itemPtrCopy = itemPtr;
            oneFrequentItems.push_back(itemPtrCopy);
        }
        checkedSequencesIDs.clear();
    }

    return oneFrequentItems;
}

vector<ExtendedIdListItemSet> FrequentItemsCalculator::twoFrequentItems(IdListSequenceSets idListSequenceSets) {
    vector<ExtendedIdListItemSet> extendedItemSets;

    for (const IdListSequenceSetPtr &sequenceSetPtr : idListSequenceSets) {
        vector<ExtendedIdListItemSet> innerItemSets;
        ItemSetEventPairs const &pairs = sequenceSetPtr->pairs();
        SequenceID const &sequenceID = sequenceSetPtr->sequenceID();

        for (ItemSetEventPair pair : pairs) {
            ItemSet itemSet = pair.first;
            EventID eventID = pair.second;
            for (ItemSetEventPair innerPair : pairs) {
                ItemSet innerItemSet = innerPair.first;
                EventID innerEventID = innerPair.second;
                if (itemSet == innerItemSet) continue;

                ExtendedIdListItemSet idListItemSet(sequenceID, itemSet, eventID, innerItemSet, innerEventID);
                bool itemExists = itemExistsInInnerSets(idListItemSet, innerItemSets);
                bool itemSetEmpty = idListItemSet.itemSets().empty();
                if (!itemExists && !itemSetEmpty) {
                    innerItemSets.push_back(idListItemSet);
                }
            }
        }

        for (auto innerIdListItemSet : innerItemSets) {
            auto idListItemSetIt = find(begin(extendedItemSets), end(extendedItemSets), innerIdListItemSet);
            bool itemSetExists = idListItemSetIt != end(extendedItemSets);
            if (!itemSetExists) {
                idListItemSetIt = extendedItemSets.insert(end(extendedItemSets), innerIdListItemSet);
            } else {
                EventID eventID = innerIdListItemSet.sequenceEventPairs.back().second;
                idListItemSetIt->sequenceEventPairs.push_back(make_pair(sequenceID, eventID));
            }
            idListItemSetIt->support++;
        }
    }

    auto removeIfIt = remove_if(begin(extendedItemSets), end(extendedItemSets), [&](const ExtendedIdListItemSet &idListItem) {
        return idListItem.support < _minSupport;
    });
    extendedItemSets.erase(removeIfIt, end(extendedItemSets));

    return extendedItemSets;
}

bool FrequentItemsCalculator::itemExistsInInnerSets(ExtendedIdListItemSet idListItemSet, vector<ExtendedIdListItemSet> innerSets) {
    auto innerSetIt = find(begin(innerSets), end(innerSets), idListItemSet);
    bool elementExists = innerSetIt != end(innerSets);
    return elementExists;
}

void FrequentItemsCalculator::sort(vector<ExtendedIdListItemSet> &list) {
    auto maxItemSetIt = ::max_element(begin(list), end(list), [](const ExtendedIdListItemSet &a, const ExtendedIdListItemSet &b) {
        return a.itemSets().size() < b.itemSets().size();
    });
    int maxSize = maxItemSetIt->itemSets().size();
    for (int i = maxSize; i >= 0; --i) {
        ::sort(begin(list), end(list), [&i](const ExtendedIdListItemSet &a, const ExtendedIdListItemSet &b) {
            if (a.itemSets().size() > i && b.itemSets().size() > i) {
                return a.itemSets()[i] < b.itemSets()[i];
            }
            return false;
        });
    }
}

void FrequentItemsCalculator::enumerateFrequentSequences(vector<ExtendedIdListItemSet> sequences) {

}
