#include "BooleanActions.h"
#include <iostream>

BooleanActions::BooleanActions(SDL_Keycode key)
	:mKey(key), mState(false)
{
}

ActionType BooleanActions::GetType() const
{
	return ActionType::Boolean;
}

void BooleanActions::Update()
{
	bool newState = IsKeyPressed(mKey);
	if (newState != mState) {
		mState = newState;
		NotifyListeners();
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
