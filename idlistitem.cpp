#include "idlistitem.h"

IdListItemSet::IdListItemSet() : _itemSet(ItemSet()), _idListPairs(IdListPairs()), support(0) {}

IdListItemSet::IdListItemSet(Item item) : _itemSet(ItemSet()), _idListPairs(IdListPairs()), support(0)
{
    _itemSet.addItem(item);
}

IdListItemSet::IdListItemSet(ItemSet itemSet) :  _itemSet(itemSet), _idListPairs(IdListPairs()), support(0)  {}

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



