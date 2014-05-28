#include "../DatabaseConvertion/DatabaseConverter.h"
#include "../Model/Transaction.h"
#include "../Model/IdListItemSet.h"
#include "../Model/IdListSequenceSet.h"

DatabaseConverter::DatabaseConverter() {
}

IdListItemSets DatabaseConverter::convertHorizontalToVertical(TransactionList &transactionList) {
    IdListItemSets idListItems;

    for (const Transaction transaction : transactionList) {
        for (const Atom item : transaction.items()) {
            auto idListItemPtrIterator = find_if(begin(idListItems),
                    end(idListItems),
                    [&](const IdListItemSetPtr itemPtr) {
                        return itemPtr->itemSet().atomExists(item);
                    });

            bool itemAlreadyExists = idListItemPtrIterator != end(idListItems);
            auto itemPtr = itemAlreadyExists ?
                    *idListItemPtrIterator :
                    make_shared<IdListItemSet>(new IdListItemSet(item));

            SequenceEventPair pair = make_pair(transaction.sequenceID(), transaction.eventID());
            itemPtr->addPair(pair);
            if (!itemAlreadyExists) {
                idListItems.push_back(itemPtr);
            }
        }
    }

    return idListItems;
}

IdListSequenceSets DatabaseConverter::convertVerticalToHorizontal(IdListItemSets &idListItemSets) {
    IdListSequenceSets idListSequenceSets;

    for (auto itemSetPtr : idListItemSets) {
        AtomSet itemSet = itemSetPtr->itemSet();

        for (auto sequenceEventPair : itemSetPtr->pairs()) {
            SequenceID sequenceID = sequenceEventPair.first;
            auto sequenceSetIterator = find_if(
                    begin(idListSequenceSets),
                    end(idListSequenceSets),
                    [&](const IdListSequenceSetPtr sequenceSetPtr) {
                        return sequenceSetPtr->sequenceID() == sequenceID;
                    });

            bool sequenceSetAlreadyExists = sequenceSetIterator != end(idListSequenceSets);
            auto sequenceSetPtr = sequenceSetAlreadyExists ?
                    *sequenceSetIterator :
                    make_shared<IdListSequenceSet>(new IdListSequenceSet(sequenceID));

            ItemSetEventPair pair = make_pair(itemSet, sequenceEventPair.second);
            sequenceSetPtr->addPair(pair);
            if (!sequenceSetAlreadyExists) {
                idListSequenceSets.push_back(sequenceSetPtr);
            }
        }
    }

    return idListSequenceSets;
}
