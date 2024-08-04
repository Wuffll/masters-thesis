#pragma once

#include "UserInputController.h"

class UserInputSubscriber
{
public:

	virtual void userInputUpdate(const UserInputController& inputController) = 0;

};