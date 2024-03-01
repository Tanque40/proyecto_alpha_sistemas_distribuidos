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

    inline static bool IsKeyPressed(int keycode) { return inputInstance->IsKeyPressed(keycode); }
    inline static bool IsMouseButtonPressed(int button) { return inputInstance->IsMouseButtonPressed(button); }
    inline static std::pair<float, float> GetMousePosition() { return inputInstance->GetMousePosition(); }
    inline static float GetMouseX() { return inputInstance->GetMouseX(); }
    inline static float GetMouseY() { return inputInstance->GetMouseY(); }
};

}  // namespace Core