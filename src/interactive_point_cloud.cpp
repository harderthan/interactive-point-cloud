#include <iostream>
#include <memory>

#include "interactive_point_cloud_application.hpp"

int main(int argc, char **argv) {
  std::cout << "hello, interactive point cloud" << std::endl;
  
  std::unique_ptr<guik::Application> app(
      std::make_unique<InteractivePointCloudApplication>());

  if(!app->init("Interactive SLAM", Eigen::Vector2i(1920, 1080))) {
    return 1;
  }

  app->run();

  return 0;
}
