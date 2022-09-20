#include "interactive_point_cloud_application.hpp"

#include "glk/primitives/coordinate_system.hpp"
#include "glk/primitives/grid.hpp"
#include "glk/primitives/primitives.hpp"
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
  main_canvas =
      std::make_unique<guik::GLCanvas>(GetShadersDirPath(), framebuffer_size());
  if (!main_canvas->ready()) {
    close();
  }
  return true;
}

void InteractivePointCloudApplication::draw_ui() {
  draw_menu_->Draw();

  // TODO(harderthan): check how to move mouse_control to draw_gl().
  main_canvas->mouse_control();  // mouse_control() should be called on draw_ui().
}

void InteractivePointCloudApplication::draw_gl() {
  glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
  main_canvas->bind();

  // draw coordinate system
  main_canvas->shader->set_uniform("color_mode", 2);
  main_canvas->shader->set_uniform(
      "model_matrix",
      (Eigen::UniformScaling<float>(3.0f) * Eigen::Isometry3f::Identity())
          .matrix());
  const auto &coord = glk::Primitives::instance()->primitive(
      glk::Primitives::COORDINATE_SYSTEM);
  coord.draw(*main_canvas->shader);

  // draw grid
  main_canvas->shader->set_uniform("color_mode", 1);
  main_canvas->shader->set_uniform(
      "model_matrix", (Eigen::Translation3f(Eigen::Vector3f::UnitZ() * -0.02) *
                       Eigen::Isometry3f::Identity())
                          .matrix());
  main_canvas->shader->set_uniform("material_color",
                                   Eigen::Vector4f(0.8f, 0.8f, 0.8f, 1.0f));
  const auto &grid =
      glk::Primitives::instance()->primitive(glk::Primitives::GRID);
  grid.draw(*main_canvas->shader);

  // flush to the screen
  main_canvas->unbind();
  main_canvas->render_to_screen();
  glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

void InteractivePointCloudApplication::framebuffer_size_callback(
    const Eigen::Vector2i &size) {}

}  // namespace interactive_point_cloud