#pragma once
#include "InputActions.h"

class IActionListener {
public:
	virtual ~IActionListener() = default;
	virtual void OnActionTriggered(InputActions* action) = 0;
};
