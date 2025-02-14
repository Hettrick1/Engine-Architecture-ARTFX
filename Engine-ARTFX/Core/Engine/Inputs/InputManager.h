#pragma once
#include "InputActions.h"
#include "IActionListener.h"
#include <unordered_map>

class InputManager
{
public:
    static InputManager& Instance();
    ~InputManager();
    void CreateNewBooleanBinding(SDL_Keycode key, IActionListener* listener);
    void CreateNewAxis2DBinding(SDL_Keycode positiveX, SDL_Keycode negativeX, SDL_Keycode positiveY, SDL_Keycode negativeY, IActionListener& listener);
    void Update();
private:
    void BindActionToKeys(InputActions* action, const std::vector<SDL_Keycode>& keys);
    std::unordered_map<SDL_Keycode, std::vector<InputActions*>> mActionBindings;
};

