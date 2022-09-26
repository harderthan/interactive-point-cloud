#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <iostream>
#include <string>

namespace interactive_point_cloud {

class Context {
 public:
  Context() = default;
  ~Context() = default;

  void SetPointCloudFileName(const std::string& file_name) {
    point_cloud_file_name_ = file_name;
    std::cout << "Context: set point cloud file name, "
              << point_cloud_file_name_ << std::endl;
  }
  std::string GetPointCloudFileName() {
    std::string result = point_cloud_file_name_;
    point_cloud_file_name_.clear();
    return result;
  }

 private:
  std::string point_cloud_file_name_;
};

}  // namespace interactive_point_cloud

#endif  // CONTEXT_HPP