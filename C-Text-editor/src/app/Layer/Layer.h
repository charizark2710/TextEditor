#pragma once

#include <memory>

#include "../Event/Event.h"
#include "glfw3.h"

#include "../Window.h"
namespace App
{
    class Layer
    {
    public:
        Layer(const std::string &name = "Layer");
        virtual ~Layer();

        virtual void OnAttatch() {}
        virtual void OnDetatch() {}
        virtual void OnUpdate() {}
        virtual void OnRender(GLFWwindow *window) {}
        virtual void OnEvent(Event &event) {}

        inline const std::string &GetName() const { return m_DebugName; }
        Window *m_window;
        const char *glsl_version = "#version 130";

    protected:
        std::string m_DebugName;
    };
} // namespace App