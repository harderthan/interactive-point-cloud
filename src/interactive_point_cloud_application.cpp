#include "interactive_point_cloud_application.hpp"

#include "ui/draw_menu.hpp"

namespace interactive_point_cloud {
bool InteractivePointCloudApplication::init(const char *window_name,
                                            const Eigen::Vector2i &size,
                                            const char *glsl_version) {
  if (!Application::init(window_name, size, glsl_version)) {
    return false;
  }

  return true;
}

void InteractivePointCloudApplication::draw_ui() {
    ui::DrawMenu();
}

void InteractivePointCloudApplication::draw_gl() {}

void InteractivePointCloudApplication::framebuffer_size_callback(
    const Eigen::Vector2i &size) {}

}  // namespace interactive_point_cloud