#pragma once

#include <iostream>
#include "../Types.h"

using namespace std;

class AtomSet;

typedef vector<AtomSet> AtomSetList;

class AtomSet {
private:
    AtomList _atoms;
public:
    AtomSet();
    AtomSet(AtomList);
    AtomSet(const AtomSet &);
    AtomSet(const AtomSet *);
    ~AtomSet();

    void addAtom(Atom atom);
    void removeAtom(Atom atom);

    bool atomExists(Atom atom) const;

    AtomList const &atoms() const {
        return _atoms;
    }

    int const size() const { return _atoms.size(); }

    void addAtomsToAtomList(AtomList &atomList) {
        for (auto atom : _atoms) {
            atomList.push_back(atom);
        }
    }

    bool operator==(const AtomSet &atomSet) const {
        return _atoms == atomSet._atoms;
    }

    bool operator!=(const AtomSet &atomSet) const {
        return !(*this == atomSet);
    }

    bool operator>(const AtomSet &atomSet) const {
        return _atoms > atomSet._atoms;
    }

    bool operator<(const AtomSet &atomSet) const {
        return _atoms < atomSet._atoms;
    }

    friend ostream &operator<<(ostream &os, const AtomSet &atomSet) {
        static char alphabet[26] = "ABCDEFGHIJKLMNOPQRSTUWXYZ";
        uint index = 0;
        os << "itemSet: {";
        for (const auto item : atomSet.atoms()) {
            if (index != 0) {os << ", ";}
            os << alphabet[item - 1];
            index++;
        }
        os << "}";
        return os;
    }
};
