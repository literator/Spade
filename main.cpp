#include <iostream>

#include "filemanagement.h"
#include "config.h"
#include "configreader.h"
#include "datareader.h"
#include "idlistitem.h"
#include "horizontaltoverticalconverter.h"
#include "onefrequentitemscalculator.h"
#include "inputprocessor.h"
#include "inputbooleanprocessstep.h"
#include "inputtrycatchprocessstep.h"

using namespace std;

int main(int argc, char** argv)
{
    InputReader input;
    OutputWriter output;
    Config config;

    auto processor = make_shared<InputProcessor>(new InputProcessor());

    processor->addStep(new InputBooleanProcessStep([&] () {
        cerr << "Invalid parameter count.\nThe command to run the program  - \"" << argv[0] << " <input file path> <result file path>\"." << endl;
    }, InputErrorReturnCode::WrongParametersCount, argc != 3));

    processor->addStep(new InputTryCatchProcessStep([&] () {
        input.openFile(string(argv[1]));
    }, InputErrorReturnCode::OpeningInputFile));

    processor->addStep(new InputTryCatchProcessStep([&] () {
        output.openFile(string(argv[2]));
    }, InputErrorReturnCode::OpeningOutputFile));

    processor->addStep(new InputTryCatchProcessStep([&] () {
        ConfigReader cr = ConfigReader::getInstance();
        cr.readConfig(input);
        config = cr.getConfig();
    }, InputErrorReturnCode::ReadingConfiguration));

    InputErrorReturnCode status = processor->processSteps();
    if(status != InputErrorReturnCode::NoError)
    {
        return (int)status;
    }

    DataReader dataReader;
    TransactionList transactions = dataReader.readTransactions(input);

    HorizontalToVerticalConverter converter;
    IdListItemSets idListItems = converter.convertTransactions(transactions);

    OneFrequentItemsCalculator ofiCalculator(config.minSupport());
    IdListItemSets oneFrequentItems = ofiCalculator.oneFrequentItems(idListItems);

    for (const IdListItemSetPtr itemPtr : oneFrequentItems)
    {
        cout << *itemPtr << endl;
    }

    return 0;
}

