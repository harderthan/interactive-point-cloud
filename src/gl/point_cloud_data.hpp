#ifndef GL_POINT_CLOUD_DATA_HPP_
#define GL_POINT_CLOUD_DATA_HPP_

#include "glk/pointcloud_buffer.hpp"

#include "draw_canvas.hpp"

namespace interactive_point_cloud::gl {
class PointCloudData : public DrawCanvas {
 public:
  PointCloudData(std::shared_ptr<guik::GLCanvas> main_canvas)
      : DrawCanvas(main_canvas) {}

  void Draw() {
    if (point_cloud_buffer_ != nullptr) {
      GetMainCanvas().shader->set_uniform("color_mode", 0);
      GetMainCanvas().shader->set_uniform(
          "model_matrix", Eigen::Isometry3f::Identity().matrix());
      point_cloud_buffer_->draw(*(GetMainCanvas().shader));
    }
  }

  void SetPointCloudBuffer(std::unique_ptr<glk::PointCloudBuffer> point_cloud) {
    point_cloud_buffer_ = std::move(point_cloud);
  }

  Eigen::Vector3f GetCenter() const {
    if (point_cloud_buffer_ != nullptr) {
      return point_cloud_buffer_->GetCenter();
    }
    return Eigen::Vector3f::Zero();
  }

 private:
  std::unique_ptr<glk::PointCloudBuffer> point_cloud_buffer_;
};

}  // namespace interactive_point_cloud::gl

#endif  // GL_POINT_CLOUD_DATA_HPP_