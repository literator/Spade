#include "horizontaltoverticalconverter.h"
#include "transaction.h"
#include "idlistitem.h"
#include <algorithm>

HorizontalToVerticalConverter::HorizontalToVerticalConverter() {}

IdListItemSets HorizontalToVerticalConverter::convertTransactions(TransactionList &transactionList)
{
    IdListItemSets idListItems;

    for(const Transaction transaction : transactionList)
    {
        for(const Item item : transaction.items())
        {
            auto idListItemPtrIterator = find_if(begin(idListItems),
                                                 end(idListItems),
                                                 [&](const IdListItemSetPtr itemPtr)
            {
                return itemPtr->itemSet().itemExists(item);
            });

            bool itemAlreadyExists = idListItemPtrIterator != end(idListItems);
            auto itemPtr = itemAlreadyExists ?
                        *idListItemPtrIterator :
                        make_shared<IdListItemSet>(new IdListItemSet(item));

            SequenceEventPair pair = make_pair<SequenceID, EventID>(transaction.sequenceID(),
                                                             transaction.eventID());
            itemPtr->addPair(pair);
            if(!itemAlreadyExists)
            {
                idListItems.push_back(itemPtr);
            }
        }
    }

    return idListItems;
}
