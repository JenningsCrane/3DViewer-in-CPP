#include "rotation_strategy.h"

#include <cmath>
#include <cstddef>

#include "../../viewer_data.h"

namespace s21 {

void RotationStrategy::RotateArr(std::vector<float>& vertex,
                                 float* matrix) const {
  for (size_t i = 0; i < vertex.size(); i += 3) {
    float temp_x = vertex[i];
    float temp_y = vertex[i + 1];
    float temp_z = vertex[i + 2];
    vertex[i] = matrix[0] * temp_x + matrix[1] * temp_y + matrix[2] * temp_z;
    vertex[i + 1] =
        matrix[3] * temp_x + matrix[4] * temp_y + matrix[5] * temp_z;
    vertex[i + 2] =
        matrix[6] * temp_x + matrix[7] * temp_y + matrix[8] * temp_z;
  }
}

void RotateX::Rotate(std::vector<float>& vertex, Coordinates& data) const {
  float dx = data.rotate_value_x - data.last_rotate_x;
  float matrix[] = {
      1, 0, 0, 0, std::cos(dx), -std::sin(dx), 0, std::sin(dx), std::cos(dx)};
  RotationStrategy::RotateArr(vertex, matrix);
  data.last_rotate_x = data.rotate_value_x;
}

void RotateY::Rotate(std::vector<float>& vertex, Coordinates& data) const {
  float dy = data.rotate_value_y - data.last_rotate_y;
  float matrix[] = {std::cos(dy),  0, std::sin(dy), 0, 1, 0,
                    -std::sin(dy), 0, std::cos(dy)};
  RotationStrategy::RotateArr(vertex, matrix);
  data.last_rotate_y = data.rotate_value_y;
}

void RotateZ::Rotate(std::vector<float>& vertex, Coordinates& data) const {
  float dz = data.rotate_value_z - data.last_rotate_z;
  float matrix[] = {
      std::cos(dz), -std::sin(dz), 0, std::sin(dz), std::cos(dz), 0, 0, 0, 1};
  RotationStrategy::RotateArr(vertex, matrix);
  data.last_rotate_z = data.rotate_value_z;
}

}  // namespace s21
