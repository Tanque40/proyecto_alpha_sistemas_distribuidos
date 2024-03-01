#include "appch.h"
#include "WindowInput.h"

#include "Core/Application.h"
#include <GLFW/glfw3.h>

namespace Core {

Input* Input::inputInstance = new WindowInput();

bool WindowInput::IsKeyPressedImplementation(int keycode) {
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool WindowInput::IsMouseButtonPressedImplementation(int button) {
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
}

std::pair<float, float> WindowInput::GetMousePositionImplementation() {
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    return {(float)xpos, (float)ypos};
}

float WindowInput::GetMouseXImplementation() {
    auto [x, y] = GetMousePositionImpl();
    return x;
}

float WindowInput::GetMouseYImplementation() {
    auto [x, y] = GetMousePositionImpl();
    return y;
}

}  // namespace Core
