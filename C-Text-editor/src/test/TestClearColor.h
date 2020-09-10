#pragma once

#include "test.h"

namespace test
{
    class testClearColor : public Test
    {
    private:
        float color[4];
    public:
        testClearColor(/* args */);
        ~testClearColor();
        void onUpdate(float time) override;
        void onRender() override;
        void onImGuiRender(const bool &window) override;
    };

} // namespace test