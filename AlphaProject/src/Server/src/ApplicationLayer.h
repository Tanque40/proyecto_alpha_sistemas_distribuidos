#pragma once

#include <EntryPoint.h>
#include <EntryPointUtils.h>

class ApplicationLayer : public Core::Layer {
   private:
    Core::Utils::Shader* m_Shader;
    Core::Utils::OrthographicCameraController m_CameraController;

    GLuint m_QuadVA, m_QuadVB, m_QuadIB;

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