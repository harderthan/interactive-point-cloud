#ifndef GL_COORDINATE_SYSTEM_HPP_
#define GL_COORDINATE_SYSTEM_HPP_

#include "draw_canvas.hpp"

namespace interactive_point_cloud::gl {
class CoordinateSystem : public DrawCanvas {
 public:
  CoordinateSystem(std::shared_ptr<guik::GLCanvas> main_canvas)
      : DrawCanvas(main_canvas) {}

  void Draw() {}
  void Update() {}
};

}  // namespace interactive_point_cloud::gl

#endif  // GL_COORDINATE_SYSTEM_HPP_