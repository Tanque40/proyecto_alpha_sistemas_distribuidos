#include "appch.h"
#include "WindowManager.h"

#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

#ifdef __WINDOWS__

#endif  // WINDOWS

#ifdef __APPLE__
#include <GL/glew.h>
#endif  // APPLE

#include <GLFW/glfw3.h>

namespace Core {

static bool GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char* description) {
    std::cout << "GLFW Error (" << error << "): " << description << std::endl;
}

Window* Window::Create(const WindowProps& props) {
    return new WindowManager(props);
}

WindowManager::WindowManager(const WindowProps& props) {
    Init(props);
}

WindowManager::~WindowManager() {
    Shutdown();
}

void WindowManager::OnUpdate() {
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void WindowManager::SetVSync(bool enabled) {
    if (enabled)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    windowData.VSync = enabled;
}

bool WindowManager::IsVSync() const {
    return windowData.VSync;
}

void WindowManager::Shutdown() {
    glfwDestroyWindow(window);
}

void WindowManager::Init(const WindowProps& props) {
    windowData.Title = props.Title;
    windowData.Width = props.Width;
    windowData.Height = props.Height;

    if (!GLFWInitialized) {
        int succes = glfwInit();
        if (!succes) {
            std::cout << "Could not initialize GLFW! Program should Stop" << std::endl;
            glfwTerminate();
        }
        glfwSetErrorCallback(GLFWErrorCallback);
        GLFWInitialized = true;
    }

    window = glfwCreateWindow((int)props.Width, (int)props.Height, windowData.Title.c_str(), nullptr, nullptr);

    glfwMakeContextCurrent(window);
#ifdef __APPLE__
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
        glfwTerminate();
    }
#endif  // APPLE

    std::cout << "OPENGL INFO:" << std::endl;
    std::cout << "\tVENDOR: " << glewGetString(GL_VENDOR) << std::endl;
    std::cout << "\tRENDERER: " << glewGetString(GL_RENDER) << std::endl;
    std::cout << "\tVERSION: " << glewGetString(GL_VERSION) << std::endl;

    glfwSetWindowUserPointer(window, &windowData);
    SetVSync(true);

    // Set GLFW callbacks
    glfwSetWindowSizeCallback(window, [](GLFWwindow* gWindow, int width, int height) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(gWindow);
        data.Width = width;
        data.Height = height;

        WindowResizeEvent event(width, height);
        data.EventCallback(event);
    });

    glfwSetWindowCloseCallback(window, [](GLFWwindow* gWindow) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(gWindow);
        WindowCloseEvent event;
        data.EventCallback(event);
    });

    glfwSetKeyCallback(window, [](GLFWwindow* gWindow, int key, int scancode, int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(gWindow);

        switch (action) {
            case GLFW_PRESS: {
                KeyPressedEvent event(key, 0);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                KeyReleasedEvent event(key);
                data.EventCallback(event);
                break;
            }
            case GLFW_REPEAT: {
                KeyPressedEvent event(key, 1);
                data.EventCallback(event);
                break;
            }
        }
    });

    glfwSetCharCallback(window, [](GLFWwindow* gWindow, uint32_t keycode) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(gWindow);

        KeyTypedEvent event(keycode);
        data.EventCallback(event);
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* gWindow, int button, int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(gWindow);

        switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent event(button);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent event(button);
                data.EventCallback(event);
                break;
            }
        }
    });

    glfwSetScrollCallback(window, [](GLFWwindow* gWindow, double xOffset, double yOffset) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(gWindow);

        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.EventCallback(event);
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow* gWindow, double xPos, double yPos) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(gWindow);

        MouseMovedEvent event((float)xPos, (float)yPos);
        data.EventCallback(event);
    });
}

}  // namespace Core
