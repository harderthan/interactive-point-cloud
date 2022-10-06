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
  main_canvas_ =
      std::make_unique<guik::GLCanvas>(GetShadersDirPath(), framebuffer_size());
  if (!main_canvas_->ready()) {
    close();
  }
  return true;
}

void InteractivePointCloudApplication::draw_ui() {
  Context context = draw_menu_->Draw();

  if (!context.file_menu.point_cloud_file_name.empty()) {
    point_cloud_buffer_ = std::make_unique<glk::PointCloudBuffer>(
        context.file_menu.point_cloud_file_name);
  }

  // TODO(harderthan): check how to move mouse_control to draw_gl().
  if (context.file_menu.is_opened == false) {
    main_canvas_->mouse_control();
  }
}

void InteractivePointCloudApplication::draw_gl() {
  glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
  main_canvas_->bind();

  // Draw coordinate system.
  main_canvas_->shader->set_uniform("color_mode", 2);
  main_canvas_->shader->set_uniform(
      "model_matrix",
      (Eigen::UniformScaling<float>(3.0f) * Eigen::Isometry3f::Identity())
          .matrix());
  const auto &coord = glk::Primitives::instance()->primitive(
      glk::Primitives::COORDINATE_SYSTEM);
  coord.draw(*main_canvas_->shader);

  // Draw grid.
  main_canvas_->shader->set_uniform("color_mode", 1);
  main_canvas_->shader->set_uniform(
      "model_matrix", (Eigen::Translation3f(Eigen::Vector3f::UnitZ() * -0.02) *
                       Eigen::Isometry3f::Identity())
                          .matrix());
  main_canvas_->shader->set_uniform("material_color",
                                    Eigen::Vector4f(0.8f, 0.8f, 0.8f, 1.0f));
  const auto &grid =
      glk::Primitives::instance()->primitive(glk::Primitives::GRID);
  grid.draw(*main_canvas_->shader);

  // Draw point cloud data on canvas.
  if (point_cloud_buffer_) {
    main_canvas_->shader->set_uniform("color_mode", 0);
    main_canvas_->shader->set_uniform("model_matrix",
                                      Eigen::Isometry3f::Identity().matrix());
    point_cloud_buffer_->draw(*main_canvas_->shader);
  }

  // Flush to the screen.
  main_canvas_->unbind();
  main_canvas_->render_to_screen();
  glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

}  // namespace interactive_point_cloud