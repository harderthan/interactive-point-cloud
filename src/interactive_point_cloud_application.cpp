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
  
  // Iinitialize the context
  context_ = std::make_shared<Context>();

  // Initialize UI components.
  app_status_ = std::make_unique<ui::AppStatus>(context_);
  draw_menu_ = std::make_unique<ui::PointCloudDataMenu>(context_);

  // Initialize OpenGL canvas.
  main_canvas_ =
      std::make_shared<guik::GLCanvas>(GetShadersDirPath(), framebuffer_size());
  if (!main_canvas_->ready()) {
    close();
  }
  coordinate_system_ = std::make_unique<gl::CoordinateSystem>(main_canvas_);
  point_cloud_data_ = std::make_unique<gl::PointCloudData>(main_canvas_);

  return true;
}

void InteractivePointCloudApplication::draw_ui() {
  app_status_->Draw();
  app_status_->Update();
  draw_menu_->Draw();
  draw_menu_->Update();

  if (context_->point_cloud_data_menu.is_updated) {
    point_cloud_data_->SetPointCloudBuffer(
        context_->point_cloud_data_menu.file_name);
    context_->point_cloud_data_menu.is_updated = false;
  }

  main_canvas_->mouse_control();
  main_canvas_->keyboard_control();
}

void InteractivePointCloudApplication::draw_gl() {
  glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
  main_canvas_->bind();

  coordinate_system_->Draw();
  point_cloud_data_->Draw();

  // Flush to the screen.
  main_canvas_->unbind();
  main_canvas_->render_to_screen();
  glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

}  // namespace interactive_point_cloud
