#include "ExtendedIdListItemSet.h"

ExtendedIdListItemSet::ExtendedIdListItemSet(unsigned int support)
        : support(support), _atomSets(AtomSetList()), sequenceEventPairs(SequenceEventPairs()) {
}

ExtendedIdListItemSet::ExtendedIdListItemSet(AtomSetList const &atomSets)
        : _atomSets(atomSets), support(0), sequenceEventPairs(SequenceEventPairs()) {
}

ExtendedIdListItemSet::ExtendedIdListItemSet(const ExtendedIdListItemSet *itemSet) {
    _atomSets = itemSet->_atomSets;
    support = itemSet->support;
    sequenceEventPairs = itemSet->sequenceEventPairs;
}

ExtendedIdListItemSet::ExtendedIdListItemSet(const ExtendedIdListItemSet &itemSet) {
    _atomSets = itemSet._atomSets;
    support = itemSet.support;
    sequenceEventPairs = itemSet.sequenceEventPairs;
}

void ExtendedIdListItemSet::createPreviousNextItemSet(AtomSet itemSet, AtomSet innerItemSet) {
    AtomList previousItemList, nextItemList;
    itemSet.addAtomsToAtomList(previousItemList);
    innerItemSet.addAtomsToAtomList(nextItemList);
    _atomSets = {AtomSet(previousItemList), AtomSet(nextItemList)};
}

void ExtendedIdListItemSet::createExtendedIdListItemSet(AtomSet itemSet, AtomSet innerItemSet) {
    AtomList itemList;
    itemSet.addAtomsToAtomList(itemList);
    innerItemSet.addAtomsToAtomList(itemList);
    _atomSets = {AtomSet(itemList)};
}

ExtendedIdListItemSet::ExtendedIdListItemSet(SequenceID sequenceId, AtomSet itemSet, EventID eventID, AtomSet innerItemSet, EventID innerEventID)
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

bool const ExtendedIdListItemSet::hasEqualElementsExcludingLast(ExtendedIdListItemSet &idListItemSet) {
    AtomList localAtoms = this->allAtomsFlattened();
    AtomList remoteAtoms = idListItemSet.allAtomsFlattened();
    for (int i = 0; i < localAtoms.size() - 1; ++i) {
        if (localAtoms[i] != remoteAtoms[i]) {
            return false;
        }
    }
    return true;
}

AtomList ExtendedIdListItemSet::allAtomsFlattened() {
    AtomList allAtoms;
    for (AtomSet atomSet : _atomSets) {
        copy(begin(atomSet.atoms()), end(atomSet.atoms()), back_inserter(allAtoms));
    }
    return allAtoms;
}
