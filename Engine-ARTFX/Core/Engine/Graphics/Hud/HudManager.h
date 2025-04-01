#pragma once
#include "HudElement.h"
#include "RendererOpenGl.h"
#include <vector>

class HudManager
{
public:
    void AddElement(HudElement* element) {
        mHudElements.push_back(element);
    }

    void Draw(RendererOpenGl& renderer) {
        for (auto& element : mHudElements) {
            element->Draw(renderer);
        }
    }
private:
    std::vector<HudElement*> mHudElements;
};

