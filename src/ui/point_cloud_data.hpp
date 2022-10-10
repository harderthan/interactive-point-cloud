#ifndef UI_POINT_CLOUD_DATA_HPP_
#define UI_POINT_CLOUD_DATA_HPP_

#include <string>

#include "draw_ui.hpp"
#include "imfilebrowser.h"

namespace interactive_point_cloud::ui {

using interactive_point_cloud::Context;

class PointCloudDataMenu : public DrawUi {
 public:
  PointCloudDataMenu(std::shared_ptr<Context> context) : DrawUi(context) {
    // Set the config of file browser.
    file_browser_.SetTitle("file browser");
    file_browser_.SetTypeFilters({".pcd"});
  }

  void Draw() {
    ImGui::SetNextWindowSize(ImVec2(400, 200));
    ImGui::SetNextWindowPos(ImVec2(10, 10));
    ImGui::Begin("Point Cloud Data Menu", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Open..", "Ctrl+O")) {
          file_browser_.Open();
        }
        ImGui::EndMenu();
      }
      ImGui::EndMenuBar();
    }
    ImGui::BeginChild("Scrolling");
    ImGui::Text("FILE: %s",
                GetContext().point_cloud_data_menu.file_name.c_str());
    ImGui::EndChild();
    ImGui::End();
  };

  void Update() {
    file_browser_.Display();

    if (file_browser_.IsOpened()) {
      GetContext().point_cloud_data_menu.is_opened = true;
    } else {
      GetContext().point_cloud_data_menu.is_opened = false;
    }

    if (file_browser_.HasSelected()) {
      GetContext().point_cloud_data_menu.file_name =
          file_browser_.GetSelected().string();
      file_browser_.ClearSelected();
      GetContext().point_cloud_data_menu.is_updated = true;
    }
  }

 private:
  ImGui::FileBrowser file_browser_;
};

}  // namespace interactive_point_cloud::ui

#endif  // UI_POINT_CLOUD_DATA_HPP_