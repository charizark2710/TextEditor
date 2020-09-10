#include "test.h"

namespace test
{

    TestMenu::TestMenu(Test *&currentTestPointer) : currentTest(currentTestPointer) {}

    void TestMenu::onImGuiRender(const bool &window)
    {
        if (window)
        {
            bool show_window = window;
            ImGui::Begin("Test",&show_window);
            for (auto &test : m_test)
            {
                if (ImGui::Button(test.first.c_str()))
                {
                    currentTest = test.second();
                }
            }
            ImGui::End();
        }
    }

    void TestMenu::onRender()
    {
        glClearColor(color[0], color[1], color[2], color[3]);
    }

} // namespace test