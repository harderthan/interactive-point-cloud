#ifndef GL_POINT_CLOUD_DATA_HPP_
#define GL_POINT_CLOUD_DATA_HPP__

#include "glk/pointcloud_buffer.hpp"

#include "draw_canvas.hpp"

namespace interactive_point_cloud::gl {
class PointCloudData : public DrawCanvas {
 public:
  PointCloudData(std::shared_ptr<guik::GLCanvas> main_canvas)
      : DrawCanvas(main_canvas) {}

  void Draw() {
    if (point_cloud_buffer_) {
      GetMainCanvas().shader->set_uniform("color_mode", 0);
      GetMainCanvas().shader->set_uniform(
          "model_matrix", Eigen::Isometry3f::Identity().matrix());
      point_cloud_buffer_->draw(*(GetMainCanvas().shader));
    }
  }

  void SetPointCloudBuffer(const std::string& file_name) {
    point_cloud_buffer_ = std::make_unique<glk::PointCloudBuffer>(file_name);
  }

 private:
  std::unique_ptr<glk::PointCloudBuffer> point_cloud_buffer_;
};

}  // namespace interactive_point_cloud::gl

#endif  // GL_POINT_CLOUD_DATA_HPP__