#include "Transaction.h"

Transaction::Transaction() {}

Transaction::Transaction(const Transaction &transaction)
{
    this->_sequenceID = transaction._sequenceID;
    this->_eventID = transaction._eventID;
    this->_itemList = transaction._itemList;
}

Transaction::Transaction(const SequenceID sequenceID, const EventID eventID, const ItemList itemList) :
    _sequenceID(sequenceID), _eventID(eventID), _itemList(itemList) {}

Transaction::~Transaction()
{
    _itemList.clear();
}
