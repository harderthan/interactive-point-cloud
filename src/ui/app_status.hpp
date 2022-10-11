#ifndef UI_APP_STATUS_HPP_
#define UI_APP_STATUS_HPP_

#include "draw_ui.hpp"

namespace interactive_point_cloud::ui {

using interactive_point_cloud::Context;

class AppStatus : public DrawUi {
 public:
  AppStatus(std::shared_ptr<Context> context) : DrawUi(context) {}

  void Draw() {
    ImGui::SetNextWindowSize(ImVec2(400, 200));
    ImGui::SetNextWindowPos(ImVec2(10, 10));
    ImGui::Begin("Status", nullptr, ImGuiWindowFlags_NoMove);
    ImGui::InputTextWithHint("view_point_x", "view point x", view_point_x_buf_,
                             256, 0, nullptr, nullptr);
    ImGui::InputTextWithHint("view_point_y", "view point y", view_point_y_buf_,
                             256, 0, nullptr, nullptr);
    ImGui::InputTextWithHint("view_point_z", "view point z", view_point_z_buf_,
                             256, 0, nullptr, nullptr);
    ImGui::End();
  };

  void Update() {
    if (!ImGui::IsItemActive() && ImGui::IsKeyPressed(ImGuiKey_Enter)) {
      std::cout << "x: " << view_point_x_buf_ << ", " << view_point_y_buf_
                << ", " << view_point_z_buf_ << std::endl;
    }
  }

 private:
  char view_point_x_buf_[256] = "0";
  char view_point_y_buf_[256] = "0";
  char view_point_z_buf_[256] = "0";
};

}  // namespace interactive_point_cloud::ui

#endif  // UI_APP_STATUS_HPP_