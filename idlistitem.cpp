#include "idlistitem.h"

IdListItem::IdListItem(Item item) : _item(item), _idListPairs(IdListPairs())
{

}

IdListItem::IdListItem(IdListItem *item)
{
    this->_item = item->_item;
    this->_idListPairs = item->_idListPairs;
}

IdListItem::IdListItem(const IdListItem &item)
{
    this->_item = item._item;
    this->_idListPairs = item._idListPairs;
}

IdListItem::~IdListItem()
{
    _idListPairs.clear();
}

void IdListItem::addPair(IdListPair pair)
{
    _idListPairs.push_back(pair);
}



