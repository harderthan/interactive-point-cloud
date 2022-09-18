#ifndef INTERACTIVE_POINT_CLOUD_APPLICATION_HPP
#define INTERACTIVE_POINT_CLOUD_APPLICATION_HPP
#include <memory>
#include <string_view>

#include "glk/lines.hpp"
#include "guik/camera_control.hpp"
#include "guik/gl_canvas.hpp"
#include "guik/imgui_application.hpp"
#include "guik/progress_modal.hpp"
#include "imgui.h"

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
  virtual void framebuffer_size_callback(const Eigen::Vector2i &size) override;

 private:
  // placeholder
};

}  // namespace interactive_point_cloud

#endif  // INTERACTIVE_POINT_CLOUD_APPLICATION_HPP