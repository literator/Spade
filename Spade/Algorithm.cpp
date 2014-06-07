#include "Algorithm.h"
#include "Model/IdListItemSet.h"
#include "Model/IdListSequenceSet.h"
#include "Model/ExtendedIdListItemSet.h"
#include "Algorithm/FrequentItemsCalculator.h"
#include "DatabaseConvertion/DatabaseConverter.h"
#include "Utilities/Timer.h"

using namespace std;

Algorithm::Algorithm(Config &config) : _config(config) {}

void Algorithm::run(TransactionList transactions) {
    DatabaseConverter converter;
    IdListItemSets idListItems = converter.convertHorizontalToVertical(transactions);

    Timer timer;
    FrequentItemsCalculator fiCalculator(_config.minSupport());
    IdListItemSets oneFrequentItems = fiCalculator.oneFrequentItems(idListItems);

    cout << "1 frequent items (" << oneFrequentItems.size() << "):" << endl;
    for (const IdListItemSetPtr itemPtr : oneFrequentItems) {
        cout << (*itemPtr) << endl;
    }

    IdListSequenceSets idListSequenceSets = converter.convertVerticalToHorizontal(oneFrequentItems);

    ExtendedIdListItemSetList twoFrequentItems = fiCalculator.twoFrequentItems(idListSequenceSets);

    fiCalculator.sort(twoFrequentItems);

    cout << "2 frequent items (" << twoFrequentItems.size() << "):" << endl;
    for (const ExtendedIdListItemSet idListItemSet : twoFrequentItems) {
        cout << idListItemSet << endl;
    }

    fiCalculator.enumerateFrequentSequences(twoFrequentItems);
    cout << "Elapsed: " << timer.elapsed() << endl;
}
