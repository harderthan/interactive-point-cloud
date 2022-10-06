#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <iostream>
#include <string>

namespace interactive_point_cloud {

struct FileMenu {
  std::string point_cloud_file_name;
  bool is_opened = false;
};

struct Context {
  FileMenu file_menu;
};

}  // namespace interactive_point_cloud

#endif  // CONTEXT_HPP