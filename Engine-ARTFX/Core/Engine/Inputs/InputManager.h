#pragma once
#include "InputActions.h"
#include "IActionListener.h"
#include <unordered_map>

class InputManager
{
public:
    static InputManager& Instance();
    ~InputManager();
    void CreateNewBooleanKeyBinding(IActionListener* listener, std::string name, SDL_Keycode key);
    void CreateNewBooleanBtnBinding(IActionListener* listener, std::string name, Uint8 mouseButton);
    void CreateNewAxis2DBinding(IActionListener* listener, std::string name, SDL_Keycode positiveX = SDLK_UNKNOWN, SDL_Keycode negativeX = SDLK_UNKNOWN, SDL_Keycode positiveY = SDLK_UNKNOWN, SDL_Keycode negativeY = SDLK_UNKNOWN);
    void Update();
private:
    void BindActionToKeys(InputActions* action, const std::vector<SDL_Keycode>& keys);
    void BindActionToMouse(InputActions* action);
    std::unordered_map<SDL_Keycode, std::vector<InputActions*>> mActionKeyBindings;
    std::vector<InputActions*> mActionMouseBindings;
};

