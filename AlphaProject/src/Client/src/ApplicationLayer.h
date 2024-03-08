#pragma once

#include <EntryPoint.h>
#include <EntryPointUtils.h>
#include <glm/glm.hpp>

#include "Renderer/Renderer.h"

class ApplicationLayer : public Core::Layer {
   private:
    std::unique_ptr<Core::Utils::Shader> shader;
    Core::Utils::OrthographicCameraController m_CameraController;

    GLuint m_QuadVA, m_QuadVB, m_QuadIB;
    GLuint moleUp, moleDown, moleWhacked;

    float m_SquareBaseColor[4] = {0.8f, 0.2f, 0.3f, 1.0f};
    float m_SquareAlternateColor[4] = {0.2f, 0.3f, 0.8f, 1.0f};
    float* m_SquareColor = m_SquareBaseColor;

   public:
    ApplicationLayer();
    virtual ~ApplicationLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnEvent(Core::Event& event) override;
    virtual void OnUpdate(Core::TimeStep timeStep) override;
    virtual void OnImGuiRender() override;
};