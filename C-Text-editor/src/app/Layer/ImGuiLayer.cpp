#include "ImGuiLayer.h"

namespace App
{
    // Our state
    bool show_demo_window = true;
    bool show_app_window = true;
    bool show_another_window = false;

    ImGuiLayer::ImGuiLayer(/* args */) : Layer("ImGUi Layer") {}
    ImGuiLayer::~ImGuiLayer() {}

    void ImGuiLayer::OnAttatch()
    {
    }

    void ImGuiLayer::OnDetatch()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnUpdate()
    {
        // m_window->SetEventCallback([&](App::Event &event) {
        //     OnEvent(event);
        //     return false;
        // });
    }

    void ImGuiLayer::OnRender(GLFWwindow *window)
    {

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static int counter = 0;

            ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");          // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window); // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);
            ImGui::ColorEdit3("clear color", (float *)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();

            ImGui::Begin("XXX");
            ImGui::BeginChild("XXX");
            ImGui::Text("avccccc \n ccccccc \n ssssss \n hhhhhhhhhhh");

            ImGuiIO &io = ImGui::GetIO();

            if (ImGui::IsWindowFocused())
            {
                if (ImGui::IsWindowHovered())
                    ImGui::SetMouseCursor(ImGuiMouseCursor_TextInput);
                //ImGui::CaptureKeyboardFromApp(true);

                for (int i = 0; i < io.InputQueueCharacters.Size; i++)
                {
                    auto c = io.InputQueueCharacters[i];
                    if (c != 0 && (c == '\n' || c >= 32))
                       std::cout << c << std::endl;
                }
                io.InputQueueCharacters.resize(0);
            }
        }
        ImGui::PushAllowKeyboardFocus(true);
        ImGui::EndChild();
        ImGui::End();

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }
    }

    void ImGuiLayer::OnEvent(Event &event)
    {
        std::cout << "ImGui layer event \t " << event.toString() << std::endl;
    }
} // namespace App