#include "ApplicationLayer.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>

using namespace Core;
using namespace Core::Utils;

ApplicationLayer::ApplicationLayer() : m_CameraController(16.0f / 9.0f, false) {
}

static void SetUnifornMat4(uint32_t shader, const char* name, const glm::mat4& matrix) {
    int location = glGetUniformLocation(shader, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

static GLuint LoadTexture(const std::string& path) {
    int w, h, bits;

    stbi_set_flip_vertically_on_load(1);
    auto* pixels = stbi_load(path.c_str(), &w, &h, &bits, STBI_rgb);
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);

    stbi_image_free(pixels);

    return textureId;
}

void ApplicationLayer::OnAttach() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    shader = std::unique_ptr<Shader>(Shader::FromGLSLTextFiles(
        "AlphaProject/src/Assets/shaders/Client.vertex.glsl",
        "AlphaProject/src/Assets/shaders/Client.frag.glsl"));

    glUseProgram(shader->GetRendererID());
    auto location = glGetUniformLocation(shader->GetRendererID(), "u_Textures");
    int samplers[16];
    for (size_t i = 0; i < 16; i++) {
        samplers[i] = i;
    }
    glUniform1iv(location, 16, samplers);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    Renderer::Init(shader->GetRendererID());

    moleUp = LoadTexture("AlphaProject/src/Assets/sprites/mole_up.png");
    moleDown = LoadTexture("AlphaProject/src/Assets/sprites/mole_down.png");
    moleWhacked = LoadTexture("AlphaProject/src/Assets/sprites/mole_whacked.png");
}

void ApplicationLayer::OnDetach() {
    Renderer::Shutdown();
}

float elapsedTime = 0.0f;

void ApplicationLayer::OnUpdate(Core::TimeStep timeStep) {
    m_CameraController.OnUpdate(timeStep);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader->GetRendererID());

    Renderer::ResetStats();
    Renderer::BeginBatch();

    elapsedTime += timeStep.GetSeconds();
    for (float y = -10.0f; y < 10.0f; y += 0.25f) {
        for (float x = -10.0f; x < 10.0f; x += 0.25f) {
            glm::vec4 color = {(x + 10) / 20.0f, 0.2f, (y + 10) / 20.f, 1.0f};
            if ((int)elapsedTime % 9 < 3) {
                Renderer::DrawQuad({x, y}, {0.25f, 0.25f}, moleWhacked);
            } else if ((int)elapsedTime % 9 < 6) {
                Renderer::DrawQuad({x, y}, {0.25f, 0.25f}, moleDown);
            } else {
                Renderer::DrawQuad({x, y}, {0.25f, 0.25f}, moleUp);
            }
        }
    }

    Renderer::EndBatch();

    auto vp = m_CameraController.GetCamera().GetViewProjectionMatrix();
    SetUnifornMat4(shader->GetRendererID(), "u_ViewProjection", vp);
    SetUnifornMat4(shader->GetRendererID(), "u_Transform", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

    Renderer::Flush();
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