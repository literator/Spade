#ifndef INPUTPROCESSOR_H
#define INPUTPROCESSOR_H

#include "inputprocessstep.h"

#include <list>

using namespace std;

class InputProcessor
{
private:
    list<InputProcessStep> _steps;
public:
    InputProcessor();
    InputProcessor(InputProcessor *);

    void addStep(const InputProcessStep step);

    InputErrorReturnCode processSteps();
};

#endif // INPUTPROCESSOR_H
