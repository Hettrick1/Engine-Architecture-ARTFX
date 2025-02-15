#include "BooleanActions.h"
#include <iostream>

BooleanActions::BooleanActions(SDL_Keycode key, std::string name)
	: mKey(key), mState(false), InputActions(name)
{
}

ActionType BooleanActions::GetType() const
{
	return ActionType::Boolean;
}

void BooleanActions::Update()
{
	bool newState = IsKeyPressed(mKey);
	if (newState == true) {
		NotifyListenersTriggered();
	}
	if (newState != mState) {
		if (newState == true) {
			NotifyListenersStarted();
		}
		else {
			NotifyListenersEnded();
		}
		mState = newState;
	}
}

bool BooleanActions::GetState() const
{
	return mState;
}

bool BooleanActions::IsKeyPressed(SDL_Keycode key) const
{
	const Uint8* keyState = SDL_GetKeyboardState(nullptr);
	return keyState[SDL_GetScancodeFromKey(key)] != 0;
}
