#pragma once

#include "Window.h"

namespace App
{
    class WindowWindow : public Window
    {

    public:
        WindowWindow(const WindowProps &props);
        ~WindowWindow();

        void OnUpdate() override;

        unsigned int GetWidth() const override { return m_Data.Width; }
        unsigned int GetHeight() const override { return m_Data.Height; }

        void SetEventCallback(const EventCallbackFn &callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        virtual GLFWwindow *GetNativeWindow() const { return m_Window; }

    private:
        virtual void Init(const WindowProps &props);
        virtual void Shutdown();
        GLFWwindow *m_Window;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };

} // namespace App
