#include "frequentitemscalculator.h"
#include <vector>
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

list<ExtendedIdListItemSet> FrequentItemsCalculator::twoFrequentItems(IdListSequenceSets idListSequenceSets) {
    list<ExtendedIdListItemSet> extendedItemSets;

    for (const IdListSequenceSetPtr &sequenceSetPtr : idListSequenceSets) {
        list<ExtendedIdListItemSet> innerItemSets;
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

    extendedItemSets.remove_if([&](const ExtendedIdListItemSet &idListItem) {
        return idListItem.support < _minSupport;
    });

    return extendedItemSets;
}

bool FrequentItemsCalculator::itemExistsInInnerSets(ExtendedIdListItemSet idListItemSet, list<ExtendedIdListItemSet> innerSets) {
    auto innerSetIt = find(begin(innerSets), end(innerSets), idListItemSet);
    bool elementExists = innerSetIt != end(innerSets);
    return elementExists;
}

void ExtendedIdListItemSet::createPreviousNextItemSet(ItemSet itemSet, ItemSet innerItemSet) {
    ItemList previousItemList, nextItemList;
    itemSet.addItemsToItemList(previousItemList);
    innerItemSet.addItemsToItemList(nextItemList);
    _itemSets = {ItemSet(previousItemList), ItemSet(nextItemList)};
}

void ExtendedIdListItemSet::createExtendedIdListItemSet(ItemSet itemSet, ItemSet innerItemSet) {
    ItemList itemList;
    itemSet.addItemsToItemList(itemList);
    innerItemSet.addItemsToItemList(itemList);
    _itemSets = {ItemSet(itemList)};
}

ExtendedIdListItemSet::ExtendedIdListItemSet(SequenceID sequenceId, ItemSet itemSet, EventID eventID, ItemSet innerItemSet, EventID innerEventID)
        : support(0), sequenceEventPairs(SequenceEventPairs()) {
    EventID eventToSave;
    if (eventID == innerEventID && itemSet < innerItemSet) {
        createExtendedIdListItemSet(itemSet, innerItemSet);
        eventToSave = eventID;
    } else if (eventID < innerEventID) {
        createPreviousNextItemSet(itemSet, innerItemSet);
        eventToSave = innerEventID;
    } else if (eventID > innerEventID) {
        createPreviousNextItemSet(innerItemSet, itemSet);
        eventToSave = eventID;
    }
    sequenceEventPairs.push_back(make_pair(sequenceId, eventToSave));
}
