#pragma once
#include "HudElement.h"
#include "RendererOpenGl.h"

#include <vector>

class HudContainer
	: public HudElement
{
public:
    HudContainer();
    void AddElement(HudElement* element);

    void Draw(RendererOpenGl& renderer) override;

private:
    std::vector<HudElement*> mElements;
};

