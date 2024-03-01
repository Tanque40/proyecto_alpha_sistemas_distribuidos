#pragma once

#include "Core/Input.h"

namespace Core {

class WindowInput : public Input {
   protected:
    virtual bool IsKeyPressedImpl(int keycode);

    virtual bool IsMouseButtonPressedImpl(int button);
    virtual std::pair<float, float> GetMousePositionImpl();
    virtual float GetMouseXImpl();
    virtual float GetMouseYImpl();
};

}  // namespace Core