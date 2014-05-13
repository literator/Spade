#pragma once

#include "inputprocessstep.h"

#include <list>

using namespace std;

class InputProcessor
{
private:
    list<InputProcessStep *> _steps;
public:
    InputProcessor();
    InputProcessor(InputProcessor *);
    ~InputProcessor();

    void addStep(InputProcessStep *step);

    InputErrorReturnCode processSteps();
};
