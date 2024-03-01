#include "appch.h"
#include "Application.h"

#include "Input.h"

#include <GLFW/glfw3.h>

namespace Core {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application* Application::applicationInstance = nullptr;

Application::Application(const std::string& name, uint32_t width, uint32_t height) {
    if (applicationInstance) {
        std::cout << "Application already exists" << std::endl;
    }

    applicationInstance = this;

    window = std::unique_ptr<Window>(Window::Create({name, width, height}));
    window->SetEventCallback(BIND_EVENT_FN(OnEvent));

    imGuiLayer = new ImGuiLayer();
    PushOverlay(imGuiLayer);
}

void Application::PushLayer(Layer* layer) {
    layerStack.PushLayer(layer);
}

void Application::PushOverlay(Layer* layer) {
    layerStack.PushOverlay(layer);
}

void Application::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

    for (auto it = layerStack.end(); it != layerStack.begin();) {
        (*--it)->OnEvent(e);
        if (e.handled)
            break;
    }
}

void Application::Run() {
    while (isRunning) {
        float time = (float)glfwGetTime();
        TimeStep timestep = time - lastFrameTime;
        lastFrameTime = time;

        for (Layer* layer : layerStack)
            layer->OnUpdate(timestep);

        imGuiLayer->Begin();
        for (Layer* layer : layerStack)
            layer->OnImGuiRender();
        imGuiLayer->End();

        window->OnUpdate();
    }
}

bool Application::OnWindowClose(WindowCloseEvent& e) {
    isRunning = false;
    return true;
}

}  // namespace Core