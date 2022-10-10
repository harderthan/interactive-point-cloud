#include <string>

#include "context.hpp"
#include "imfilebrowser.h"
#include "imgui.h"

namespace ui {

using interactive_point_cloud::Context;

class PointCloudData {
 public:
  PointCloudData(std::shared_ptr<Context> context) : context_(context) {
    // Set the config of file browser.
    file_browser_.SetTitle("file browser");
    file_browser_.SetTypeFilters({".pcd"});
  }

  void Draw() {
    ImGui::Begin("Point Cloud Data Menu", nullptr, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Open..", "Ctrl+O")) { 
          file_browser_.Open();
        }
        if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */
        }
        ImGui::EndMenu();
      }
      ImGui::EndMenuBar();
    }
    ImGui::End();
    file_browser_.Display();
  };

  void Update() {
    if (file_browser_.IsOpened()) {
      context_->file_menu.is_opened = true;
    } else {
      context_->file_menu.is_opened = false;
    }

    if (file_browser_.HasSelected()) {
      context_->file_menu.point_cloud_file_name =
          file_browser_.GetSelected().string();
      file_browser_.ClearSelected();
    }
  }

 private:
  std::shared_ptr<Context> context_;
  ImGui::FileBrowser file_browser_;
};

}  // namespace ui