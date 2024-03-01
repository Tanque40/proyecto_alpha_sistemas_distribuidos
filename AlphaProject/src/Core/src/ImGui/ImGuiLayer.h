#pragma once

#include "Core/Layer.h"

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace Core {

class ImGuiLayer : public Layer {
   private:
    float time = 0.0f;

   public:
    ImGuiLayer();
    ~ImGuiLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void Begin();
    void End();

    virtual void OnEvent(Event& event) override;
    bool OnMouseButtonPressed(MouseButtonPressedEvent& mouseEvent);
};

}  // namespace Core