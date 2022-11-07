#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

#include <glk/pointcloud_buffer.hpp>

namespace {

Eigen::Vector3f CalculateCenter(
    const pcl::PointCloud<pcl::PointXYZ>::ConstPtr& cloud) {
  float x_min = std::numeric_limits<float>::max();
  float x_max = std::numeric_limits<float>::max() * -1;
  float y_min = std::numeric_limits<float>::max();
  float y_max = std::numeric_limits<float>::max() * -1;
  float z_min = std::numeric_limits<float>::max();
  float z_max = std::numeric_limits<float>::max() * -1;
  for (const auto& p : cloud->points) {
    x_min = std::min(x_min, p.x);
    x_max = std::max(x_max, p.x);
    y_min = std::min(y_min, p.y);
    y_max = std::max(y_max, p.y);
    z_min = std::min(z_min, p.z);
    z_max = std::max(z_max, p.z);
  }
  return Eigen::Vector3f((x_min + x_max) / 2.0f, (y_min + y_max) / 2.0f,
                           (z_min + z_max) / 2.0f);
}

}  // namespace

namespace glk {

PointCloudBuffer::PointCloudBuffer(const std::string& cloud_filename) {
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(
      new pcl::PointCloud<pcl::PointXYZ>());
  if (pcl::io::loadPCDFile(cloud_filename, *cloud)) {
    std::cerr << "error: failed to load " << cloud_filename << std::endl;
    num_points = 0;
    return;
  }

  center = CalculateCenter(cloud);
  std::cout << center.transpose() << std::endl;

  stride = sizeof(pcl::PointXYZ);
  num_points = cloud->size();
  std::cout << "loaded " << cloud_filename << std::endl;
  std::cout << "number of points: " << num_points << std::endl;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, cloud->size() * sizeof(pcl::PointXYZ),
               cloud->points.data(), GL_STATIC_DRAW);
}

PointCloudBuffer::PointCloudBuffer(
    const pcl::PointCloud<pcl::PointXYZ>::ConstPtr& cloud) {
  stride = sizeof(pcl::PointXYZ);
  num_points = cloud->size();
  std::cout << "num_points " << num_points << ", stride " << stride
            << std::endl;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, cloud->size() * sizeof(pcl::PointXYZ),
               cloud->points.data(), GL_STATIC_DRAW);
}

PointCloudBuffer::~PointCloudBuffer() {
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
}

void PointCloudBuffer::draw(glk::GLSLShader& shader) {
  if (num_points == 0) {
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
