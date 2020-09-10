#pragma once
#include "Event.h"

namespace App
{
    using MouseCode = uint16_t;

    enum : MouseCode
    {
        // From glfw3.h
        Button0 = 0,
        Button1 = 1,
        Button2 = 2,
        Button3 = 3,
        Button4 = 4,
        Button5 = 5,
        Button6 = 6,
        Button7 = 7,

        ButtonLast = Button7,
        ButtonLeft = Button0,
        ButtonRight = Button1,
        ButtonMiddle = Button2
    };

    class MouseMovedEvent : public Event
    {
    private:
        float X, Y;

    public:
        MouseMovedEvent(float x, float y) : X(x), Y(y) {}
        ~MouseMovedEvent() {}
        inline float getX() { return X; }
        inline float getY() { return Y; }
        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << X << " : " << Y;
            return ss.str();
        }
        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryMouse | (int)EventCategory::EventCategoryInput)
    };

    class MouseScrollEvent : public Event
    {
    public:
        MouseScrollEvent(float offsetX, float offsetY) : x_offset(offsetX), y_offset(offsetY) {}

        inline float getX() { return x_offset; }
        inline float getY() { return y_offset; }
        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseScrollEvent" << x_offset << " : " << y_offset;
            return ss.str();
        }
        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryMouse | (int)EventCategory::EventCategoryInput)

    private:
        float x_offset, y_offset;
    };

    class MouseButtonEvent : public Event
    {
    public:
        MouseCode GetMouseButton() const { return m_Button; }

        EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryMouse | (int)EventCategory::EventCategoryInput)
    protected:
        MouseButtonEvent(const MouseCode button)
            : m_Button(button) {}

        MouseCode m_Button;
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(const MouseCode button)
            : MouseButtonEvent(button) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonRelease)
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(const MouseCode button)
            : MouseButtonEvent(button) {}

        std::string toString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

} // namespace App