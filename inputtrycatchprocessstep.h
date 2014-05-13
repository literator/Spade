#pragma once

#include "inputprocessstep.h"
#include <iostream>

using namespace std;

class InputTryCatchProcessStep : public InputProcessStep
{
public:
    InputTryCatchProcessStep(ActionBlock action, InputErrorReturnCode errorCode)
        : InputProcessStep(action, errorCode) {}

    virtual InputErrorReturnCode processAction() final {
        try {
            this->_action();
        } catch(string message) {
            cerr << "Exception occured while processing step: " << message << endl;
            return this->_errorCode;
        } catch(...) {
            cerr << "Unknown error occured" << endl;
            return InputErrorReturnCode::Unknown;
        }
        return InputErrorReturnCode::Success;
    }
};
