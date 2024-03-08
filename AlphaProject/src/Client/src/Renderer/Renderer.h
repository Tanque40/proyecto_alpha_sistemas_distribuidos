#pragma once

#include <glm/glm.hpp>
#include <EntryPointUtils.h>

// ? 2D batch renderer
class Renderer {
   public:
    // ?  Renderer Stats
    struct Stats {
        uint32_t DrawCount = 0;
        uint32_t QuadCount = 0;
    };

    static void Init(uint32_t shaderId);
    static void Shutdown();

    static void BeginBatch();
    static void EndBatch();
    static void Flush();

    static void DrawQuad(const glm::vec2& position, const glm::vec2& size, uint32_t textureId);
    static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);

    static const Stats& GetStats();
    static void ResetStats();
};