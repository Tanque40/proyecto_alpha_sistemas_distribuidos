#pragma once

#include "Core.h"

namespace Core {

class Input {
   private:
    static Input* inputInstance;

   protected:
    Input() = default;

   public:
    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;

    inline static bool IsKeyPressed(int keycode) { return inputInstance->IsKeyPressedImpl(keycode); }
    inline static bool IsMouseButtonPressed(int button) { return inputInstance->IsMouseButtonPressed(button); }
    inline static std::pair<float, float> GetMousePosition() { return inputInstance->GetMousePosition(); }
    inline static float GetMouseX() { return inputInstance->GetMouseX(); }
    inline static float GetMouseY() { return inputInstance->GetMouseY(); }

   protected:
    virtual bool IsKeyPressedImpl(int keycode) = 0;

    virtual bool IsMouseButtonPressedImpl(int button) = 0;
    virtual std::pair<float, float> GetMousePositionImpl() = 0;
    virtual float GetMouseXImpl() = 0;
    virtual float GetMouseYImpl() = 0;
};

}  // namespace Core