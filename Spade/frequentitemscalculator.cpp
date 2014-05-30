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
                auto innerSetIt = find(begin(innerItemSets), end(innerItemSets), idListItemSet);
                bool itemExists = innerSetIt != end(innerItemSets);
                bool itemSetEmpty = idListItemSet.atomSets().empty();
                if (!itemExists && !itemSetEmpty) {
                    innerItemSets.push_back(idListItemSet);
                }
                if (itemExists) {
                    SequenceEventPairs sequenceEventPairs = idListItemSet.sequenceEventPairs;
                    for_each(begin(sequenceEventPairs), end(sequenceEventPairs), [&innerSetIt](SequenceEventPair sequenceEventPair) {
                        SequenceEventPairs currentPairs = innerSetIt->sequenceEventPairs;
                        auto pairIt = find(begin(currentPairs), end(currentPairs), sequenceEventPair);
                        if (pairIt == end(currentPairs)) {
                            innerSetIt->sequenceEventPairs.push_back(sequenceEventPair);
                        }
                    });
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

    ExtendedIdListItemSetList joinedItemSetList;
    for (int i = 0, j = 0; i < firstSize, j < secondSize; ++i, ++j) {
        AtomSet const &firstAtomSet = first.atomSets()[i];
        AtomSet const &secondAtomSet = second.atomSets()[j];
        if (firstAtomSet != secondAtomSet) {
            bool isLastAtomSetFromFirst = i == firstSize - 1;
            bool isLastAtomSetFromSecond = j == secondSize - 1;
            if (isLastAtomSetFromFirst && isLastAtomSetFromSecond) {
                if (firstAtomSet.atoms().front() != secondAtomSet.atoms().front()) {
                    // s & s
                    ExtendedIdListItemSet firstTrailingItemSet(first);
                    firstTrailingItemSet.atomSets().push_back(secondAtomSet);

                    ExtendedIdListItemSet secondTrailingItemSet(second);
                    secondTrailingItemSet.atomSets().push_back(firstAtomSet);

                    ExtendedIdListItemSet eventTrailingItemSet(first);
                    eventTrailingItemSet.atomSets().back().addAtom(secondAtomSet.atoms().back());

                    for (SequenceEventPair firstPair : first.sequenceEventPairs) {
                        for (SequenceEventPair secondPair : second.sequenceEventPairs) {
                            if (secondPair.first == firstPair.first) {

                                if (firstPair.second < secondPair.second) {
                                    firstTrailingItemSet.addPairIfNotExists(secondPair);
                                } else if (firstPair.second == secondPair.second) {
                                    eventTrailingItemSet.addPairIfNotExists(secondPair);
                                } else if (firstPair.second > secondPair.second) {
                                    secondTrailingItemSet.addPairIfNotExists(firstPair);
                                }

                            }
                        }
                    }

                } else {
                    // e & e
                    ExtendedIdListItemSet newIdListItemSet(first);
                    newIdListItemSet.atomSets().back().addAtom(secondAtomSet.atoms().front());
                    for (auto pair : second.sequenceEventPairs) {
                        SequenceEventPairs eventPairs = newIdListItemSet.sequenceEventPairs;
                        bool pairExists = find(begin(eventPairs), end(eventPairs), pair) != end(eventPairs);
                        if (!pairExists) {
                            newIdListItemSet.sequenceEventPairs.push_back(pair);
                        }
                    }
                    newIdListItemSet.recalculateSupport();
                    joinedItemSetList.push_back(newIdListItemSet);
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

    return joinedItemSetList;
}

