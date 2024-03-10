#pragma once

#include <EntryPoint.h>
#include <EntryPointUtils.h>
#include <glm/glm.hpp>

#include "Core/Renderer/Renderer.h"

class ApplicationLayer : public Core::Layer {
   private:
    // Variables for engine start
    std::unique_ptr<Core::Utils::Shader> shader;
    Core::Utils::OrthographicCameraController m_CameraController;

    GLuint m_QuadVA, m_QuadVB, m_QuadIB;

    // Variables for the game
    int numberOfMoles;
    GLuint moleUp, moleDown, moleWhacked;

    float mouseXPosition, mouseYPosition;

   public:
    ApplicationLayer();
    virtual ~ApplicationLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnEvent(Core::Event& event) override;
    virtual void OnUpdate(Core::TimeStep timeStep) override;
    virtual void OnImGuiRender() override;
};