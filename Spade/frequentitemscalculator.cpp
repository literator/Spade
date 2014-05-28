#include "FrequentItemsCalculator.h"
#include "Model/IdListItemSet.h"
#include "Model/IdListSequenceSet.h"

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

ExtendedIdListItemSetList FrequentItemsCalculator::twoFrequentItems(IdListSequenceSets idListSequenceSets) {
    ExtendedIdListItemSetList extendedItemSets;

    for (const IdListSequenceSetPtr &sequenceSetPtr : idListSequenceSets) {
        ExtendedIdListItemSetList innerItemSets;
        ItemSetEventPairs const &pairs = sequenceSetPtr->pairs();
        SequenceID const &sequenceID = sequenceSetPtr->sequenceID();

        for (ItemSetEventPair pair : pairs) {
            AtomSet itemSet = pair.first;
            EventID eventID = pair.second;
            for (ItemSetEventPair innerPair : pairs) {
                AtomSet innerItemSet = innerPair.first;
                EventID innerEventID = innerPair.second;
                if (itemSet == innerItemSet) continue;

                ExtendedIdListItemSet idListItemSet(sequenceID, itemSet, eventID, innerItemSet, innerEventID);
                bool itemExists = itemExistsInInnerSets(idListItemSet, innerItemSets);
                bool itemSetEmpty = idListItemSet.atomSets().empty();
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

bool FrequentItemsCalculator::itemExistsInInnerSets(ExtendedIdListItemSet idListItemSet, ExtendedIdListItemSetList innerSets) {
    auto innerSetIt = find(begin(innerSets), end(innerSets), idListItemSet);
    bool elementExists = innerSetIt != end(innerSets);
    return elementExists;
}

void FrequentItemsCalculator::sort(ExtendedIdListItemSetList &list) {
    auto maxItemSetIt = ::max_element(begin(list), end(list), [](const ExtendedIdListItemSet &a, const ExtendedIdListItemSet &b) {
        return a.atomSets().size() < b.atomSets().size();
    });
    int maxSize = maxItemSetIt->atomSets().size();
    for (int i = maxSize; i >= 0; --i) {
        ::sort(begin(list), end(list), [&i](const ExtendedIdListItemSet &a, const ExtendedIdListItemSet &b) {
            if (a.atomSets().size() > i && b.atomSets().size() > i) {
                return a.atomSets()[i] < b.atomSets()[i];
            }
            return false;
        });
    }
}

void FrequentItemsCalculator::enumerateFrequentSequences(ExtendedIdListItemSetList sequences) {
    for (int i = 0; i < sequences.size(); ++i) {
        ExtendedIdListItemSet idListItemSet = sequences[i];
        ExtendedIdListItemSetList newSequences;
        for (int j = i + 1; j < sequences.size(); ++j) {
            ExtendedIdListItemSet innerIdListItemSet = sequences[j];
            ExtendedIdListItemSetList joinedIdListItemSetList = temporalJoin(idListItemSet, innerIdListItemSet);
            bool noJoinPerformed = joinedIdListItemSetList.empty();
            if (noJoinPerformed) {
                continue;
            }
        }
    }
}

ExtendedIdListItemSetList FrequentItemsCalculator::temporalJoin(ExtendedIdListItemSet &first, ExtendedIdListItemSet &second) {
    if (first.numberOfAtoms() != second.numberOfAtoms()) {
        return ExtendedIdListItemSetList();
    }
    unsigned long firstSize = first.atomSets().size();
    unsigned long secondSize = second.atomSets().size();
    bool numberOfItemsSetsInRange = ::abs(firstSize - secondSize) <= 1;
    if (!numberOfItemsSetsInRange) {
        return ExtendedIdListItemSetList();
    }
    for (int i = 0, j = 0; i < firstSize, j < secondSize; ++i, ++j) {
        AtomSet const &firstAtomSet = first.atomSets()[i];
        AtomSet const &secondAtomSet = second.atomSets()[j];
        if (firstAtomSet != secondAtomSet) {
            bool isLastAtomSetFromFirst = i == firstSize - 1;
            bool isLastAtomSetFromSecond = j == secondSize - 1;
            if (isLastAtomSetFromFirst && isLastAtomSetFromSecond) {
                if (firstAtomSet.atoms().front() != secondAtomSet.atoms().front()) {
                    // s & s
                } else {
                    // e & e
                }
            } else {
                if (first.hasEqualElementsExcludingLast(second)) {
                    if (isLastAtomSetFromFirst) {
                        // e + s
                    } else if (isLastAtomSetFromSecond) {
                        // s + e
                    }
                }
            }
        }
    }

    return ExtendedIdListItemSetList();
}

