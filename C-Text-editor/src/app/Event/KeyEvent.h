#pragma once

#include "Event.h"

namespace App
{
    class KeyEvent : public Event
    {
    public:
        inline int getKeyCode() const { return m_keyCode; };

        EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryKeyBoard | (int)EventCategory::EventCategoryInput)

    protected:
        KeyEvent(int keycode) : m_keyCode(keycode) {}
        ~KeyEvent() {}
        int m_keyCode;
    };

    class KeyPressEvent : public KeyEvent
    {
    private:
        /* data */
    public:
        KeyPressEvent(int keycode) : KeyEvent(keycode) {}
        ~KeyPressEvent(){};

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyPressEvent: " << m_keyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPress);
    };

    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keycode)
            : KeyEvent(keycode) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_keyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyRelease)
    };

    class KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(int keycode)
            : KeyEvent(keycode) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_keyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyType)
    };
} // namespace App