#include "imgui.h"
#include "imfilebrowser.h"

namespace ui {

class DrawMenu {
 public:
  DrawMenu() {
    // Set the config of file browser.
    file_browser_.SetTitle("file browser");
    file_browser_.SetTypeFilters({".pcd"});
  }

  void Draw() {
    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Open")) {
          file_browser_.Open();
        }
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }

    file_browser_.Display();
    if (file_browser_.HasSelected()) {
      std::cout << "Selected: " << file_browser_.GetSelected().string() << std::endl;
      file_browser_.ClearSelected();
    }
  }

 private:
  ImGui::FileBrowser file_browser_;
};

}  // namespace ui