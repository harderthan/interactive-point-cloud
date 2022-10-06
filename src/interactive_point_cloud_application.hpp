#ifndef INTERACTIVE_POINT_CLOUD_APPLICATION_HPP
#define INTERACTIVE_POINT_CLOUD_APPLICATION_HPP
#include <memory>
#include <string_view>

#include "glk/pointcloud_buffer.hpp"
#include "guik/gl_canvas.hpp"
#include "guik/imgui_application.hpp"
#include "imgui.h"
#include "ui/draw_menu.hpp"

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

  explicit InteractivePointCloudApplication() : Application() {}

  // Override functions from guik::Application
  bool init(const char *window_name, const Eigen::Vector2i &size,
            const char *glsl_version = "#version 330") override;
  virtual void draw_ui() override;
  virtual void draw_gl() override;

 private:
  Context context_;

  // UI
  std::unique_ptr<ui::DrawMenu> draw_menu_;

  // Gl
  std::unique_ptr<guik::GLCanvas> main_canvas_;

  std::unique_ptr<glk::PointCloudBuffer> point_cloud_buffer_;
};

}  // namespace interactive_point_cloud

#endif  // INTERACTIVE_POINT_CLOUD_APPLICATION_HPP