#ifndef GL_COORDINATE_SYSTEM_HPP_
#define GL_COORDINATE_SYSTEM_HPP_

#include "draw_canvas.hpp"

namespace interactive_point_cloud::gl {
class CoordinateSystem : public DrawCanvas {
 public:
  CoordinateSystem(std::shared_ptr<guik::GLCanvas> main_canvas)
      : DrawCanvas(main_canvas) {}

  void Draw() {
    // Draw coordinate system.
    GetMainCanvas().shader->set_uniform("color_mode", 2);
    GetMainCanvas().shader->set_uniform(
        "model_matrix",
        (Eigen::UniformScaling<float>(3.0f) * Eigen::Isometry3f::Identity())
            .matrix());
    const auto &coord = glk::Primitives::instance()->primitive(
        glk::Primitives::COORDINATE_SYSTEM);
    coord.draw(*(GetMainCanvas().shader));

    // Draw grid.
    GetMainCanvas().shader->set_uniform("color_mode", 1);
    GetMainCanvas().shader->set_uniform(
        "model_matrix",
        (Eigen::Translation3f(Eigen::Vector3f::UnitZ() * -0.02) *
         Eigen::Isometry3f::Identity())
            .matrix());
    GetMainCanvas().shader->set_uniform(
        "material_color", Eigen::Vector4f(0.8f, 0.8f, 0.8f, 1.0f));
    const auto &grid =
        glk::Primitives::instance()->primitive(glk::Primitives::GRID);
    grid.draw(*(GetMainCanvas().shader));
  }
};

}  // namespace interactive_point_cloud::gl

#endif  // GL_COORDINATE_SYSTEM_HPP_