#pragma once

#include <iostream>
#include "../Types.h"

using namespace std;

class Transaction
{
private:
    SequenceID _sequenceID;
    EventID _eventID;
    AtomList _itemList;
public:
    Transaction();
    Transaction(const Transaction&);
    Transaction(const SequenceID, const EventID, const AtomList = AtomList());
    ~Transaction();

    inline AtomList items() const { return _itemList; }
    inline SequenceID sequenceID() const { return _sequenceID; }
    inline EventID eventID() const { return _eventID; }

    friend ostream& operator<<(ostream& os, const Transaction& t)
    {
        os << "sid: " << t._sequenceID << ", eid: " << t._eventID << ", items: ";
        for(const auto &item : t.items())
        {
            os << item << " ";
        }
        return os;
    }
};
