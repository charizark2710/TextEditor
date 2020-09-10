#pragma once

#include <iostream>
#include <functional>
#include <glfw3.h>
#include <direct.h>

#include "Event/Event.h"
#include "Event/AppEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

namespace App
{
    struct WindowProps
    {
        std::string Title;
        int Width;
        int Height;

        WindowProps(const std::string &title = "App",
                    int width = 1280,
                    int height = 720)
            : Title(title), Width(width), Height(height) {}
    };

    class Window
    {
    public:
        using EventCallbackFn = std::function<void(Event &)>;

        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        // Window attributes
        virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual GLFWwindow *GetNativeWindow() const = 0;

        static Window *Create(const WindowProps &props = WindowProps());

        static Window &Get() { return *s_Instance; }

        static Window *s_Instance;
    };

} // namespace App