#pragma once

#include "Core.h"

#include "Window.h"
#include "LayerStack.h"
#include "../Events/Event.h"
#include "../Events/ApplicationEvent.h"

#include "TimeStep.h"

#include "ImGui/ImGuiLayer.h"

namespace Core {

class Application {
   private:
    std::unique_ptr<Window> window;
    ImGuiLayer* imGuiLayer;
    bool isRunning = true;
    LayerStack layerStack;
    float lastFrameTime = 0.0f;

    static Application* applicationInstance;

   public:
    Application(const std::string& name = "Proyecto Alpha", uint32_t width = 1280, uint32_t height = 720);
    virtual ~Application() = default;

    void Run();

    void OnEvent(Event& event);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);

    inline Window& GetWindow() { return *window; }

    inline static Application& Get() { return *applicationInstance; }

   private:
    bool OnWindowClose(WindowCloseEvent& e);
};

}  // namespace Core