#include <glk/pointcloud_buffer.hpp>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

namespace glk {

PointCloudBuffer::PointCloudBuffer(const std::string& cloud_filename) {
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>());
  if(pcl::io::loadPCDFile(cloud_filename, *cloud)) {
    std::cerr << "error: failed to load " << cloud_filename << std::endl;
    num_points = 0;
    return;
  }

  // Calculate the center of the point cloud.
  Eigen::Vector3f point(0, 0, 0);
  for (const auto& p : cloud->points) {
    point += Eigen::Vector3f(p.x, p.y, p.z);
  }
  point /= cloud->size();
  center = point;

  stride = sizeof(pcl::PointXYZ);
  num_points = cloud->size();
  std::cout << "loaded " << cloud_filename << std::endl;
  std::cout << "number of points: " << num_points << std::endl;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, cloud->size() * sizeof(pcl::PointXYZ), cloud->points.data(), GL_STATIC_DRAW);
}

PointCloudBuffer::PointCloudBuffer(const pcl::PointCloud<pcl::PointXYZ>::ConstPtr& cloud) {
  stride = sizeof(pcl::PointXYZ);
  num_points = cloud->size();
  std::cout << "num_points " << num_points << ", stride " << stride << std::endl;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, cloud->size() * sizeof(pcl::PointXYZ), cloud->points.data(), GL_STATIC_DRAW);
}

PointCloudBuffer::~PointCloudBuffer() {
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
}

void PointCloudBuffer::draw(glk::GLSLShader& shader) {
  if(num_points == 0) {
    return;
  }

  GLint position_loc = shader.attrib("vert_position");

  glBindVertexArray(vao);
  glEnableVertexAttribArray(position_loc);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);

  glDrawArrays(GL_POINTS, 0, num_points);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glDisableVertexAttribArray(0);
}



}  // namespace glk
