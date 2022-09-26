#include "guik/gl_canvas.hpp"

namespace gl {
class DrawCanvas {
 public:
  DrawCanvas();
  void Draw();

 private:
  std::unique_ptr<guik::GLCanvas> main_canvas;
};

}  // namespace gl