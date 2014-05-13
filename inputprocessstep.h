#pragma once

#include <functional>

enum class InputErrorReturnCode : int {
    NoError = 0,
    WrongParametersCount = 1,
    OpeningInputFile = 2,
    OpeningOutputFile = 3,
    ReadingConfiguration = 4,
    Unknown = 5,
};

typedef std::function<void()> ActionBlock;

class InputProcessStep
{
protected:
    ActionBlock _action;
    InputErrorReturnCode _errorCode;
public:
    InputProcessStep(ActionBlock action, InputErrorReturnCode errorCode)
        : _action(action), _errorCode(errorCode) {}

    virtual InputErrorReturnCode processAction() { return InputErrorReturnCode::Unknown; }
    virtual ~InputProcessStep() {}
};
