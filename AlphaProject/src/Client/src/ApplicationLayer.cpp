#include "ApplicationLayer.h"

#include <glm/gtc/type_ptr.hpp>

using namespace Core;
using namespace Core::Utils;

ApplicationLayer::ApplicationLayer() : m_CameraController(16.0f / 9.0f) {
}

void ApplicationLayer::OnAttach() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_Shader = Shader::FromGLSLTextFiles(
        "AlphaProject/src/Assets/shaders/Client.vertex.glsl",
        "AlphaProject/src/Assets/shaders/Client.frag.glsl");

    glGenVertexArrays(1, &m_QuadVA);
    glBindVertexArray(m_QuadVA);
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f};

    glGenBuffers(1, &m_QuadVB);
    glBindBuffer(GL_ARRAY_BUFFER, m_QuadVB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

    uint32_t indices[] = {0, 1, 2, 2, 3, 0};
    glGenBuffers(1, &m_QuadIB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_QuadIB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void ApplicationLayer::OnDetach() {
    glDeleteVertexArrays(1, &m_QuadVA);
    glDeleteBuffers(1, &m_QuadVB);
    glDeleteBuffers(1, &m_QuadIB);
}

void ApplicationLayer::OnUpdate(Core::TimeStep timeStep) {
    m_CameraController.OnUpdate(timeStep);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(m_Shader->GetRendererID());

    int location = glGetUniformLocation(m_Shader->GetRendererID(), "u_ViewProjection");
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(m_CameraController.GetCamera().GetViewProjectionMatrix()));

    location = glGetUniformLocation(m_Shader->GetRendererID(), "u_Color");
    glUniform4fv(location, 1, m_SquareColor);

    glBindVertexArray(m_QuadVA);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void ApplicationLayer::OnImGuiRender() {
    ImGui::Begin("Controls");
    if (ImGui::ColorEdit4("Square Base Color", m_SquareBaseColor))
        m_SquareColor = m_SquareBaseColor;
    ImGui::ColorEdit4("Square Alternate Color", m_SquareAlternateColor);
    ImGui::End();
}

void ApplicationLayer::OnEvent(Core::Event& event) {
    m_CameraController.OnEvent(event);

    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MouseButtonPressedEvent>(
        [&](MouseButtonPressedEvent& e) {
            m_SquareColor = m_SquareAlternateColor;
            return false;
        });
    dispatcher.Dispatch<MouseButtonReleasedEvent>(
        [&](MouseButtonReleasedEvent& e) {
            m_SquareColor = m_SquareBaseColor;
            return false;
        });
}

ApplicationLayer::~ApplicationLayer() {
}
