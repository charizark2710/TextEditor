#pragma once

#include "../Layer/Layer.h"

#include <iostream>
#include <vector>
#include <imgui.h>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
namespace App
{
    class CustomTextEditor : public Layer
    {
    public:
        CustomTextEditor();
        virtual ~CustomTextEditor() {}
        struct Coord
        {
            int mColumn;
            int mLine;
            Coord(int column, int line) : mColumn(column), mLine(line) {}
            Coord() : mColumn(0), mLine(0) {}

            bool operator==(const Coord &o) const
            {
                return mLine == o.mLine &&
                       mColumn == o.mColumn;
            }

            bool operator!=(const Coord &o) const
            {
                return mLine != o.mLine ||
                       mColumn != o.mColumn;
            }

            bool operator<(const Coord &o) const
            {
                if (mLine != o.mLine)
                    return mLine < o.mLine;
                return mColumn < o.mColumn;
            }

            bool operator>(const Coord &o) const
            {
                if (mLine != o.mLine)
                    return mLine > o.mLine;
                return mColumn > o.mColumn;
            }

            bool operator<=(const Coord &o) const
            {
                if (mLine != o.mLine)
                    return mLine < o.mLine;
                return mColumn <= o.mColumn;
            }

            bool operator>=(const Coord &o) const
            {
                if (mLine != o.mLine)
                    return mLine > o.mLine;
                return mColumn >= o.mColumn;
            }
        };

        struct TextCustom
        {
            long long mcolor;
            unsigned char mtext;
            TextCustom(long long color, unsigned char text) : mcolor(color), mtext(text) {}
        };

        struct State
        {
            Coord mSelectionStart;
            Coord mSelectionEnd;
            Coord mCursorPosition;
        };

        //Lụm bên ImGui
        static inline int ImTextCharToUtf8(char *buf, int buf_size, unsigned int c)
        {
            if (c < 0x80)
            {
                buf[0] = (char)c;
                return 1;
            }
            if (c < 0x800)
            {
                if (buf_size < 2)
                    return 0;
                buf[0] = (char)(0xc0 + (c >> 6));
                buf[1] = (char)(0x80 + (c & 0x3f));
                return 2;
            }
            if (c >= 0xdc00 && c < 0xe000)
            {
                return 0;
            }
            if (c >= 0xd800 && c < 0xdc00)
            {
                if (buf_size < 4)
                    return 0;
                buf[0] = (char)(0xf0 + (c >> 18));
                buf[1] = (char)(0x80 + ((c >> 12) & 0x3f));
                buf[2] = (char)(0x80 + ((c >> 6) & 0x3f));
                buf[3] = (char)(0x80 + ((c)&0x3f));
                return 4;
            }
            //else if (c < 0x10000)
            {
                if (buf_size < 3)
                    return 0;
                buf[0] = (char)(0xe0 + (c >> 12));
                buf[1] = (char)(0x80 + ((c >> 6) & 0x3f));
                buf[2] = (char)(0x80 + ((c)&0x3f));
                return 3;
            }
        }

        //Render window
        void OnRender(GLFWwindow *window) override;
        void OnEvent(Event &event) override;
        void OnAttatch() override;
        void OnDetatch() override;
        void OnUpdate() override;
        //Set Text, Cursor, Size, .....
        void SetUp();
        int GetTextIndex(Coord c);
        void setSelection();
        //Copy Paste
        void Copy();
        void Paste();
        //Vị trí của con trỏ nhưng với tọa độ đầy đủ
        void SetCursorPosition(Coord &c);
        Coord GetCurrentCursor();
        int CalculateCurrentLine();
        int CalculateCurrentIndex(int line);

    private:
        int countClick = 0;
        bool isClicked = false;
        bool hasSelection = false;
        bool isCtrl = false;
        float blink;
        typedef std::vector<TextCustom> Line;
        typedef std::vector<Line> Lines;
        ImVec2 charAdvance;
        std::string mLineBuffer;
        Lines mLines;
        Line mLine;
        uint64_t mStartTime;
        State state;
        ImVec2 cursor;
        float cursorX = 0.0f;
        float cursorY = 0.0f;
        ImVec2 CursorPos;
        //Vị trí của cửa sổ
        ImVec2 cursorScreenPos;
        std::string clipboardString;
        float textSize = 22.0f;

    public:
        Line &InsertLine(int line);
        void InsertTab(int line);
        void DeleteChar(Line &line, int index = 0);
    };
} // namespace App
