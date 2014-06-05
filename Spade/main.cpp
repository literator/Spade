#include <iostream>

#include "Config/Config.h"
#include "Config/ConfigReader.h"
#include "DataReading/FileManagement.h"
#include "DataReading/DataReader.h"
#include "Model/IdListItemSet.h"
#include "Model/IdListSequenceSet.h"
#include "DatabaseConvertion/DatabaseConverter.h"
#include "FrequentItemsCalculator.h"
#include "CommandLineProcessing/InputProcessor.h"
#include "CommandLineProcessing/InputBooleanProcessstep.h"
#include "CommandLineProcessing/InputTryCatchProcessStep.h"
#include "Utilities/Timer.h"

using namespace std;

int main(int argc, char **argv) {
    InputReader input;
    OutputWriter output;
    Config config;

    auto processor = make_shared<InputProcessor>(new InputProcessor());

    processor->addStep(new InputBooleanProcessStep([&]() {
        cerr << "Invalid parameter count.\nThe command to run the program  - \"" << argv[0] << " <input file path> <result file path>\"." << endl;
    }, InputErrorReturnCode::WrongParametersCount, argc != 3));

    processor->addStep(new InputTryCatchProcessStep([&]() {
        input.openFile(string(argv[1]));
    }, InputErrorReturnCode::OpeningInputFile));

    processor->addStep(new InputTryCatchProcessStep([&]() {
        output.openFile(string(argv[2]));
    }, InputErrorReturnCode::OpeningOutputFile));

    processor->addStep(new InputTryCatchProcessStep([&]() {
        ConfigReader cr = ConfigReader::getInstance();
        cr.readConfig(input);
        config = cr.getConfig();
    }, InputErrorReturnCode::ReadingConfiguration));

    InputErrorReturnCode status = processor->processSteps();
    if (status != InputErrorReturnCode::Success) {
        return (int) status;
    }

    DataReader dataReader;
    TransactionList transactions = dataReader.readTransactions(input);

    DatabaseConverter converter;
    IdListItemSets idListItems = converter.convertHorizontalToVertical(transactions);

    Timer timer;
    FrequentItemsCalculator fiCalculator(config.minSupport());
    IdListItemSets oneFrequentItems = fiCalculator.oneFrequentItems(idListItems);

    cout << "1 frequent items(" << oneFrequentItems.size() << "):" << endl;
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

    return (int) InputErrorReturnCode::Success;
}

