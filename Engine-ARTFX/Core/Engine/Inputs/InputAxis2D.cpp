#include "InputAxis2D.h"

InputAxis2D::InputAxis2D(SDL_Keycode positiveX, SDL_Keycode negativeX, SDL_Keycode positiveY, SDL_Keycode negativeY, std::string name)
    : mPositiveX(positiveX), mNegativeX(negativeX), mPositiveY(positiveY), mNegativeY(negativeY),
      x(0), y(0), InputActions(name)
{
}

ActionType InputAxis2D::GetType() const
{
    return ActionType::Axis2D;
}

void InputAxis2D::Update()
{
    float newX = static_cast<float>((IsKeyPressed(mPositiveX) ? 1 : 0) - (IsKeyPressed(mNegativeX) ? 1 : 0));
    float newY = static_cast<float>((IsKeyPressed(mPositiveY) ? 1 : 0) - (IsKeyPressed(mNegativeY) ? 1 : 0));
    if (newX != x || newY != y) {
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
