#include "TestTexture.h"

namespace test
{
    TestTexture2D::TestTexture2D(/* args */) : color{0.0f, 0.0f, 0.0f, 0.0f}, modelValue(1.0f, 0.5f, 0.0f),
                                               modelValue2(-1.0f, -1.0f, 0.0f), proj(glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f)),
                                               view(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)))
    {
        float position[] = {
            -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 1.0f};

        unsigned int indices[] = {
            0, 1, 2, //first triangle
            2, 3, 0  //second triangle
        };

        // float RecPosition[8] = {
        //     -0.5f, -0.3f,
        //     0.5f, -0.3f,
        //     0.5f, 0.3f,
        //     -0.5f, 0.3f};

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //vertex buffer
        va = std::make_unique<VertexArray>();
        vb = std::make_unique<VertexBuffer>(position, 16);

        //vertex array
        VertexBufferLayout layout;
        layout.push<float>(2, GL_FLOAT, GL_FALSE);
        layout.push<float>(2, GL_FLOAT, GL_FALSE);
        va->AddBuffer(*vb, layout);

        //index buffer
        ib = std::make_unique<IndexBuffer>(indices, 6);

        //shader
        char *buffer = _getcwd(NULL, 0);
        std::string path = buffer;
        free(buffer);
        shader = std::make_unique<Shader>(path);
        // shader.setUniform4f("u_color", 0.5f, 0.3f, 0.8f, 0.1f);
        shader->Bind();

        //texture
        texture = std::make_unique<Texture>(path);
        texture->Bind();
        shader->setUniform1i("u_texture", 0);

        vb->UnBind();
    }

    TestTexture2D::~TestTexture2D()
    {
    }

    void TestTexture2D::onUpdate(float time)
    {
    }

    void TestTexture2D::onRender()
    {
        //unbind buffer and index buffer and vertex array
        va->UnBind();
        ib->UnBind();
        shader->UnBind();

        //mvp matrix
        proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
        // glm::mat4 proj = glm::perspective(
        //     glm::radians(45.0f), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
        //     4.0f / 3.0f,         // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
        //     0.1f,                // Near clipping plane. Keep as big as possible, or you'll get precision issues.
        //     100.0f               // Far clipping plane. Keep as little as possible.
        // );

        view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        // glm::mat4 view = glm::lookAt(
        //     glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
        //     glm::vec3(0, 0, 0), // and looks at the origin
        //     glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
        // );

        // glm::mat4 model = glm::translate(glm::mat4(1.0f), modelValue);
        // glm::mat4 model = glm::mat4(modelValue);

        // glm::mat4 mvp = proj * view * model;

        Renderer renderer;

        glClearColor(color[0], color[1], color[2], color[3]);
        // first
        {
            model = glm::translate(glm::mat4(1.0f), modelValue);
            // glm::mat4 model = glm::mat4(modelValue);
            mvp = proj * view * model;
            renderer.Draw(*va, *ib, *shader);
            shader->setUniform4fMatrix("u_MVP", mvp);
        }
        //second
        {
            model = glm::translate(glm::mat4(1.0f), modelValue2);
            mvp = proj * view * model;
            // glDrawArrays(GL_QUADS, 0, 4);
            renderer.Draw(*va, *ib, *shader);
            shader->setUniform4fMatrix("u_MVP", mvp);
        }
    }

    void TestTexture2D::onImGuiRender(const bool &window)
    {
        if (window)
        {
            ImGui::SliderFloat3("float", &modelValue.x, 1.0f, 2.0f);    // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderFloat3("float2", &modelValue2.x, -1.0f, 2.0f); // Edit 1 float using a slider from 0.0f to 1.0f
        }
    }
} // namespace test
