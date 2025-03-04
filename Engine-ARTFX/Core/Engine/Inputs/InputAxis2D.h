#pragma once
#include "InputActions.h"
class InputAxis2D : public InputActions
{
public:
    InputAxis2D(SDL_Keycode positiveX, SDL_Keycode negativeX, SDL_Keycode positiveY, SDL_Keycode negativeY, std::string name);

    InputAxis2D(std::string name);

    ActionType GetType() const override;

    void Update() override;

    Vector2D GetAxis() const;

private:
    bool mUseMouse;
    SDL_Keycode mPositiveX, mNegativeX, mPositiveY, mNegativeY;
    float x, y;
    bool IsKeyPressed(SDL_Keycode key) const;
};

