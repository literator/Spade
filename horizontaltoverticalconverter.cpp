#include "horizontaltoverticalconverter.h"
#include "transaction.h"
#include <algorithm>

HorizontalToVerticalConverter::HorizontalToVerticalConverter() {}

IdListItems HorizontalToVerticalConverter::convertTransactions(TransactionList &transactionList)
{
    IdListItems idListItems;

    for(const Transaction transaction : transactionList)
    {
        for(const Item item : transaction.items())
        {
            auto idListItemPtrIterator = find_if(begin(idListItems),
                                              end(idListItems),
                                              [&](const IdListItemPtr itemPtr) { return itemPtr->item() == item; });

            bool itemAlreadyExists = idListItemPtrIterator != end(idListItems);
            auto itemPtr = itemAlreadyExists ?
                        *idListItemPtrIterator :
                        make_shared<IdListItem>(new IdListItem(item));

            IdListPair pair = make_pair<SequenceID, EventID>(transaction.sequenceID(),
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
