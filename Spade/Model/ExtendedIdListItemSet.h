#pragma once

#include "../Types.h"
#include "AtomSet.h"

using namespace std;

class ExtendedIdListItemSet;

typedef vector<ExtendedIdListItemSet> ExtendedIdListItemSetList;

class ExtendedIdListItemSet {
private:
    AtomSetList _atomSets;

    void createExtendedIdListItemSet(AtomSet itemSet, AtomSet innerItemSet);
    void createPreviousNextItemSet(AtomSet itemSet, AtomSet innerItemSet);

public:
    unsigned int support;
    SequenceEventPairs sequenceEventPairs;

    ExtendedIdListItemSet(unsigned int support = 0);
    ExtendedIdListItemSet(AtomSetList const &atomSets);
    ExtendedIdListItemSet(SequenceID sequenceId, AtomSet itemSet, EventID eventID, AtomSet innerItemSet, EventID innerEventID);

    ExtendedIdListItemSet(const ExtendedIdListItemSet &);
    ExtendedIdListItemSet(const ExtendedIdListItemSet *);

    void recalculateSupport();

    void addPairIfNotExists(SequenceEventPair pair);

    bool const hasEqualElementsExcludingLast(ExtendedIdListItemSet &idListItemSet);
    AtomList allAtomsFlattened() const;

    AtomSetList const &atomSets() const {
        return _atomSets;
    }

    void addAtomSet(AtomSet atomSet) {
        _atomSets.push_back(atomSet);
    }

    int const numberOfAtoms() const {
        return allAtomsFlattened().size();
    }

    bool operator==(const ExtendedIdListItemSet &extendedIdListItemSet) const {
        return _atomSets == extendedIdListItemSet._atomSets;
    }

    bool operator!=(const ExtendedIdListItemSet &extendedIdListItemSet) const {
        return !(*this == extendedIdListItemSet);
    }

    bool operator<(const ExtendedIdListItemSet *extendedIdListItemSet) const {
        return _atomSets < extendedIdListItemSet->_atomSets;
    }

    friend ostream &operator<<(ostream &os, const ExtendedIdListItemSet &idListItemSet) {
        os << "support: " << idListItemSet.support << ", itemSets: ";
        for (const auto &itemSet : idListItemSet.atomSets()) {
            os << "[" << itemSet << "], ";
        }
        for (const auto &sequenceEventPair : idListItemSet.sequenceEventPairs) {
            os << "(" << sequenceEventPair.first << "," << sequenceEventPair.second << "), ";
        }
        return os;
    }

    void addAtomToTheLatestAtomSet(Atom atom);
};
