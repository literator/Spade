#pragma once

#include "InputProcessStep.h"

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
