#pragma once
#include "ActionType.h"
#include "SDL.h"
#include "Vector2D.h"
#include <vector>

class IActionListener;

class InputActions
{
public :
	InputActions(std::string name);
	virtual ~InputActions() = default;

	virtual ActionType GetType() const = 0;
	virtual void Update() = 0;

	std::string GetName();
	void SetName(std::string newName);

	void AddListener(IActionListener* listener);
	void RemoveListener(IActionListener* listener);
	void ClearListeners();
protected:
	void NotifyListenersStarted();
	void NotifyListenersTriggered();
	void NotifyListenersEnded();
private:
	std::vector<IActionListener*> mListeners;
	std::string mName;
};
