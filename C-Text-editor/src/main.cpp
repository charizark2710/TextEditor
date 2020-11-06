#include <iostream>
#include <fstream>
#include <sstream>
#include <direct.h>

#include <GL/glew.h>
#include <glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/gtc/matrix_transform.hpp"
#include "test/TestClearColor.h"
#include "GetResolution.h"
#include "test/TestTexture.h"
#include "app/Event/AppEvent.h"
#include "app/Event/Event.h"
#include "app/Window.h"
#include "app/Layer/LayerStack.h"
#include "app/Layer/ImGuiLayer.h"
#include "app/TextEditor/TextEditor.h"
#include "app/TextEditor/CustomTextEditor.h"

int main(int argc, char *argv[])
{

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const char *glsl_version = "#version 130";

    App::Layer *m_ImGuiLayer = new App::ImGuiLayer();
    App::Layer *cText = new App::CustomTextEditor();

    TextEditor *t = new TextEditor();

    std::unique_ptr<App::Window> m_window;
    m_window = std::unique_ptr<App::Window>(App::Window::Create());
    m_window->SetEventCallback([&](App::Event &event) {
        std::cout << event.toString() << std::endl;
    });

    GLFWwindow *window = m_window->GetNativeWindow();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    App::LayerStack layerStack;

    layerStack.PushOverlay(m_ImGuiLayer);
    layerStack.PushLayer(cText);

    //Must create gl context first
    if (glewInit() != GLEW_OK)
    {
        std::cout << "error";
    };

    // Our state
    bool show_demo_window = true;
    bool show_app_window = true;

    test::Test *currentTest = nullptr;
    test::TestMenu *testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;
    testMenu->RegisterTest<test::testClearColor>("Clear color");
    testMenu->RegisterTest<test::TestTexture2D>("Texture2D");

    //check error
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(MessageCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        for (App::Layer *layer : layerStack)
        {
            layer->OnUpdate();
        }

        // if (currentTest)
        // {
        //     currentTest->onUpdate(0.0f);
        //     currentTest->onRender();
        //     currentTest->onImGuiRender(show_demo_window);
        //     if (currentTest != testMenu && ImGui::Button("<-"))
        //     {
        //         delete currentTest;
        //         currentTest = testMenu;
        //         glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        //     }
        // }

        // t->Render("Text");

        // Rendering
        for (App::Layer *layer : layerStack)
        {
            layer->OnRender(window);
        }

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        // glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        // glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        m_window->OnUpdate();
    }

    //Shutdown
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}