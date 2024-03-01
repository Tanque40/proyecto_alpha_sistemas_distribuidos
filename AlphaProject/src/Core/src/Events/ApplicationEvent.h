#pragma once

#include "Event.h"

namespace Core {

class WindowResizeEvent : public Event {
   private:
    uint32_t width, height;

   public:
    WindowResizeEvent(uint32_t _width, uint32_t _height)
        : width(_width), height(_height) {}

    inline uint32_t GetWidth() const { return width; }
    inline uint32_t GetHeight() const { return height; }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << width << ", " << height;
        return ss.str();
    }

    EVENT_CLASS_TYPE(Core::EventType::WindowResize)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WindowCloseEvent : public Event {
   public:
    WindowCloseEvent() {}

    EVENT_CLASS_TYPE(Core::EventType::WindowClose)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppTickEvent : public Event {
   public:
    AppTickEvent() {}

    EVENT_CLASS_TYPE(Core::EventType::AppTick)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppUpdateEvent : public Event {
   public:
    AppUpdateEvent() {}

    EVENT_CLASS_TYPE(Core::EventType::AppUpdate)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppRenderEvent : public Event {
   public:
    AppRenderEvent() {}

    EVENT_CLASS_TYPE(Core::EventType::AppRender)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

}  // namespace Core