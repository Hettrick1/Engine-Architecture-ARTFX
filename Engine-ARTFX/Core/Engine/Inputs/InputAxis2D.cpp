#include "InputAxis2D.h"

InputAxis2D::InputAxis2D(SDL_Keycode positiveX, SDL_Keycode negativeX, SDL_Keycode positiveY, SDL_Keycode negativeY, std::string name)
    : mPositiveX(positiveX), mNegativeX(negativeX), mPositiveY(positiveY), mNegativeY(negativeY),
      x(0), y(0), InputActions(name), mUseMouse(false)
{
}

InputAxis2D::InputAxis2D(std::string name)
    : mPositiveX(SDLK_UNKNOWN), mNegativeX(SDLK_UNKNOWN), mPositiveY(SDLK_UNKNOWN), mNegativeY(SDLK_UNKNOWN),
      x(0), y(0), mUseMouse(true), InputActions(name)
{
}

ActionType InputAxis2D::GetType() const
{
    return ActionType::Axis2D;
}

void InputAxis2D::Update()
{
    float newX, newY;

    if (mUseMouse) { // mouse mode

        int deltaX = 0, deltaY = 0; 
        SDL_GetRelativeMouseState(&deltaX, &deltaY); 
        newX = deltaX; 
        newY = deltaY; 

    }
    else { // keyboard mode
        newX = static_cast<float>((IsKeyPressed(mPositiveX) ? 1 : 0) - (IsKeyPressed(mNegativeX) ? 1 : 0));
        newY = static_cast<float>((IsKeyPressed(mPositiveY) ? 1 : 0) - (IsKeyPressed(mNegativeY) ? 1 : 0));
    }

    if (newX != x || newY != y) {
        if (newX != 0 || newY != 0) {
            NotifyListenersStarted();
        }
        else {
            NotifyListenersEnded();
        }
        x = newX;
        y = newY;
        NotifyListenersTriggered();
    }
}

Vector2D InputAxis2D::GetAxis() const
{
    return {x, y};
}

bool InputAxis2D::IsKeyPressed(SDL_Keycode key) const
{
    const Uint8* keyState = SDL_GetKeyboardState(nullptr);
    return keyState[SDL_GetScancodeFromKey(key)] != 0;
}
