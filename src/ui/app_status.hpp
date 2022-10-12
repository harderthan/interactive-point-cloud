#ifndef UI_APP_STATUS_HPP_
#define UI_APP_STATUS_HPP_

#include "draw_ui.hpp"

namespace interactive_point_cloud::ui {

using interactive_point_cloud::Context;

class AppStatus : public DrawUi {
 public:
  AppStatus(std::shared_ptr<Context> context)
      : DrawUi(context),
        view_point_x_(256, '\0'),
        view_point_y_(256, '\0'),
        view_point_z_(256, '\0') {}

  void Draw() {
    ImGui::SetNextWindowSize(ImVec2(400, 200));
    ImGui::SetNextWindowPos(ImVec2(10, 10));
    ImGui::Begin("Status", nullptr, ImGuiWindowFlags_NoMove);
    ImGui::InputTextWithHint(
        "view_point_x",
        std::to_string(GetContext().app_status.coordinate_x).c_str(),
        view_point_x_.data(), 256);
    ImGui::InputTextWithHint(
        "view_point_y",
        std::to_string(GetContext().app_status.coordinate_y).c_str(),
        view_point_y_.data(), 256);
    ImGui::InputTextWithHint(
        "view_point_z",
        std::to_string(GetContext().app_status.coordinate_z).c_str(),
        view_point_z_.data(), 256);
    ImGui::End();
  };

  void Update() {
    if (!ImGui::IsItemActive() && ImGui::IsKeyPressed(ImGuiKey_Enter)) {
      PullOutNumber(view_point_x_, GetContext().app_status.coordinate_x);
      PullOutNumber(view_point_y_, GetContext().app_status.coordinate_y);
      PullOutNumber(view_point_z_, GetContext().app_status.coordinate_z);
    }
  }

 private:
  bool IsNothing(const std::string& str) {
    for (const auto& c : str) {
      if (c != '\0') {
        return false;
      }
    }
    return true;
  }
  bool IsNumber(const std::string& str) {
    for (const auto& c : str) {
      if (!isdigit(c) && c != '\0' && c != '.') {
        return false;
      }
    }
    return true;
  }
  void PullOutNumber(std::string& source, double& target) {
    if (IsNumber(source) && !IsNothing(source)) {
      target = std::stod(source);
    }
    source = std::string(256, '\0');
  }
  std::string view_point_x_;
  std::string view_point_y_;
  std::string view_point_z_;
};

}  // namespace interactive_point_cloud::ui

#endif  // UI_APP_STATUS_HPP_