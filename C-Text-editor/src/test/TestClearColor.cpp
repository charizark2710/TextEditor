#include "TestClearColor.h"

namespace test
{
    testClearColor::testClearColor(/* args */) : color{1.0f, 0.3f, 0.8f, 1.0f}
    {
    }

    testClearColor::~testClearColor()
    {
    }

    void testClearColor::onUpdate(float time)
    {
    }

    void testClearColor::onRender()
    {
        glClearColor(color[0], color[1], color[2], color[3]);
    }

    void testClearColor::onImGuiRender(const bool &window)
    {
        if (window)
        {
            ImGui::ColorEdit4("Clear color", color);
            std::cout << color << std::endl;
        }
    }
} // namespace test
