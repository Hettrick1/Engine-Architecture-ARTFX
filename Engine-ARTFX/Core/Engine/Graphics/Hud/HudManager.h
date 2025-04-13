#pragma once
#include "HudElement.h"
#include "RendererOpenGl.h"
#include <vector>

class HudManager
{
public:
    void AddElement(HudElement* element);
    void Draw(RendererOpenGl& renderer);
    void Unload();
private:
    std::vector<HudElement*> mHudElements;
};

