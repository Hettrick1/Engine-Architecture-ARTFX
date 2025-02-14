#pragma once
#include "ActionType.h"
#include "SDL.h"
#include "Vector2D.h"
#include <vector>

class IActionListener;

class InputActions
{
public :
	virtual ~InputActions() = default;

	virtual ActionType GetType() const = 0;
	virtual void Update() = 0;

	void AddListener(IActionListener* listener);
	void RemoveListener(IActionListener* listener);
protected:
	void NotifyListeners();
private:
	std::vector<IActionListener*> mListeners;
};
