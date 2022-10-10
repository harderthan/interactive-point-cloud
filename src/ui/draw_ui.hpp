#ifndef UI_DRAW_UI_HPP_
#define UI_DRAW_UI_HPP_

#include <memory>
#include <string>

#include "context.hpp"
#include "imgui.h"

namespace interactive_point_cloud::ui {

using interactive_point_cloud::Context;

class DrawUi {
 public:
  DrawUi(std::shared_ptr<Context> context) : context_(context) {}

  virtual void Draw() = 0;
  virtual void Update() = 0;

  Context& GetContext() const { return *context_; }

 private:
  std::shared_ptr<Context> context_;
};

}  // namespace interactive_point_cloud::ui

#endif  // UI_DRAW_UI_HPP_