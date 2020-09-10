#pragma once

#include <iostream>
#include <sstream>
#include <functional>

#define BIT(x) (1 << x)

namespace App
{

    enum class EventType
    {
        None = 0,
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMove,
        AppTick,
        AppUpdate,
        AppRender,
        KeyPress,
        KeyRelease,
        KeyTypedEvent,
        MouseButtonPressed,
        MouseButtonRelease,
        KeyType,
        MouseMoved,
        MouseScrolled
    };

#define EVENT_CLASS_TYPE(type)                                                  \
    static EventType getStaticType() { return EventType::type; }                \
    virtual EventType getEventType() const override { return getStaticType(); } \
    virtual const char *getName() const override { return #type; }

    enum class EventCategory
    {
        None = 0,
        EventCategoryApp = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyBoard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };

#define EVENT_CLASS_CATEGORY(category) \
    virtual int getCategoryFlag() const override { return category; }

    class Event
    {
        friend class EventDispatcher;

    public:
        virtual EventType getEventType() const = 0;
        virtual const char *getName() const = 0;
        virtual int getCategoryFlag() const = 0;
        virtual std::string toString() const { return getName(); }

        inline bool IsInCategory(EventCategory category)
        {
            return getCategoryFlag() & (int)category;
        }

    protected:
        bool m_handle = false;
    };

    class EventDispatcher
    {
    private:
        Event &m_event;

    public:
        EventDispatcher(Event &event) : m_event(event) {}
        ~EventDispatcher() {}

        template <typename T, typename F>
        bool Dispatch(const F &func)
        {
            if (m_event.getEventType() == T::getStaticType())
            {
                m_event.m_handle = func(static_cast<T &>(m_event));
                return true;
            }
            return false;
        }
    };

} // namespace App
