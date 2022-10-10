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
  draw_menu_ = std::make_unique<ui::PointCloudDataMenu>(context_);

  // Initialize OpenGL canvas.
  main_canvas_ =
      std::make_shared<guik::GLCanvas>(GetShadersDirPath(), framebuffer_size());
  if (!main_canvas_->ready()) {
    close();
  }

  coordinate_system_ = std::make_unique<gl::CoordinateSystem>(main_canvas_);
  return true;
}

void InteractivePointCloudApplication::draw_ui() {
  draw_menu_->Draw();
  draw_menu_->Update();

  if (context_->point_cloud_data_menu.is_updated) {
    point_cloud_buffer_ = std::make_unique<glk::PointCloudBuffer>(
        context_->point_cloud_data_menu.file_name);
    context_->point_cloud_data_menu.is_updated = false;
  }

  // TODO(harderthan): check how to move mouse_control to draw_gl().
  if (context_->point_cloud_data_menu.is_opened == false) {
    main_canvas_->mouse_control();
  }
}

void InteractivePointCloudApplication::draw_gl() {
  glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
  main_canvas_->bind();

  coordinate_system_->Draw();

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