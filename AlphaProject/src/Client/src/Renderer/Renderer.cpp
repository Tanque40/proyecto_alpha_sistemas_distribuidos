#include "Renderer.h"

#include <EntryPoint.h>
#include <array>
#ifdef __APPLE__
#include <GL/glew.h>
#endif  // APPLE

static const size_t MaxQuadCount = 1000;
static const size_t MaxVertexCount = MaxQuadCount * 4;
static const size_t MaxIndexCount = MaxQuadCount * 6;
static const size_t MaxTextures = 16;

struct Vertex {
    glm::vec3 Position;
    glm::vec4 Color;
    glm::vec2 TexCoords;
    float TextureIndex;
};

struct RendererData {
    GLuint QuadVA = 0;
    GLuint QuadVB = 0;
    GLuint QuadIB = 0;

    GLuint WhiteTexture = 0;
    uint32_t WhiteTextureSlot = 0;

    uint32_t IndexCount = 0;

    Vertex* QuadBuffer = nullptr;
    Vertex* QuadBufferPtr = nullptr;

    std::array<uint32_t, MaxTextures> TextureSlots;
    uint32_t TextureSlotIndex = 1;

    Renderer::Stats RendererStats;
};

static RendererData rendererData;
static uint32_t shaderId;

void Renderer::Init(uint32_t _shaderId) {
    shaderId = _shaderId;
    rendererData.QuadBuffer = new Vertex[MaxVertexCount];

    glGenVertexArrays(1, &rendererData.QuadVA);
    glBindVertexArray(rendererData.QuadVA);

    glGenBuffers(1, &rendererData.QuadVB);
    glBindBuffer(GL_ARRAY_BUFFER, rendererData.QuadVB);
    glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoords));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TextureIndex));

    uint32_t indices[MaxIndexCount];
    uint32_t offset = 0;
    for (size_t i = 0; i < MaxIndexCount; i += 6) {
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 2 + offset;

        indices[i + 3] = 0 + offset;
        indices[i + 4] = 3 + offset;
        indices[i + 5] = 2 + offset;

        offset += 4;
    }

    glGenBuffers(1, &rendererData.QuadIB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererData.QuadIB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // ? 1 x 1 white texture
    glGenTextures(1, &rendererData.WhiteTexture);
    glBindTexture(GL_TEXTURE_2D, rendererData.WhiteTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    uint32_t color = 0xffffffff;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);

    rendererData.TextureSlots[0] = rendererData.WhiteTexture;
    glActiveTexture(GL_TEXTURE0);
    for (size_t i = 1; i < MaxTextures; i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        rendererData.TextureSlots[i] = 0;
    }
}

void Renderer::Shutdown() {
    glDeleteVertexArrays(1, &rendererData.QuadVA);
    glDeleteBuffers(1, &rendererData.QuadVB);
    glDeleteBuffers(1, &rendererData.QuadIB);

    glDeleteTextures(1, &rendererData.WhiteTexture);

    delete[] rendererData.QuadBuffer;
}

void Renderer::BeginBatch() {
    rendererData.QuadBufferPtr = rendererData.QuadBuffer;
}

void Renderer::EndBatch() {
    GLsizeiptr size = (uint8_t*)rendererData.QuadBufferPtr - (uint8_t*)rendererData.QuadBuffer;
    glBindBuffer(GL_ARRAY_BUFFER, rendererData.QuadVB);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, rendererData.QuadBuffer);
}

void Renderer::Flush() {
    for (uint32_t i = 0; i < rendererData.TextureSlotIndex; i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, rendererData.TextureSlots[i]);
        glUniform1i(glGetUniformLocation(shaderId, "u_Textures"), i);
    }

    glBindVertexArray(rendererData.QuadVA);
    glDrawElements(GL_TRIANGLES, rendererData.IndexCount, GL_UNSIGNED_INT, nullptr);
    rendererData.RendererStats.DrawCount++;

    rendererData.IndexCount = 0;
    rendererData.TextureSlotIndex = 1;
}

