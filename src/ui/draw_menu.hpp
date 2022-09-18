#include "imgui.h"

namespace ui {
void DrawMenu() {
  ImGui::BeginMainMenuBar();
  if (ImGui::BeginMenu("File")) {
    if (ImGui::BeginMenu("Open")) {
      ImGui::EndMenu();
    }
    ImGui::EndMenu();
  }
  ImGui::EndMainMenuBar();
}
}  // namespace ui