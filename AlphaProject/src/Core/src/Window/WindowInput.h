#include "Core/Input.h"

namespace Core {

class WindowInput : public Input {
   protected:
    virtual bool IsKeyPressedImplementation(int keycode) override;

    virtual bool IsMouseButtonPressedImplementation(int button) override;
    virtual std::pair<float, float> GetMousePositionImplementation() override;
    virtual float GetMouseXImpementation() override;
    virtual float GetMouseYImplementation() override;
};

}  // namespace Core