#pragma once

#include <functional>
#include <direct.h>
#include <memory>

#include "..\Renderer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "..\VertexBuffer.h"
#include "..\IndexBuffer.h"
#include "..\VertexArray.h"
#include "..\VertexBufferLayout.h"
#include "..\Shader.h"
#include "..\Texture.h"
#include "glm/gtc/matrix_transform.hpp"

namespace test
{
    class Test
    {
    private:
        /* data */
    public:
        Test(/* args */){};
        virtual ~Test(){};

        virtual void onUpdate(float time) {}

        virtual void onRender() {}

        virtual void onImGuiRender(const bool &window) {}
    };

    class TestMenu : public Test
    {
    public:
        TestMenu(Test *&currentTestPointer);
        void onImGuiRender(const bool &window) override;
        void onRender() override;

        template <typename T>
        void RegisterTest(const std::string &name)
        {
            m_test.insert(std::make_pair(name, [] { return new T(); }));
        }

    private:
        /* data */
        float color[4];
        Test *&currentTest;
        std::unordered_map<std::string, std::function<Test *()>> m_test;
    };
} // namespace test