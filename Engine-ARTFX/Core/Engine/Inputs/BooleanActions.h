#pragma once
#include "InputActions.h"

class BooleanActions :
    public InputActions
{
public :
    BooleanActions(SDL_Keycode key, std::string name);
    ActionType GetType() const override;

    void Update() override;

    bool GetState() const;
private :
    bool mState;
    SDL_Keycode mKey;

    bool IsKeyPressed(SDL_Keycode key) const;
};

