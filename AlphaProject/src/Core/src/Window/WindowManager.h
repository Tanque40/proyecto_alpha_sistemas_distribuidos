#include "Core/Window.h"

#include <GLFW/glfw3.h>

namespace Core {

class WindowManager : public Window {
   private:
    struct WindowData {
        std::string Title;
        uint32_t Width, Height;
        bool VSync;

        EventCallbackFn EventCallback;
    };

    GLFWwindow* window;
    WindowData windowData;

   public:
    WindowManager(const WindowProps& props);
    virtual ~WindowManager();

    void OnUpdate() override;

    inline uint32_t GetWidth() const override { return windowData.Width; }
    inline uint32_t GetHeight() const override { return windowData.Height; }

    // Window attributes
    inline void SetEventCallback(const EventCallbackFn& callback) override { windowData.EventCallback = callback; }
    void SetVSync(bool enabled) override;
    bool IsVSync() const override;

    inline virtual void* GetNativeWindow() const override { return window; }

   private:
    virtual void Init(const WindowProps& props);
    virtual void Shutdown();
};

}  // namespace Core