#include "CustomTextEditor.h"

#include <algorithm>
#include <math.h>
#include <cmath>
#include <chrono>

#include <imgui_internal.h>
namespace App
{
    CustomTextEditor::CustomTextEditor() : Layer("Custom Txt")
    {
    }

    int CustomTextEditor::GetTextIndex(Coord c)
    {
        auto &line = mLines[c.mLine];
        int count = 0;
        for (int i = 0; i <= c.mColumn; i++)
        {
            count++;
        }
        return (count - 1);
    }

    void CustomTextEditor::SetCursorPosition(Coord &c)
    {
        if (c != state.mCursorPosition)
        {
            state.mCursorPosition = c;
        }
        c = GetCurrentCursor();
    }

    //Lấy số dòng mà con trỏ đang chỉ tới
    int CustomTextEditor::CalculateCurrentLine()
    {
        float firstLine = cursorScreenPos.y;
        float lastLine = CursorPos.y;
        float y = cursorY > lastLine ? lastLine : cursorY;
        float currentLine = (lastLine - y) / charAdvance.y;
        float maxLine = (lastLine - firstLine) / charAdvance.y;
        float result = std::round(maxLine - currentLine);
        return result;
    }

    //Lấy số cột mà con trỏ đang chỉ tới
    int CustomTextEditor::CalculateCurrentIndex(int line)
    {
        Line lineContent = mLines[line];
        float lineStart = cursorScreenPos.x;
        float lineEnd = cursorScreenPos.x + (charAdvance.x * lineContent.size());

        float x = cursorX > lineEnd ? lineEnd : cursorX;
        float currentIndex = (lineEnd - x) / charAdvance.x;
        float thisLine = (lineEnd - lineStart) / charAdvance.x;
        float result = std::round(thisLine - currentIndex);
        return result;
    }

    //Lụm số dòng và số cột khi có click chuột
    CustomTextEditor::Coord CustomTextEditor::GetCurrentCursor()
    {
        Coord coord;

        if (isClicked)
        {
            int Y = CalculateCurrentLine();
            int X = CalculateCurrentIndex(Y);
            coord = {X, Y};
        }
        return coord;
    }

    CustomTextEditor::Line &CustomTextEditor::InsertLine(int line)
    {
        auto &result = *mLines.emplace(mLines.begin() + line, Line());
        return result;
    }

    void CustomTextEditor::InsertTab(int column)
    {
        mLines[state.mCursorPosition.mLine].emplace(mLines[state.mCursorPosition.mLine].begin() + column, TextCustom(ImGui::GetColorU32(ImGuiCol_Text), ' '));
        mLines[state.mCursorPosition.mLine].emplace(mLines[state.mCursorPosition.mLine].begin() + column + 1, TextCustom(ImGui::GetColorU32(ImGuiCol_Text), ' '));
        mLines[state.mCursorPosition.mLine].emplace(mLines[state.mCursorPosition.mLine].begin() + column + 2, TextCustom(ImGui::GetColorU32(ImGuiCol_Text), ' '));
        mLines[state.mCursorPosition.mLine].emplace(mLines[state.mCursorPosition.mLine].begin() + column + 3, TextCustom(ImGui::GetColorU32(ImGuiCol_Text), ' '));
    }

    void CustomTextEditor::OnRender(GLFWwindow *window)
    {
        ImGui::Begin((this->GetName()).c_str());
        ImGui::BeginChild("XXX");
        cursorScreenPos = ImGui::GetCursorScreenPos();
        ImGuiIO &io = ImGui::GetIO();
        io.MouseClickedPos;
        if (ImGui::IsWindowFocused())
        {
            if (ImGui::IsWindowHovered())
            {
                ImGui::SetMouseCursor(ImGuiMouseCursor_TextInput);
                ImVec2 origin = io.MousePos;
                cursorX = origin.x;
                cursorY = origin.y;
            }

            m_window->SetEventCallback([&](App::Event &event) {
                // std::cout << event.toString() << std::endl;
                OnEvent(event);
            });
        }
        else
        {
            m_window->SetEventCallback([&](App::Event &event) {
                // std::cout << event.toString() << std::endl;
            });
        }

        SetUp();

        ImGui::EndChild();
        ImGui::End();
        isClicked = false;
    }

