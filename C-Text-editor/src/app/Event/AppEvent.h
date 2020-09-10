#pragma once

#include "Event.h"

namespace App
{
    class WindowResizeEvent : public Event
    {
    private:
        unsigned int m_width, m_height;

    public:
        WindowResizeEvent(unsigned int width, unsigned int height) : m_height(height), m_width(width) {}
        ~WindowResizeEvent() {}
        inline unsigned int getWidth() { return m_width; }
        inline unsigned int getHeight() { return m_height; }
        std::string toString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_width << "x" << m_height;
            return ss.str();
        }
        EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApp)
        EVENT_CLASS_TYPE(WindowResize)
    };

    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() {}
        EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApp)
        EVENT_CLASS_TYPE(WindowClose)
    };

    class AppTickEvent : public Event
    {
    public:
        AppTickEvent() {}
        ~AppTickEvent() {}

        EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApp)
        EVENT_CLASS_TYPE(AppTick)
    };

    class AppUpdateEvent : public Event
    {
    public:
        AppUpdateEvent() {}
        ~AppUpdateEvent() {}

        EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApp)
        EVENT_CLASS_TYPE(AppUpdate)
    };

    class AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() {}
        ~AppRenderEvent() {}

        EVENT_CLASS_CATEGORY((int)EventCategory::EventCategoryApp)
        EVENT_CLASS_TYPE(AppRender)
    };
} // namespace App