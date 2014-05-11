#include "inputprocessor.h"


void InputProcessor::addStep(const InputProcessStep step)
{
    _steps.push_back(step);
}

InputErrorReturnCode InputProcessor::processSteps()
{
    for(InputProcessStep step : _steps) {
        InputErrorReturnCode code = step.processAction();
        if(code != InputErrorReturnCode::NoError) {
            return code;
        }
    }
    return InputErrorReturnCode::NoError;
}
