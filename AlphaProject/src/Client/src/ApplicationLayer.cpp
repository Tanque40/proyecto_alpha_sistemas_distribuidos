#include "ApplicationLayer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui_internal.h"
#include <math.h>
#include <stb_image.h>

#include "Core/Renderer/FrameBuffer.h"

using namespace Core;
using namespace Core::Utils;

ApplicationLayer::ApplicationLayer() : m_CameraController(16.0f / 9.0f, false), numberOfMoles(9) {
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

    clientSocket = SocketTCP(SocketType::Client, "127.0.0.1");
    // FrameBuffer::CreateFrameBuffer();
}

void ApplicationLayer::OnDetach() {
    Renderer::Shutdown();
}

float elapsedTime = 0.0f;

void ApplicationLayer::OnUpdate(Core::TimeStep timeStep) {
    m_CameraController.OnUpdate(timeStep);

    // FrameBuffer::Bind();

    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shader->GetRendererID());

    Renderer::ResetStats();
    Renderer::BeginBatch();

    elapsedTime += timeStep.GetSeconds();

    float zoom = m_CameraController.GetZoomLevel();
    float leftSideWindow = -16.0f / 9.0f * zoom;
    float rightSideWindow = 16.0f / 9.0f * zoom;
    float squareSizeY = (2.0f * zoom) / sqrt(numberOfMoles);
    float squareSizeX = (rightSideWindow - leftSideWindow) / sqrt(numberOfMoles);
    for (float x = leftSideWindow; x < rightSideWindow; x += squareSizeX) {
        for (float y = -1.0f * zoom; y < 1.0f * zoom; y += squareSizeY) {
            if ((int)elapsedTime % 9 < 3)
                Renderer::DrawQuad({x, y}, glm::vec2(squareSizeX, squareSizeY), moleDown);
            else if ((int)elapsedTime % 9 < 6)
                Renderer::DrawQuad({x, y}, glm::vec2(squareSizeX, squareSizeY), moleUp);
            else
                Renderer::DrawQuad({x, y}, glm::vec2(squareSizeX, squareSizeY), moleWhacked);
        }
    }

    Renderer::EndBatch();
    auto vp = m_CameraController.GetCamera().GetViewProjectionMatrix();
    SetUnifornMat4(shader->GetRendererID(), "u_ViewProjection", vp);
    SetUnifornMat4(shader->GetRendererID(), "u_Transform", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.3f)));

    Renderer::Flush();
    glUseProgram(0);
    // FrameBuffer::UnBind();
}

void ApplicationLayer::OnImGuiRender() {
    ImGui::Begin("Settings");
    {
        ImGui::SeparatorText("Game Controls");
        for (size_t i = 1; i <= 8; i++) {
            int numberOfMolesImGui = i * i;
            std::string message = "Topos: " + std::to_string(numberOfMolesImGui);
            ImGui::RadioButton(message.c_str(), &numberOfMoles, numberOfMolesImGui);
        }

        ImGui::SeparatorText("ServerConnection");
        if (ImGui::Button("Send Message")) {
            std::string response;
            std::string message = "Hola desde GUI";
            if (clientSocket.SendMessage(0, &message)) {
                if (clientSocket.ReciveMessage(0, &response))
                    std::cout << response.c_str() << std::endl;
                clientSocket.EndConnection();
                clientSocket = SocketTCP(SocketType::Client, "127.0.0.1");
            }
        }
    }
    ImGui::End();

    /* ImGui::Begin("Game Window");
    {
        float windowWidth = ImGui::GetContentRegionAvail().x;
        float windowHeight = ImGui::GetContentRegionAvail().y;
        FrameBuffer::Rescale(windowWidth, windowHeight);
        float aspectRatio = windowWidth / windowHeight;
        m_CameraController.GetCamera().SetProjection(-aspectRatio * m_CameraController.GetZoomLevel(),
                                                     aspectRatio * m_CameraController.GetZoomLevel(),
                                                     -m_CameraController.GetZoomLevel(),
                                                     m_CameraController.GetZoomLevel());
        ImVec2 pos = ImGui::GetCursorScreenPos();

        ImGui::Image(
            (ImTextureID*)FrameBuffer::GetTextureFrameBufferId(),
            ImGui::GetContentRegionAvail(),
            ImVec2(0, 1),
            ImVec2(1, 0));
    }
    ImGui::End(); */
}

void ApplicationLayer::OnEvent(Core::Event& event) {
    m_CameraController.OnEvent(event);

    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MouseMovedEvent>(
        [&](MouseMovedEvent& e) {
            mouseXPosition = e.GetX();
            mouseYPosition = e.GetY();
            return false;
        });
    dispatcher.Dispatch<MouseButtonPressedEvent>(
        [&](MouseButtonPressedEvent& e) {
            std::cout << mouseXPosition << ", " << mouseYPosition << std::endl;
            return false;
        });
    dispatcher.Dispatch<MouseButtonReleasedEvent>(
        [&](MouseButtonReleasedEvent& e) {
            return false;
        });
}

ApplicationLayer::~ApplicationLayer() {
}