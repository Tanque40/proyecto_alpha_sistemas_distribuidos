#pragma once

#include "OrthographicCamera.h"
#include "Core/TimeStep.h"

#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"

namespace Core::Utils {

class OrthographicCameraController {
   private:
    float aspectRatio;
    float zoomLevel = 1.0f;
    OrthographicCamera camera;

    bool rotation;

    glm::vec3 cameraPosition = {0.0f, 0.0f, 0.0f};
    float cameraRotation = 0.0f;  // In degrees, in the anti-clockwise direction
    float cameraTranslationSpeed = 5.0f, cameraRotationSpeed = 180.0f;

   public:
    OrthographicCameraController(float aspectRatio, bool rotation = false);

    void OnUpdate(TimeStep ts);
    void OnEvent(Event& e);

    OrthographicCamera& GetCamera() { return camera; }
    const OrthographicCamera& GetCamera() const { return camera; }

    float GetZoomLevel() const { return zoomLevel; }
    void SetZoomLevel(float level) { zoomLevel = level; }

   private:
    bool OnMouseScrolled(MouseScrolledEvent& e);
    bool OnWindowResized(WindowResizeEvent& e);
};

}  // namespace Core::Utils