    void CustomTextEditor::SetUp()
    {
        const float fontSize = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, -1.0f, "#", nullptr, nullptr).x;
        charAdvance = ImVec2(fontSize, ImGui::GetTextLineHeightWithSpacing() * 1.0f);
        auto contentSize = ImGui::GetWindowContentRegionMax();
        auto drawList = ImGui::GetWindowDrawList();
        auto scrollX = ImGui::GetScrollX();
        auto scrollY = ImGui::GetScrollY();
        auto lineNo = (int)std::floor(scrollY / charAdvance.y);
        auto globalLineMax = (int)mLines.size();
        auto lineMax = std::max(0, std::min((int)mLines.size() - 1, lineNo + (int)floor((scrollY + contentSize.y) / charAdvance.y)));
        ImVec2 cursor_offset;
        ImGuiIO &io = ImGui::GetIO();
        ImVec2 textScreenPos;
        if (!mLines.empty())
        {
            float spaceSize = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, -1.0f, " ", nullptr, nullptr).x;
            while (lineNo <= lineMax)
            {
                ImVec2 lineStartScreenPos = ImVec2(cursorScreenPos.x, cursorScreenPos.y + lineNo * charAdvance.y);
                textScreenPos = ImVec2(lineStartScreenPos.x, lineStartScreenPos.y);
                auto &line = mLines[lineNo];
                int columnNo = 0;
                Coord lineStart(0, lineNo);
                Coord lineEnd(line.size(), lineNo);
                const ImVec2 draw_scroll = ImVec2(scrollX, 0.0f);

                //Render Text
                ImVec2 bufferOffset;
                for (int i = 0; i < line.size(); i++)
                {
                    auto t = line[i];
                    mLineBuffer.push_back(t.mtext);
                }

                if (!mLineBuffer.empty())
                {
                    const ImVec2 newOffset(textScreenPos.x + bufferOffset.x, textScreenPos.y + bufferOffset.y);
                    drawList->AddText(newOffset, ImGui::GetColorU32(ImGuiCol_Text), mLineBuffer.c_str());
                    mLineBuffer.clear();
                }
                lineNo++;
            }
            CursorPos = textScreenPos;
            // draw cursor
            Coord currentCur = state.mCursorPosition;
            if (ImGui::IsWindowFocused())
            {
                blink += io.DeltaTime;
                bool cursor_is_visible = (!io.ConfigInputTextCursorBlink) || (blink <= 0.0f) || fmodf(blink, 1.20f) <= 0.80f;
                if (cursor_is_visible)
                {
                    ImVec2 cstart(CursorPos.x + (currentCur.mColumn * spaceSize), cursorScreenPos.y + currentCur.mLine * charAdvance.y);
                    cursor = cstart;
                    ImVec2 cend(cstart.x, cstart.y + ImGui::GetFontSize());
                    ImRect rectCursor(cstart, cend);
                    drawList->AddLine(rectCursor.Min, rectCursor.Max, ImGui::GetColorU32(ImGuiCol_Text));
                }
            }
        }
    }

    void CustomTextEditor::OnUpdate()
    {
    }

    void CustomTextEditor::OnEvent(Event &event)
    {
        //Xử lý đầu vào đặc biệt
        EventDispatcher dispatch(event);
        dispatch.Dispatch<KeyPressEvent>([&](KeyPressEvent e) {
            int cline = state.mCursorPosition.mLine;
            int column = mLines.empty() ? 0 : state.mCursorPosition.mColumn;

            Coord coord(column, cline);

            auto &line = mLines[coord.mLine];

            switch (e.getKeyCode())
            {
            case 257:
                //Enter
                InsertLine(coord.mLine + 1);
                state.mCursorPosition.mColumn = 0;
                state.mCursorPosition.mLine++;
                break;
            case 258:
                //Tab
                InsertTab(coord.mColumn);
                state.mCursorPosition.mColumn += 4;
                break;
            case 259:
                //Backspace
                if (coord.mLine > 0 && coord.mColumn == 0)
                {
                    state.mCursorPosition.mColumn = mLines[--state.mCursorPosition.mLine].size();
                    mLines.pop_back();
                }
                if (!line.empty())
                {
                    line.pop_back();
                    state.mCursorPosition.mColumn--;
                }
                break;
            default:
                break;
            }
            return false;
        });

        //Xử lý các chữ cái thông thường kể cả utf-8 (utf-8 khó quá tính sau)
        dispatch.Dispatch<KeyTypedEvent>([&](KeyTypedEvent e) {
            int cline = state.mCursorPosition.mLine;
            int column = mLines.empty() ? 0 : state.mCursorPosition.mColumn;

            Coord coord(column, cline);

            int i = 0;
            char buf[7];

            char aChar = (char)e.getKeyCode();
            i = ImTextCharToUtf8(buf, 7, aChar);

            if (i > 0)
            {
                auto &line = mLines[coord.mLine];
                auto index = GetTextIndex(coord);
                buf[i] = '\0';
                for (char *c = buf; *c != '\0'; c++, ++index)
                {
                    line.emplace(line.begin() + index, TextCustom(ImGui::GetColorU32(ImGuiCol_Text), *c));
                }
                state.mCursorPosition.mColumn++;
            }
            return false;
        });

        //Nhấn chuột trái
        dispatch.Dispatch<MouseButtonPressedEvent>([&](MouseButtonPressedEvent e) {
            isClicked = true;
            SetCursorPosition(state.mCursorPosition);
            std::cout << cursorX << " : " << cursorY << std::endl;
            return false;
        });

        //Di Chuột
        //Chưa biết nên làm gì vì đống dispatch hoạt động trên cả chương trình thay vì trên cửa sổ imgui hiện tại
        dispatch.Dispatch<MouseMovedEvent>([&](MouseMovedEvent e) {
            return false;
        });
    }

    void CustomTextEditor::OnAttatch()
    {
        m_window = &Window::Get();
        mLines.push_back(Line());
    }

    void CustomTextEditor::OnDetatch() {}

} // namespace App