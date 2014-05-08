#include "transaction.h"

#include "Types.h"

Transaction::Transaction() {}

Transaction::Transaction(const Transaction &transaction)
{
    this->_sequenceID = transaction._sequenceID;
    this->_eventID = transaction._eventID;
    this->_itemlist = transaction._itemlist;
}

Transaction::Transaction(const SequenceID sequenceID, const EventID eventID, const ItemList itemList) :
    _sequenceID(sequenceID), _eventID(eventID), _itemlist(itemList) {}

Transaction::~Transaction()
{
    _itemlist.clear();
}
