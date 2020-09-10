# TextEditor

Api: OpenGl, glfw, glm, Dear ImGui
Ngôn ngữ: C++

- Cần làm: 
  + Hiển thị được chữ số lên editor (hoàn thành)
  + Hiển thị được utf-8 (sẽ giải quyết sau)
  + Vẽ được blink cursor
  + Chức năng undo

- Có thể làm:
  + Một cửa sổ File chooser
    + Save file
    + Open file

* Hiển thị được chữ số lên editor:
  - Cách thức nhập text: Nhận các ký tự từ bàn phím, đưa vào vector line rồi chuyển qua string buffer để hiển thị lên màn hình. Các nút đặc biệt (tab, enter, ...) sẽ lấy từ keycode của glfw
