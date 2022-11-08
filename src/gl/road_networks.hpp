#ifndef GL_OPEN_STREET_MAP_HPP_
#define GL_OPEN_STREET_MAP_HPP_

#include <memory>

#include "draw_canvas.hpp"
#include "glk/lines.hpp"

namespace interactive_point_cloud::gl {
class RoadNetworks : public DrawCanvas {
 public:
  RoadNetworks(std::shared_ptr<guik::GLCanvas> main_canvas)
      : DrawCanvas(main_canvas) {}

  void Draw() {
    if (lines_buffer_ != nullptr) {
      GetMainCanvas().shader->set_uniform("color_mode", 0);
      GetMainCanvas().shader->set_uniform(
          "model_matrix", Eigen::Isometry3f::Identity().matrix());
      lines_buffer_->draw(*(GetMainCanvas().shader));
    }
  }

  void SetRoadNetworks(
      const std::vector<Eigen::Vector3f,
                        Eigen::aligned_allocator<Eigen::Vector3f>>& vertice) {
    lines_buffer_.reset();
    lines_buffer_ = std::make_unique<glk::Lines>(0.01f, vertice);
  }

  Eigen::Vector3f GetCenter() const { return Eigen::Vector3f::Zero(); }

 private:
  std::unique_ptr<glk::Lines> lines_buffer_;
};

}  // namespace interactive_point_cloud::gl

#endif  // GL_OPEN_STREET_MAP_HPP_