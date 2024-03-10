#pragma once

#include <EntryPoint.h>

// ? Frame Buffer Creator
class FrameBuffer {
   public:
    static void CreateFrameBuffer(uint32_t width = 1280, uint32_t height = 720);
    static void Bind();
    static void UnBind();
    static void Rescale(uint32_t width, uint32_t height);
    static GLuint GetTextureFrameBufferId();
};