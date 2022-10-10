#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <iostream>
#include <string>

namespace interactive_point_cloud {

struct Context {
  struct PointCloudDataMenu {
    std::string file_name;
    bool is_updated = false;
    bool is_opened = false;
  };
  PointCloudDataMenu point_cloud_data_menu;
};

}  // namespace interactive_point_cloud

#endif  // CONTEXT_HPP