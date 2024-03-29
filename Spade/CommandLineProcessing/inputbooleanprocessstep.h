#pragma once

#include <string>
#include <iostream>
#include "InputProcessStep.h"

using namespace std;

class InputBooleanProcessStep : public InputProcessStep
{
private:
    bool _condition;
    string _explanation;
public:
    InputBooleanProcessStep(ActionBlock action, InputErrorReturnCode errorCode, bool condition, string explanation = "")
        : InputProcessStep(action, errorCode), _condition(condition), _explanation(explanation) {}

    virtual InputErrorReturnCode processAction() final {
        if(_condition)
        {
            if(!_explanation.empty())
            {
                cerr << _explanation << endl;
            }
            this->_action();
            return this->_errorCode;
        }
        return InputErrorReturnCode::Success;
    }
};
