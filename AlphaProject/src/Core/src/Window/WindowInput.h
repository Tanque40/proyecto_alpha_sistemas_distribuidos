#pragma once

#include "Core/Input.h"

namespace Core {

class WindowInput : public Input {
   protected:
    virtual bool IsKeyPressed(int keycode);

    virtual bool IsMouseButtonPressed(int button);
    virtual std::pair<float, float> GetMousePosition();
    virtual float GetMouseX();
    virtual float GetMouseY();
};

}  // namespace Core