void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
    if (rendererData.IndexCount >= MaxIndexCount) {
        EndBatch();
        Flush();
        BeginBatch();
    }

    float textureIndex = 0.0f;

    rendererData.QuadBufferPtr->Position = {position.x, position.y, 0.0f};
    rendererData.QuadBufferPtr->Color = color;
    rendererData.QuadBufferPtr->TexCoords = {0.0f, 0.0f};
    rendererData.QuadBufferPtr->TextureIndex = textureIndex;
    rendererData.QuadBufferPtr++;

    rendererData.QuadBufferPtr->Position = {position.x + size.x, position.y, 0.0f};
    rendererData.QuadBufferPtr->Color = color;
    rendererData.QuadBufferPtr->TexCoords = {0.0f, 0.0f};
    rendererData.QuadBufferPtr->TextureIndex = textureIndex;
    rendererData.QuadBufferPtr++;

    rendererData.QuadBufferPtr->Position = {position.x + size.x, position.y + size.y, 0.0f};
    rendererData.QuadBufferPtr->Color = color;
    rendererData.QuadBufferPtr->TexCoords = {1.0f, 1.0f};
    rendererData.QuadBufferPtr->TextureIndex = textureIndex;
    rendererData.QuadBufferPtr++;

    rendererData.QuadBufferPtr->Position = {position.x, position.y + size.y, 0.0f};
    rendererData.QuadBufferPtr->Color = color;
    rendererData.QuadBufferPtr->TexCoords = {0.0f, 1.0f};
    rendererData.QuadBufferPtr->TextureIndex = textureIndex;
    rendererData.QuadBufferPtr++;

    rendererData.IndexCount += 6;
    rendererData.RendererStats.QuadCount++;
}

void Renderer::DrawQuad(const glm::vec2& position, const glm::vec2& size, uint32_t textureId) {
    if (rendererData.IndexCount >= MaxIndexCount || rendererData.TextureSlotIndex > 31) {
        EndBatch();
        Flush();
        BeginBatch();
    }

    constexpr glm::vec4 color = {1.0f, 1.0f, 1.0f, 1.0f};

    float textureIndex = 0.0f;
    for (size_t i = 1; i < rendererData.TextureSlotIndex; i++) {
        if (rendererData.TextureSlots[i] == textureId) {
            textureIndex = (float)i;
            break;
        }
    }

    if (textureIndex == 0.0f) {
        textureIndex = (float)rendererData.TextureSlotIndex;
        rendererData.TextureSlots[rendererData.TextureSlotIndex] = textureId;
        rendererData.TextureSlotIndex++;
    }

    rendererData.QuadBufferPtr->Position = {position.x, position.y, 0.0f};
    rendererData.QuadBufferPtr->Color = color;
    rendererData.QuadBufferPtr->TexCoords = {0.0f, 0.0f};
    rendererData.QuadBufferPtr->TextureIndex = textureIndex;
    rendererData.QuadBufferPtr++;

    rendererData.QuadBufferPtr->Position = {position.x + size.x, position.y, 0.0f};
    rendererData.QuadBufferPtr->Color = color;
    rendererData.QuadBufferPtr->TexCoords = {1.0f, 0.0f};
    rendererData.QuadBufferPtr->TextureIndex = textureIndex;
    rendererData.QuadBufferPtr++;

    rendererData.QuadBufferPtr->Position = {position.x + size.x, position.y + size.y, 0.0f};
    rendererData.QuadBufferPtr->Color = color;
    rendererData.QuadBufferPtr->TexCoords = {1.0f, 1.0f};
    rendererData.QuadBufferPtr->TextureIndex = textureIndex;
    rendererData.QuadBufferPtr++;

    rendererData.QuadBufferPtr->Position = {position.x, position.y + size.y, 0.0f};
    rendererData.QuadBufferPtr->Color = color;
    rendererData.QuadBufferPtr->TexCoords = {0.0f, 1.0f};
    rendererData.QuadBufferPtr->TextureIndex = textureIndex;
    rendererData.QuadBufferPtr++;

    rendererData.IndexCount += 6;
    rendererData.RendererStats.QuadCount++;
}

const Renderer::Stats& Renderer::GetStats() {
    return rendererData.RendererStats;
}

void Renderer::ResetStats() {
    memset(&rendererData.RendererStats, 0, sizeof(Stats));
}