#include "appch.h"
#include "OrthographicCameraController.h"

#include "Core/Input.h"
#include "Core/KeyCodes.h"

namespace Core::Utils {

OrthographicCameraController::OrthographicCameraController(float _aspectRatio, bool _rotation)
    : aspectRatio(_aspectRatio), camera(-aspectRatio * zoomLevel, _aspectRatio * zoomLevel, -zoomLevel, zoomLevel), rotation(_rotation) {
}

void OrthographicCameraController::OnUpdate(TimeStep ts) {
    if (Input::IsKeyPressed(RN_KEY_A)) {
        cameraPosition.x -= cos(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
        cameraPosition.y -= sin(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
    } else if (Input::IsKeyPressed(RN_KEY_D)) {
        cameraPosition.x += cos(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
        cameraPosition.y += sin(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
    }

    if (Input::IsKeyPressed(RN_KEY_W)) {
        cameraPosition.x += -sin(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
        cameraPosition.y += cos(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
    } else if (Input::IsKeyPressed(RN_KEY_S)) {
        cameraPosition.x -= -sin(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
        cameraPosition.y -= cos(glm::radians(cameraRotation)) * cameraTranslationSpeed * ts;
    }

    if (rotation) {
        if (Input::IsKeyPressed(RN_KEY_Q))
            cameraRotation += cameraRotationSpeed * ts;
        if (Input::IsKeyPressed(RN_KEY_E))
            cameraRotation -= cameraRotationSpeed * ts;

        if (cameraRotation > 180.0f)
            cameraRotation -= 360.0f;
        else if (cameraRotation <= -180.0f)
            cameraRotation += 360.0f;

        camera.SetRotation(cameraRotation);
    }

    camera.SetPosition(cameraPosition);
    cameraTranslationSpeed = zoomLevel;
}

void OrthographicCameraController::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseScrolledEvent>(CORE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
    dispatcher.Dispatch<WindowResizeEvent>(CORE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e) {
    zoomLevel -= e.GetYOffset() * 0.25f;
    zoomLevel = std::max(zoomLevel, 0.25f);
    camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
    return false;
}

bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e) {
    aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
    camera.SetProjection(-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel);
    return false;
}

}  // namespace Core::Utils