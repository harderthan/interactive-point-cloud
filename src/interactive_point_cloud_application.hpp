#ifndef INTERACTIVE_POINT_CLOUD_APPLICATION_HPP
#define INTERACTIVE_POINT_CLOUD_APPLICATION_HPP
#include <memory>
#include <string_view>

#include "glk/pointcloud_buffer.hpp"
#include "guik/imgui_application.hpp"
#include "imgui.h"

#include "gl/coordinate_system.hpp"
#include "gl/point_cloud_data.hpp"
#include "gl/road_networks.hpp"

#include "ui/app_status.hpp"
#include "ui/point_cloud_data.hpp"

namespace interactive_point_cloud {

class InteractivePointCloudApplication : public guik::Application {
 public:
  InteractivePointCloudApplication(const InteractivePointCloudApplication &) =
      delete;
  InteractivePointCloudApplication &operator=(
      const InteractivePointCloudApplication &) = delete;
  InteractivePointCloudApplication(InteractivePointCloudApplication &&) =
      delete;
  InteractivePointCloudApplication &operator=(
      InteractivePointCloudApplication &&) = delete;

  explicit InteractivePointCloudApplication()
      : Application() {}

  // Override functions from guik::Application
  bool init(const char *window_name, const Eigen::Vector2i &size,
            const char *glsl_version = "#version 330") override;
  virtual void draw_ui() override;
  virtual void draw_gl() override;

 private:
  std::shared_ptr<Context> context_;
  std::unique_ptr<glk::PointCloudBuffer> point_cloud_buffer_;

  // UI
  std::unique_ptr<ui::AppStatus> app_status_;
  std::unique_ptr<ui::PointCloudDataMenu> draw_menu_;

  // Gl
  std::shared_ptr<guik::GLCanvas> main_canvas_;
  std::unique_ptr<gl::CoordinateSystem> coordinate_system_;
  std::unique_ptr<gl::PointCloudData> point_cloud_data_;
  std::unique_ptr<gl::RoadNetworks> road_networks_;
};

}  // namespace interactive_point_cloud

#endif  // INTERACTIVE_POINT_CLOUD_APPLICATION_HPP