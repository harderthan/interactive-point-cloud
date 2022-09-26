#include <string>

#include "imgui.h"
#include "imfilebrowser.h"

#include "context.hpp"

namespace ui {

class DrawMenu {
 public:
  DrawMenu() {
    // Set the config of file browser.
    file_browser_.SetTitle("file browser");
    file_browser_.SetTypeFilters({".pcd"});
  }

  void Draw(interactive_point_cloud::Context &context) {
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
      context.SetPointCloudFileName(file_browser_.GetSelected().string());
      file_browser_.ClearSelected();
    }
  }

  std::string GetSelectedFile() const { return file_browser_.GetSelected().string(); }

 private:
  ImGui::FileBrowser file_browser_;
};

}  // namespace ui