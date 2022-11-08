#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <iostream>
#include <string>

namespace interactive_point_cloud {

struct Context {
  struct AppStatus {
    double coordinate_x = 0.0;
    double coordinate_y = 0.0;
    double coordinate_z = 0.0;
    bool is_updated = false;
  };
  AppStatus app_status;

  struct PointCloudDataMenu {
    std::string file_name;
    bool is_updated = false;
    bool is_opened = false;
  };
  PointCloudDataMenu point_cloud_data_menu;

  struct RoadNetworksMenu {
    std::string file_name;
    bool is_updated = false;
    bool is_opened = false;
  };
  RoadNetworksMenu road_networks_menu;
};

}  // namespace interactive_point_cloud

#endif  // CONTEXT_HPP