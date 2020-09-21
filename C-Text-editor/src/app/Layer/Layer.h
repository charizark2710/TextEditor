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

        virtual void OnAttatch()=0;
        virtual void OnDetatch()=0;
        virtual void OnUpdate()=0;
        virtual void OnRender(GLFWwindow *window)=0;
        virtual void OnEvent(Event &event)=0;

        inline const std::string &GetName() const { return m_DebugName; }
        Window *m_window;
        const char *glsl_version = "#version 130";

    protected:
        std::string m_DebugName;
    };
} // namespace App