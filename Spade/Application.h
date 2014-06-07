#include "Config/Config.h"
#include "CommandLineProcessing/InputProcessor.h"
#include "DataReading/FileManagement.h"

#pragma once

class Application {
private:
    int _argc;
    char **_argv;
public:
    Application(int argc, char **argv);
    int run();
};
