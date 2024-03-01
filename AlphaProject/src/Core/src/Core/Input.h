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

    inline static bool IsKeyPressed(int keycode) { return inputInstance->IsKeyPressedImplementation(keycode); }
    inline static bool IsMouseButtonPressed(int button) { return inputInstance->IsMouseButtonPressedImplementation(button); }
    inline static std::pair<float, float> GetMousePosition() { return inputInstance->GetMousePositionImplementation(); }
    inline static float GetMouseX() { return inputInstance->GetMouseXImplementation(); }
    inline static float GetMouseY() { return inputInstance->GetMouseYImplementation(); }
};

}  // namespace Core