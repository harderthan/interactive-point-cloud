#include "interactive_point_cloud_application.hpp"

#include "gl/coordinate_system.hpp"
#include "gl/point_cloud_data.hpp"
#include "gl/road_networks.hpp"
#include "glk/primitives/coordinate_system.hpp"
#include "glk/primitives/grid.hpp"
#include "glk/primitives/primitives.hpp"
#include "shaders.h"
#include "ui/app_status.hpp"
#include "ui/point_cloud_data.hpp"

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
  road_networks_ = std::make_unique<gl::RoadNetworks>(main_canvas_);

  return true;
}

void InteractivePointCloudApplication::draw_ui() {
  app_status_->Draw();
  app_status_->Update();
  draw_menu_->Draw();
  draw_menu_->Update();

  if (context_->point_cloud_data_menu.is_updated) {
    auto ptr = std::make_unique<glk::PointCloudBuffer>(
        context_->point_cloud_data_menu.file_name);
    point_cloud_data_->SetPointCloudBuffer(std::move(ptr));
    main_canvas_->set_view_point(point_cloud_data_->GetCenter());
    context_->point_cloud_data_menu.is_updated = false;
  }

  if (context_->app_status.is_updated) {
    main_canvas_->set_view_point(Eigen::Vector3f(
        context_->app_status.coordinate_x, context_->app_status.coordinate_y,
        context_->app_status.coordinate_z));
    context_->app_status.is_updated = false;
  }

  if (context_->road_networks_menu.is_updated) {
    auto file = context_->road_networks_menu.file_name;
    std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f>>
        vertices;
    vertices.push_back(Eigen::Vector3f::Zero());
    road_networks_->SetRoadNetworks(vertices);
    context_->road_networks_menu.is_updated = false;
  }

  main_canvas_->mouse_control();
  main_canvas_->keyboard_control();
}

void InteractivePointCloudApplication::draw_gl() {
  glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
  main_canvas_->bind();

  coordinate_system_->Draw();
  point_cloud_data_->Draw();
  road_networks_->Draw();

  // Flush to the screen.
  main_canvas_->unbind();
  main_canvas_->render_to_screen();
  glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
}

}  // namespace interactive_point_cloud
