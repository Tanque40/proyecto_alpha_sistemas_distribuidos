#include "Event.h"

namespace Core {

class KeyEvent : public Event {
   protected:
    int keyCode;
    KeyEvent(int _keycode)
        : keyCode(_keycode) {}

   public:
    inline int GetKeyCode() const { return keyCode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
};

class KeyPressedEvent : public KeyEvent {
   private:
    int repeatCount;

   public:
    KeyPressedEvent(int keycode, int _repeatCount)
        : KeyEvent(keycode), repeatCount(_repeatCount) {}

    inline int GetRepeatCount() const { return repeatCount; }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << keyCode << " (" << repeatCount << " repeats)";
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)
};

class KeyReleasedEvent : public KeyEvent {
   public:
    KeyReleasedEvent(int keycode)
        : KeyEvent(keycode) {}

    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << keyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
};

class KeyTypedEvent : public KeyEvent {
   public:
    KeyTypedEvent(int keycode)
        : KeyEvent(keycode) {}

    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << keyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyTyped)
};

}  // namespace Core