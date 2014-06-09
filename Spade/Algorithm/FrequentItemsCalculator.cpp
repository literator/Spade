#include "FrequentItemsCalculator.h"
#include "../Model/IdListItemSet.h"
#include "../Model/IdListSequenceSet.h"

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

ExtendedIdListItemSetVector FrequentItemsCalculator::twoFrequentItems(IdListSequenceSets idListSequenceSets) {
    ExtendedIdListItemSetVector extendedItemSets;

    for (const IdListSequenceSetPtr &sequenceSetPtr : idListSequenceSets) {
        ExtendedIdListItemSetVector innerItemSets;
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

void FrequentItemsCalculator::sort(ExtendedIdListItemSetVector &list) {
    auto maxItemSetIt = ::max_element(begin(list), end(list), [](const ExtendedIdListItemSet &a, const ExtendedIdListItemSet &b) {
        return a.atomSets().size() < b.atomSets().size();
    });
    int maxSize = maxItemSetIt->atomSets().size();
    for (int i = maxSize; i >= 0; --i) {
        ::sort(begin(list), end(list), [&i](const ExtendedIdListItemSet &a, const ExtendedIdListItemSet &b) {
            unsigned long aSize = a.atomSets().size();
            unsigned long bSize = b.atomSets().size();
            if (aSize > i && bSize > i) {
                return a.atomSets()[i] < b.atomSets()[i];
            }
            return false;
        });
    }
    ::sort(begin(list), end(list), [&](const ExtendedIdListItemSet &a, const ExtendedIdListItemSet &b) {
        unsigned long aSize = a.atomSets().size();
        unsigned long bSize = b.atomSets().size();
        return aSize < bSize;
    });
}

void FrequentItemsCalculator::enumerateFrequentSequences(ExtendedIdListItemSetVector sequences) {
    ExtendedIdListItemSetSet newSequences;
    for (auto i = begin(sequences); i != end(sequences); ++i) {
        ExtendedIdListItemSet idListItemSet = *i;
        for (auto j = i + 1; j != end(sequences); ++j) {
            ExtendedIdListItemSet innerIdListItemSet = *j;
            ExtendedIdListItemSetVector joinedIdListItemSetList = temporalJoin(idListItemSet, innerIdListItemSet);
            bool noJoinPerformed = joinedIdListItemSetList.empty();
            if (noJoinPerformed) {
                continue;
            }
            for (ExtendedIdListItemSet joinedIdListItemSet : joinedIdListItemSetList) {
                if (joinedIdListItemSet.support >= this->_minSupport) {
                    auto itemSetIt = newSequences.find(joinedIdListItemSet);
                    if (itemSetIt != end(newSequences) &&
                            itemSetIt->sequenceEventPairs.size() < joinedIdListItemSet.sequenceEventPairs.size()) {
                        newSequences.erase(itemSetIt);
                    }
                    newSequences.insert(joinedIdListItemSet);
                }
            }
        }
    }
    if (!newSequences.empty()) {
        cout << newSequences.begin()->numberOfAtoms() << " frequent items (" << newSequences.size() << "):" << endl;
        if (newSequences.begin()->numberOfAtoms() >= this->_minSupport) {
            for (auto item : newSequences) {
                cout << item << endl;
            }
        }
        // BFS
        ExtendedIdListItemSetVector newSequencesVector = ExtendedIdListItemSetVector(begin(newSequences), end(newSequences));
        enumerateFrequentSequences(newSequencesVector);
    }
}

ExtendedIdListItemSetVector FrequentItemsCalculator::temporalJoin(ExtendedIdListItemSet &first, ExtendedIdListItemSet &second) {
    if (first.numberOfAtoms() != second.numberOfAtoms()) {
        return ExtendedIdListItemSetVector();
    }

    ExtendedIdListItemSetVector joinedItemSetList;

    if (first.hasEqualElementsExcludingLast(second)) {
        ExtendedIdListItemSet firstSecond(first.atomSets());
        firstSecond.addAtomToTheLatestAtomSet(second.lastAtomFromLastAtomSet());

        ExtendedIdListItemSet firstToSecond(first.atomSets());
        firstToSecond.addAtomSet(AtomSet(second.lastAtomFromLastAtomSet()));

        ExtendedIdListItemSet secondToFirst(second.atomSets());
        secondToFirst.addAtomSet(AtomSet(first.lastAtomFromLastAtomSet()));

        SequenceEventMap firstSequenceEventMap = first.sequenceEventMap();
        SequenceEventMap secondSequenceEventMap = second.sequenceEventMap();
        for (auto &sequenceEventsPair : firstSequenceEventMap) {
            SequenceID sequenceID = sequenceEventsPair.first;
            if (secondSequenceEventMap.find(sequenceID) != secondSequenceEventMap.end()) {
                vector<EventID> &firstEvents = sequenceEventsPair.second;
                vector<EventID> &secondEvents = secondSequenceEventMap[sequenceID];

                for (auto firstEvent : firstEvents) {
                    for (auto secondEvent : secondEvents) {

                        if (firstEvent < secondEvent) {
                            firstToSecond.addPairIfNotExists(make_pair(sequenceID, secondEvent));
                        } else if (firstEvent > secondEvent) {
                            secondToFirst.addPairIfNotExists(make_pair(sequenceID, firstEvent));
                        } else {
                            firstSecond.addPairIfNotExists(make_pair(sequenceID, firstEvent));
                        }

                    }
                }
            }
        }

        if (!firstSecond.sequenceEventPairs.empty()) {
            firstSecond.recalculateSupport();
            joinedItemSetList.push_back(firstSecond);
        }
        if (!firstToSecond.sequenceEventPairs.empty()) {
            firstToSecond.recalculateSupport();
            joinedItemSetList.push_back(firstToSecond);
        }
        if (!secondToFirst.sequenceEventPairs.empty()) {
            secondToFirst.recalculateSupport();
            joinedItemSetList.push_back(secondToFirst);
        }

    }

    return joinedItemSetList;
}

