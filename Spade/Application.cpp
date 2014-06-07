#include "Application.h"
#include <iostream>

#include "Config/ConfigReader.h"
#include "DataReading/DataReader.h"
#include "CommandLineProcessing/InputBooleanProcessstep.h"
#include "CommandLineProcessing/InputTryCatchProcessStep.h"
#include "Algorithm.h"

using namespace std;

Application::Application(int argc, char **argv) : _argc(argc), _argv(argv) {
}

int Application::run() {
    int argc = this->_argc;
    char **argv = this->_argv;

    InputReader input;
    OutputWriter output;
    Config config;

    InputProcessor processor = new InputProcessor();

    processor.addStep(new InputBooleanProcessStep([&]() {
        cerr << "Invalid parameter count.\nThe command to run the program  - \"" << argv[0] << " <input file path> <result file path>\"." << endl;
    }, InputErrorReturnCode::WrongParametersCount, argc != 3));

    processor.addStep(new InputTryCatchProcessStep([&]() {
        input.openFile(string(argv[1]));
    }, InputErrorReturnCode::OpeningInputFile));

    processor.addStep(new InputTryCatchProcessStep([&]() {
        output.openFile(string(argv[2]));
    }, InputErrorReturnCode::OpeningOutputFile));

    processor.addStep(new InputTryCatchProcessStep([&]() {
        ConfigReader cr = ConfigReader::getInstance();
        cr.readConfig(*&input);
        config = cr.getConfig();
    }, InputErrorReturnCode::ReadingConfiguration));
    InputErrorReturnCode status = processor.processSteps();
    if (status != InputErrorReturnCode::Success) {
        return (int) status;
    }

    DataReader dataReader;
    TransactionList transactions = dataReader.readTransactions(input);

    Algorithm algorithm = Algorithm(config);
    algorithm.run(transactions);

    return (int) InputErrorReturnCode::Success;
}

