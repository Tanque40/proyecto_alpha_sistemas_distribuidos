#pragma once

#include <glm/glm.hpp>

namespace Core::Utils {

class OrthographicCamera {
   private:
    glm::mat4 projectionMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 viewProjectionMatrix;

    glm::vec3 position = {0.0f, 0.0f, 0.0f};
    float rotation = 0.0f;

   public:
    OrthographicCamera(float left, float right, float bottom, float top);

    void SetProjection(float left, float right, float bottom, float top);

    const glm::vec3& GetPosition() const { return position; }
    void SetPosition(const glm::vec3& _position) {
        position = _position;
        RecalculateViewMatrix();
    }

    float GetRotation() const { return rotation; }
    void SetRotation(float _rotation) {
        rotation = _rotation;
        RecalculateViewMatrix();
    }

    const glm::mat4& GetProjectionMatrix() const { return projectionMatrix; }
    const glm::mat4& GetViewMatrix() const { return viewMatrix; }
    const glm::mat4& GetViewProjectionMatrix() const { return viewProjectionMatrix; }

   private:
    void RecalculateViewMatrix();
};

}  // namespace Core::Utils
