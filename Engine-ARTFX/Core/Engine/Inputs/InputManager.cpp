#include "InputManager.h"
#include "BooleanActions.h"
#include "InputAxis2D.h"

InputManager& InputManager::Instance()
{
    static InputManager instance;
    return instance;
}

InputManager::~InputManager()
{
    for (auto it = mActionBindings.begin(); it != mActionBindings.end(); ++it) {
        auto& key = it->first;
        auto& actions = it->second;
        while (actions.size() > 0) {
            delete actions.back();
            actions.pop_back();
        }
    }
}

void InputManager::CreateNewBooleanBinding(SDL_Keycode key, IActionListener* listener)
{
    if (mActionBindings.find(key) != mActionBindings.end()) {
        std::vector<InputActions*> actionsToBind = mActionBindings[key];
        for (InputActions* action : actionsToBind) {
            action->AddListener(listener);
        }
    }
    else {
        BooleanActions* newAction = new BooleanActions(key);
        newAction->AddListener(listener);
        BindActionToKeys(newAction, { key });
    }
}

void InputManager::CreateNewAxis2DBinding(SDL_Keycode positiveX, SDL_Keycode negativeX, SDL_Keycode positiveY, SDL_Keycode negativeY, IActionListener& listener)
{

}

void InputManager::BindActionToKeys(InputActions* action, const std::vector<SDL_Keycode>& keys)
{
    for (auto& key : keys) {
        mActionBindings[key].push_back(action);
    }
}

void InputManager::Update()
{
    for (auto it = mActionBindings.begin(); it != mActionBindings.end(); ++it) {
        auto& key = it->first;        
        auto& actions = it->second;
        for (auto* action : actions) {
            action->Update();
        }
    }
}
