#pragma once

#include "Layer.h"
#include "../Window.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace App
{
    class ImGuiLayer : public Layer
    {
    private:
    public:
        ImGuiLayer(/* args */);
        ~ImGuiLayer();

        void OnAttatch() override;
        void OnDetatch() override;
        void OnUpdate() override;
        void OnRender(GLFWwindow *window) override;
        void OnEvent(Event &event) override;
    };
} // namespace App