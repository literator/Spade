#include "idlistitem.h"
#include "itemset.h"

IdListItemSet::IdListItemSet() : support(0), _itemSet(ItemSet()), _idListPairs(IdListPairs()) {}

IdListItemSet::IdListItemSet(Item item) : support(0), _itemSet(ItemSet()), _idListPairs(IdListPairs())
{
    _itemSet.addItem(item);
}

IdListItemSet::IdListItemSet(ItemSet itemSet) : support(0), _itemSet(itemSet), _idListPairs(IdListPairs()) {}

IdListItemSet::IdListItemSet(IdListItemSet *item)
{
    this->support = item->support;
    this->_itemSet = item->_itemSet;
    this->_idListPairs = item->_idListPairs;
}

IdListItemSet::IdListItemSet(const IdListItemSet &item)
{
    this->_itemSet = item._itemSet;
    this->_idListPairs = item._idListPairs;
}

IdListItemSet::~IdListItemSet()
{
    _idListPairs.clear();
}

void IdListItemSet::addPair(IdListPair pair)
{
    _idListPairs.push_back(pair);
}



