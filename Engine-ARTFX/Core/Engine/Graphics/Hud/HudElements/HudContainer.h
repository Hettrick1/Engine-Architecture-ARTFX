#pragma once
#include "HudElement.h"
#include "RendererOpenGl.h"

#include <vector>

class HudContainer
	: public HudElement
{
public:
    void AddElement(HudElement* element) {
        mElements.push_back(element);
    }

    void Draw(RendererOpenGl& renderer) override {
        for (auto& element : mElements) {
            element->Draw(renderer);
        }
    }

private:
    std::vector<HudElement*> mElements;
};

