#include "interactive_point_cloud_application.hpp"

#include <cstdlib>

#include "shaders.h"

namespace interactive_point_cloud {


bool InteractivePointCloudApplication::init(const char *window_name,
                                            const Eigen::Vector2i &size,
                                            const char *glsl_version) {
  if (!Application::init(window_name, size, glsl_version)) {
    return false;
  }

  // Initialize UI components.
  draw_menu_ = std::make_unique<ui::DrawMenu>();

  // Initialize OpenGL canvas.
  
  std::string data_directory = std::filesystem::current_path();;
  main_canvas =
      std::make_unique<guik::GLCanvas>(GetShadersDirPath(), framebuffer_size());

  return true;
}

void InteractivePointCloudApplication::draw_ui() { draw_menu_->Draw(); }

void InteractivePointCloudApplication::draw_gl() {
  glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

void InteractivePointCloudApplication::framebuffer_size_callback(
    const Eigen::Vector2i &size) {}

}  // namespace interactive_point_cloud