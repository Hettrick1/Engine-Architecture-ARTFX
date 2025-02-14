#include "InputActions.h"
#include "IActionListener.h"

void InputActions::AddListener(IActionListener* listener)
{
	mListeners.push_back(listener);
}

void InputActions::RemoveListener(IActionListener* listenerToRemove)
{
	//mListeners.erase(std::remove(mListeners.begin(), mListeners.end(), listenerToRemove), mListeners.end());
}

void InputActions::NotifyListeners()
{
	for (IActionListener* listener : mListeners) {
		listener->OnActionTriggered(this);
	}
}
