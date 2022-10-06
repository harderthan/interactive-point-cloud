#include <string>

#include "context.hpp"
#include "imfilebrowser.h"
#include "imgui.h"

namespace ui {

using interactive_point_cloud::Context;

class DrawMenu {
 public:
  DrawMenu() {
    // Set the config of file browser.
    file_browser_.SetTitle("file browser");
    file_browser_.SetTypeFilters({".pcd"});
  }

  Context Draw() {
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
      Context context{file_browser_.GetSelected().string()};
      file_browser_.ClearSelected();
      return context;
    }

    return Context{""};
  };

 private:
  ImGui::FileBrowser file_browser_;
};

}  // namespace ui