#ifndef IDLISTITEM_H
#define IDLISTITEM_H

#include "Types.h"
#include <list>
#include <iostream>

using namespace std;

typedef pair<SequenceID, EventID> IdListPair;
typedef list<IdListPair> IdListPairs;

class IdListItem
{
private:
    Item _item;
    IdListPairs _idListPairs;
public:
    IdListItem(Item);
    IdListItem(IdListItem *);
    IdListItem(const IdListItem &);
    ~IdListItem();

    inline Item item() const { return _item; }

    void addPair(IdListPair pair);
    inline IdListPairs pairs() const { return _idListPairs; }

    friend ostream& operator<<(ostream& os, const IdListItem& item)
    {
        os << "item: " << item.item() << ", pairs: ";
        for(const auto &pair : item.pairs())
        {
            os << "[" << pair.first << "," << pair.second << "], ";
        }
        return os;
    }
};

#endif // IDLISTITEM_H
