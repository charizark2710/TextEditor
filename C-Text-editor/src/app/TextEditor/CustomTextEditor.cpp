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
        mLines.push_back(Line());
    }

    int CustomTextEditor::GetLastCol(int aline)
    {
        auto &line = mLines[aline];
        return line.size();
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

    CustomTextEditor::Line &CustomTextEditor::InsertLine(int line)
    {
        auto &result = *mLines.emplace(mLines.begin() + line, Line());
        return result;
    }

    void CustomTextEditor::OnRender(GLFWwindow *window)
    {
        ImGui::Begin((this->GetName()).c_str());
        ImGui::BeginChild("XXX");
        ImGuiIO &io = ImGui::GetIO();
        if (ImGui::IsWindowFocused())
        {
            if (ImGui::IsWindowHovered())
                ImGui::SetMouseCursor(ImGuiMouseCursor_TextInput);

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
    }

    void CustomTextEditor::SetUp()
    {
        const float fontSize = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, -1.0f, "#", nullptr, nullptr).x;
        charAdvance = ImVec2(fontSize, ImGui::GetTextLineHeightWithSpacing() * 1.0f);
        auto contentSize = ImGui::GetWindowContentRegionMax();
        auto drawList = ImGui::GetWindowDrawList();

        ImVec2 cursorScreenPos = ImGui::GetCursorScreenPos();
        auto scrollX = ImGui::GetScrollX();
        auto scrollY = ImGui::GetScrollY();
        auto lineNo = (int)std::floor(scrollY / charAdvance.y);
        auto globalLineMax = (int)mLines.size();
        auto lineMax = std::max(0, std::min((int)mLines.size() - 1, lineNo + (int)floor((scrollY + contentSize.y) / charAdvance.y)));
        ImVec2 cursor_offset;
        ImGuiIO &io = ImGui::GetIO();
        if (!mLines.empty())
        {
            float spaceSize = ImGui::GetFont()->CalcTextSizeA(ImGui::GetFontSize(), FLT_MAX, -1.0f, " ", nullptr, nullptr).x;
            while (lineNo <= lineMax)
            {
                ImVec2 lineStartScreenPos = ImVec2(cursorScreenPos.x, cursorScreenPos.y + lineNo * charAdvance.y);
                ImVec2 textScreenPos = ImVec2(lineStartScreenPos.x, lineStartScreenPos.y);
                auto &line = mLines[lineNo];
                int columnNo = 0;
                Coord lineStart(0, lineNo);
                Coord lineEnd(line.size(), lineNo);
                const ImVec2 draw_scroll = ImVec2(scrollX, 0.0f);

                // draw cursor khó quá tính sau
                if (ImGui::IsWindowFocused())
                {
                    blink += io.DeltaTime;
                    bool cursor_is_visible = (!io.ConfigInputTextCursorBlink) || (blink <= 0.0f) || fmodf(blink, 1.20f) <= 0.80f;
                    if (cursor_is_visible)
                    {
                        ImVec2 Pos((float)lineEnd.mColumn, (float)lineEnd.mColumn);
                        ImRect cursor;
                        drawList->AddLine(cursor.Min, cursor.GetBL(), ImGui::GetColorU32(ImGuiCol_Text));
                    }
                }

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
                    drawList->AddText(newOffset, 4289374890, mLineBuffer.c_str());
                    mLineBuffer.clear();
                }
                lineNo++;
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
            // std::cout << e.getKeyCode() << std::endl;
            std::cout << "KeyPressEvent: " << e.getKeyCode() << std::endl;

            int cline = state.mCursorPosition.mLine;
            int column = mLines.empty() ? 0 : std::min(column, GetLastCol(cline));

            Coord coord(column, cline);

            int i = 0;
            char buf[7];
            auto &line = mLines[coord.mLine];

            switch (e.getKeyCode())
            {
            case 257:
                //Enter
                // InsertLine(coord.mLine + 1);
                i = ImTextCharToUtf8(buf, 7, '\n');
                break;
            case 258:
                //Tab
                i = ImTextCharToUtf8(buf, 7, '\t');
                break;
            case 259:
                //Backspace
                line.pop_back();
                break;
            default:
                break;
            }

            if (i > 0)
            {
                auto index = GetTextIndex(coord);
                buf[i] = '\0';
                for (char *c = buf; *c != '\0'; c++, ++index)
                {
                    line.emplace(line.begin() + index, TextCustom(4289374890, *c));
                }
            }
            return false;
        });

        //Xử lý các chữ cái thông thường kể cả utf-8 (utf-8 khó quá tính sau)
        dispatch.Dispatch<KeyTypedEvent>([&](KeyTypedEvent e) {
            int cline = state.mCursorPosition.mLine;
            int column = mLines.empty() ? 0 : std::min(column, GetLastCol(cline));

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
                    line.emplace(line.begin() + index, TextCustom(4289374890, *c));
                }
            }
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
