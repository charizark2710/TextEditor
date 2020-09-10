#pragma once

#include "test.h"
#include "../Renderer.h"
namespace test
{
    class TestTexture2D : public Test
    {
    private:
        float color[4];
        glm::vec3 modelValue;
        glm::vec3 modelValue2;
        std::unique_ptr<VertexArray> va;
        std::unique_ptr<VertexBuffer> vb;
        std::unique_ptr<IndexBuffer> ib;
        std::unique_ptr<Shader> shader;
        std::unique_ptr<Texture> texture;

        glm::mat4 model, view, proj, mvp;

    public:
        TestTexture2D(/* args */);
        ~TestTexture2D();
        void onUpdate(float time) override;
        void onRender() override;
        void onImGuiRender(const bool &window) override;
    };

} // namespace test