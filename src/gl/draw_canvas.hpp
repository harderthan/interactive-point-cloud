#ifndef GL_DRAW_CANVAS_HPP_
#define GL_DRAW_CANVAS_HPP_

#include "guik/gl_canvas.hpp"
#include "glk/primitives/primitives.hpp"

namespace interactive_point_cloud::gl {
class DrawCanvas {
 public:
  DrawCanvas(std::shared_ptr<guik::GLCanvas> main_canvas)
      : main_canvas_(main_canvas) {}

  virtual void Draw() = 0;

  guik::GLCanvas& GetMainCanvas() const { return *main_canvas_; }

 private:
  std::shared_ptr<guik::GLCanvas> main_canvas_;
};

}  // namespace interactive_point_cloud::gl

#endif   // GL_DRAW_CANVAS_HPP_