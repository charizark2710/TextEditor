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
        // float y = cursorY > lastLine ? lastLine : cursorY;
        float y = cursorY;
        float currentLine = (lastLine - y) / charAdvance.y;
        float maxLine = (lastLine - firstLine) / charAdvance.y;
        float result = maxLine - currentLine;
        float temp = std::floor(result) - result;
        if (temp < 0.55)
        {
            result = std::floor(result);
        }
        else
        {
            result = std::ceil(result);
        }
        return result;
    }

    //Lấy số cột mà con trỏ đang chỉ tới
    int CustomTextEditor::CalculateCurrentIndex(int line)
    {
        Line lineContent = mLines[line];
        float lineStart = cursorScreenPos.x;
        float lineEnd = cursorScreenPos.x + (charAdvance.x * lineContent.size());
        // float x = cursorX > lineEnd ? lineEnd : cursorX;
        float x = cursorX;
        float leftIndex = (lineEnd - x) / charAdvance.x;
        float rightIndex = (lineEnd - lineStart) / charAdvance.x;
        float result = std::round(rightIndex - leftIndex);
        return result;
    }

    //Lụm số dòng và số cột khi có click chuột
    CustomTextEditor::Coord CustomTextEditor::GetCurrentCursor()
    {
        Coord coord;

        int Y = CalculateCurrentLine();

        if (Y > mLines.size() - 1)
            Y = mLines.size() - 1;

        int X = CalculateCurrentIndex(Y);

        if (X > mLines[Y].size())
            X = mLines[Y].size();

        coord = {X, Y};
        return coord;
    }

    void CustomTextEditor::setSelection()
    {
        //end
        int line = CalculateCurrentLine();

        if (line > mLines.size() - 1)
        {
            hasSelection = false;
            return;
        }

        int column = CalculateCurrentIndex(line);

        if (column > mLines[line].size())
        {
            hasSelection = false;
            return;
        }

        state.mSelectionEnd = {column, line};
        hasSelection = true;
    }

    void CustomTextEditor::DeleteChar(CustomTextEditor::Line &line, int index)
    {
        if (hasSelection)
        {
            int lineEnd = state.mSelectionEnd.mLine;
            int lineStart = state.mSelectionStart.mLine;
            int cStart = state.mSelectionStart.mColumn;
            int cEnd = state.mSelectionEnd.mColumn;
            if (lineStart != lineEnd)
            {
                if (lineEnd < lineStart)
                {
                    std::swap(cStart, cEnd);
                    std::swap(lineEnd, lineStart);
                }
                line.erase(line.begin() + cStart, line.end());
                mLines[lineEnd].erase(mLines[lineEnd].begin(), mLines[lineEnd].begin() + cEnd);
                mLines.erase(mLines.begin() + lineStart + 1, mLines.begin() + lineEnd);
            }
            else
            {
                if (cStart > cEnd)
                {
                    std::swap(cStart, cEnd);
                }
                line.erase(line.begin() + cStart, line.begin() + cEnd);
            }
        }
        else
        {
            line.erase(line.begin() + index - 1);
        }
    }

    CustomTextEditor::Line &CustomTextEditor::InsertLine(int line)
    {
        auto &result = *mLines.emplace(mLines.begin() + line, Line());
        return result;
    }

    void CustomTextEditor::InsertTab(int column)
    {
        mLines[state.mCursorPosition.mLine].emplace(mLines[state.mCursorPosition.mLine].begin() + column, ImGui::GetColorU32(ImGuiCol_Text), ' ');
        mLines[state.mCursorPosition.mLine].emplace(mLines[state.mCursorPosition.mLine].begin() + column + 1, ImGui::GetColorU32(ImGuiCol_Text), ' ');
        mLines[state.mCursorPosition.mLine].emplace(mLines[state.mCursorPosition.mLine].begin() + column + 2, ImGui::GetColorU32(ImGuiCol_Text), ' ');
        mLines[state.mCursorPosition.mLine].emplace(mLines[state.mCursorPosition.mLine].begin() + column + 3, ImGui::GetColorU32(ImGuiCol_Text), ' ');
    }

    void CustomTextEditor::Copy()
    {
        clipboardString.clear();
        int startLine = state.mSelectionStart.mLine;
        int endLine = state.mSelectionEnd.mLine;
        int startCol = state.mSelectionStart.mColumn;
        int endCol = state.mSelectionEnd.mColumn;
        if (startLine > endLine)
        {
            std::swap(startLine, endLine);
            std::swap(startCol, endCol);
        }
        for (int line = startLine; line <= endLine; line++)
        {
            if (line == startLine && line == endLine)
            {
                for (int column = startCol; column < endCol; column++)
                {
                    clipboardString.push_back(mLines[line][column].mtext);
                }
            }
            else if (line == startLine)
            {
                for (int column = startCol; column < mLines[line].size(); column++)
                {
                    clipboardString.push_back(mLines[line][column].mtext);
                }
            }
            else if (line == endLine)
            {
                for (int column = 0; column < endCol; column++)
                {
                    clipboardString.push_back(mLines[line][column].mtext);
                }
            }
            else
            {
                for (int column = 0; column < mLines[line].size(); column++)
                {
                    clipboardString.push_back(mLines[line][column].mtext);
                }
            }
            clipboardString.push_back('\n');
        }
        glfwSetClipboardString(m_window->GetNativeWindow(), clipboardString.c_str());
    }

    void CustomTextEditor::Paste()
    {
        std::string text = glfwGetClipboardString(m_window->GetNativeWindow());
        const char *c = text.c_str();
        if (!text.empty())
        {
            while (*c != '\0')
            {
                if (*c == '\n')
                {
                    InsertLine(state.mCursorPosition.mLine + 1);
                    state.mCursorPosition.mLine++;
                    state.mCursorPosition.mColumn = 0;
                }
                else if (*c == '\r')
                {
                    state.mCursorPosition.mColumn = 0;
                }
                else if (*c == '\t')
                {
                    InsertTab(state.mCursorPosition.mColumn);
                    state.mCursorPosition.mColumn += 4;
                }
                else
                {
                    auto line = &mLines[state.mCursorPosition.mLine];
                    auto index = GetTextIndex(state.mCursorPosition);
                    line->emplace(line->begin() + index, ImGui::GetColorU32(ImGuiCol_Text), *c);
                    state.mCursorPosition.mColumn++;
                }
                c++;
            }
        }
    }

    void CustomTextEditor::OnRender(GLFWwindow *window)
    {
        ImGui::Begin((this->GetName()).c_str());
        ImGui::BeginChild("XXX");
        cursorScreenPos = ImGui::GetCursorScreenPos();
        int diffSize = textSize - (cursorScreenPos.x - cursorScreenPos.y);
        cursorScreenPos.y = cursorScreenPos.y + diffSize;
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigWindowsMoveFromTitleBarOnly = true;
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
    }

    void CustomTextEditor::SetUp()
    {
        ImGuiIO &io = ImGui::GetIO();
        const float fontSize = ImGui::GetFont()->CalcTextSizeA(textSize, FLT_MAX, -1.0f, "#", nullptr, nullptr).x;
        charAdvance = ImVec2(fontSize, (textSize + ImGui::GetCurrentContext()->Style.ItemSpacing.y) * 1.0f);
        auto contentSize = ImGui::GetWindowContentRegionMax();
        auto drawList = ImGui::GetWindowDrawList();
        auto scrollX = ImGui::GetScrollX();
        auto scrollY = ImGui::GetScrollY();
        auto lineNo = (int)std::floor(scrollY / charAdvance.y);
        auto globalLineMax = (int)mLines.size();
        auto lineMax = std::max(0, std::min((int)mLines.size() - 1, lineNo + (int)floor((scrollY + contentSize.y) / charAdvance.y)));
        ImVec2 cursor_offset;
        ImVec2 textScreenPos;
        Coord currentCur = state.mCursorPosition;
        int startLine = state.mSelectionStart.mLine;
        int endLine = state.mSelectionEnd.mLine;
        if (!mLines.empty())
        {
            float spaceSize = ImGui::GetFont()->CalcTextSizeA(textSize, FLT_MAX, -1.0f, " ", nullptr, nullptr).x;
            while (lineNo <= lineMax)
            {
                ImVec2 lineStartScreenPos = ImVec2(cursorScreenPos.x, cursorScreenPos.y + lineNo * charAdvance.y);
                textScreenPos = ImVec2(lineStartScreenPos.x, lineStartScreenPos.y);
                auto &line = mLines[lineNo];
                int columnNo = 0;
                Coord lineStart(0, lineNo);
                Coord lineEnd(line.size(), lineNo);
                const ImVec2 draw_scroll = ImVec2(scrollX, 0.0f);

                //draw selection
                if (hasSelection && ((lineNo >= startLine && lineNo <= endLine) || (lineNo <= startLine && lineNo >= endLine)))
                {
                    int startColumn = state.mSelectionStart.mColumn;
                    int endColumn = state.mSelectionEnd.mColumn;

                    if (startColumn > endColumn)
                    {
                        std::swap(startColumn, endColumn);
                    }

                    ImVec2 vstart;
                    ImVec2 vend;
                    // Phương pháp là vẽ từng dòng khi chạy vòng while theo dòng bắt đầu và kết thúc
                    // Đoạn này để xác định nên bôi chỗ nào khi con trỏ kéo khỏi dòng ban đầu
                    if (endLine != startLine && lineNo == startLine)
                    {
                        if (endLine < startLine)
                        {
                            startColumn = 0;
                            endColumn = state.mSelectionStart.mColumn;
                        }
                        else
                        {
                            startColumn = state.mSelectionStart.mColumn;
                            endColumn = mLines[lineNo].size();
                        }
                    }
                    // bôi đen toàn bộ những dòng trong khoảng từ dòng đầu đến dòng cuối
                    else if (lineNo != endLine)
                    {
                        startColumn = 0;
                        endColumn = mLines[lineNo].size();
                    }
                    // Xác định nên bôi thế nào tại dòng hiện tại (dòng cuối)
                    else if (lineNo < startLine)
                    {
                        startColumn = state.mCursorPosition.mColumn;
                        endColumn = mLines[lineNo].size();
                    }
                    else if (lineNo > startLine)
                    {
                        startColumn = 0;
                        endColumn = state.mCursorPosition.mColumn;
                    }

                    if (endColumn > mLines[lineNo].size())
                    {
                        endColumn = mLines[lineNo].size();
                    }
                    vstart = ImVec2(CursorPos.x + (startColumn * spaceSize), cursorScreenPos.y + lineNo * charAdvance.y);
                    vend = ImVec2(CursorPos.x + (endColumn * spaceSize), vstart.y + charAdvance.y);
                    drawList->AddRectFilled(vstart, vend, ImGui::GetColorU32(ImGuiCol_TextSelectedBg));

                    state.mCursorPosition = state.mSelectionEnd;
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
                    auto font = ImGui::GetCurrentContext()->Font;
                    drawList->AddText(font, textSize, newOffset, ImGui::GetColorU32(ImGuiCol_Text), mLineBuffer.c_str());
                    mLineBuffer.clear();
                }
                lineNo++;
            }
            CursorPos = textScreenPos;
            // draw cursor
            if (ImGui::IsWindowFocused())
            {
                blink += io.DeltaTime;
                bool cursor_is_visible = (!io.ConfigInputTextCursorBlink) || (blink <= 0.0f) || fmodf(blink, 1.20f) <= 0.80f;
                if (cursor_is_visible)
                {
                    ImVec2 cstart(CursorPos.x + (currentCur.mColumn * spaceSize), cursorScreenPos.y + currentCur.mLine * charAdvance.y);
                    cursor = cstart;
                    ImVec2 cend(cstart.x, cstart.y + textSize);
                    ImRect rectCursor(cstart, cend);
                    drawList->AddLine(rectCursor.Min, rectCursor.Max, ImGui::GetColorU32(ImGuiCol_Text));
                }
            }
        }
    }

    void CustomTextEditor::OnEvent(Event &event)
    {
        //Xử lý đầu vào đặc biệt
        EventDispatcher dispatch(event);
        dispatch.Dispatch<KeyPressEvent>([&](KeyPressEvent e) {
            int cline = state.mCursorPosition.mLine;
            int column = mLines.empty() ? 0 : state.mCursorPosition.mColumn;

            Coord coord(column, cline);

            auto line = &mLines[coord.mLine];

            const auto temp = *line;

            if (e.getKeyCode() == GLFW_KEY_LEFT_CONTROL || e.getKeyCode() == GLFW_KEY_RIGHT_CONTROL)
            {
                isCtrl = true;
            }

            switch (e.getKeyCode())
            {
            case GLFW_KEY_ENTER:
            {
                //Enter
                Line &newLine = InsertLine(coord.mLine + 1);
                if (!line->empty())
                {
                    newLine.insert(newLine.begin(), temp.begin() + column, temp.end());
                    mLines[coord.mLine].erase(mLines[coord.mLine].begin() + column, mLines[coord.mLine].end());
                }
                state.mCursorPosition.mColumn = 0;
                state.mCursorPosition.mLine++;
                break;
            }
            case GLFW_KEY_TAB:
            {
                //Tab
                InsertTab(coord.mColumn);
                state.mCursorPosition.mColumn += 4;
                break;
            }
            case GLFW_KEY_BACKSPACE:
            {
                //Backspace
                if (cline > 0 && column == 0)
                {
                    state.mCursorPosition.mColumn = mLines[--state.mCursorPosition.mLine].size();

                    if (!line->empty() && cline > 0)
                    {
                        mLines[cline - 1].insert(mLines[cline - 1].end(), line->begin(), line->end());
                    }
                    mLines.erase(mLines.begin() + cline);
                }

                else if (line != nullptr && !line->empty() && column > 0)
                {
                    DeleteChar(*line, column);
                    hasSelection == false ? state.mCursorPosition.mColumn-- : state.mCursorPosition.mColumn;
                    hasSelection = false;
                }
                break;
            }
            case GLFW_KEY_DELETE:
            {
                //delete
                if (line != nullptr && !line->empty())
                {
                    if (temp[column].mtext)
                    {
                        DeleteChar(*line, column + 1);
                        hasSelection = false;
                    }
                }

                if (mLines.size() - 1 > cline && !temp[column].mtext)
                {
                    mLines[cline].insert(mLines[cline].end(), mLines[cline + 1].begin(), mLines[cline + 1].end());
                    mLines.erase(mLines.begin() + cline + 1);
                }
                break;
            }
            case GLFW_KEY_C:
            {
                if (isCtrl)
                {
                    if (hasSelection)
                    {
                        Copy();
                    }
                }
                break;
            }
            case GLFW_KEY_V:
            {
                if (isCtrl)
                {
                    Paste();
                }
                break;
            }
            case GLFW_KEY_LEFT:
            {
                if (column > 0)
                {
                    state.mCursorPosition.mColumn--;
                }
                else
                {
                    if (cline - 1 >= 0)
                        state.mCursorPosition.mColumn = mLines[--state.mCursorPosition.mLine].size();
                }
                break;
            }
            case GLFW_KEY_RIGHT:
            {
                if (column < line->size())
                {
                    state.mCursorPosition.mColumn++;
                }
                else
                {
                    if (cline + 1 <= mLines.size() - 1)
                    {
                        state.mCursorPosition.mColumn = 0;
                        state.mCursorPosition.mLine++;
                    }
                }
            }
            case GLFW_KEY_DOWN:
            {
                break;
            }
            case GLFW_KEY_UP:
            {
                break;
            }
            default:
                break;
            }
            return false;
        });

        dispatch.Dispatch<KeyReleasedEvent>([&](KeyReleasedEvent e) {
            if (e.getKeyCode() == GLFW_KEY_LEFT_CONTROL || e.getKeyCode() == GLFW_KEY_RIGHT_CONTROL)
            {
                isCtrl = false;
            }
            else if (e.getKeyCode() == GLFW_KEY_LEFT_SHIFT || e.getKeyCode() == GLFW_KEY_RIGHT_SHIFT)
            {
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
                    line.emplace(line.begin() + index, ImGui::GetColorU32(ImGuiCol_Text), *c);
                    if (*c == '(' || *c == '{' || *c == '[')
                    {
                        if (*c == '(')
                        {
                            line.emplace(line.begin() + index + 1, line[index - 1].mcolor, ')');
                        }
                        else
                        {
                            int temp = (int)*c;
                            line.emplace(line.begin() + index + 1, line[index - 1].mcolor, (char)(temp + 2));
                        }
                    }
                }
                state.mCursorPosition.mColumn++;
            }
            return false;
        });

        //Nhấn chuột trái
        dispatch.Dispatch<MouseButtonPressedEvent>([&](MouseButtonPressedEvent e) {
            if (e.GetMouseButton() == GLFW_MOUSE_BUTTON_LEFT)
            {
                hasSelection = false;
                SetCursorPosition(state.mCursorPosition);
                isClicked = true;
                state.mSelectionStart.mColumn = state.mCursorPosition.mColumn;
                state.mSelectionStart.mLine = state.mCursorPosition.mLine;

                //double click
                static auto before = std::chrono::system_clock::now();
                auto now = std::chrono::system_clock::now();
                double diff_ms = std::chrono::duration<double, std::milli>(now - before).count();
                before = now;
                if (diff_ms > 10 && diff_ms < 200)
                {
                    std::cout << diff_ms << std::endl;
                }
            }
            return false;
        });

        //Thả chuột
        dispatch.Dispatch<MouseButtonReleasedEvent>([&](MouseButtonReleasedEvent e) {
            isClicked = false;
            return false;
        });

        //Di Chuột
        dispatch.Dispatch<MouseMovedEvent>([&](MouseMovedEvent e) {
            if (isClicked)
            {
                setSelection();
            }
            return false;
        });
    }

    void CustomTextEditor::OnUpdate()
    {
    }

    void CustomTextEditor::OnAttatch()
    {
        m_window = &Window::Get();
        mLines.push_back(Line());
    }

    void CustomTextEditor::OnDetatch()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

} // namespace App