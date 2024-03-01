#pragma once

#include "Event.h"

namespace Core {

class MouseMovedEvent : public Event {
   private:
    float mouseX, mouseY;

   public:
    MouseMovedEvent(float x, float y)
        : mouseX(x), mouseY(y) {}

    inline float GetX() const { return mouseX; }
    inline float GetY() const { return mouseY; }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << mouseX << ", " << mouseY;
        return ss.str();
    }

    EVENT_CLASS_TYPE(Core::EventType::MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
};

class MouseScrolledEvent : public Event {
   private:
    float xOffset, yOffset;

   public:
    MouseScrolledEvent(float _xOffset, float _yOffset)
        : xOffset(_xOffset), yOffset(_yOffset) {}

    inline float GetXOffset() const { return xOffset; }
    inline float GetYOffset() const { return yOffset; }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
        return ss.str();
    }

    EVENT_CLASS_TYPE(Core::EventType::MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
};

class MouseButtonEvent : public Event {
   protected:
    int button;
    MouseButtonEvent(int _button)
        : button(_button) {}

   public:
    inline int GetMouseButton() const { return button; }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
};

class MouseButtonPressedEvent : public MouseButtonEvent {
   public:
    MouseButtonPressedEvent(int button)
        : MouseButtonEvent(button) {}

    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(Core::EventType::MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
   public:
    MouseButtonReleasedEvent(int button)
        : MouseButtonEvent(button) {}

    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(Core::EventType::MouseButtonReleased)
};

}  // namespace Core