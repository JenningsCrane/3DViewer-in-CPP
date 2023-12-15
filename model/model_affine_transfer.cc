#include "model_affine_transfer.h"

#include <cmath>

#include "../viewer_data.h"

namespace s21 {

void ModelAffineTransfer::Rotate(const RotationStrategy& rotation,
                                 std::vector<float>& v, Coordinates& data) {
  rotation.Rotate(v, data);
}

void ModelAffineTransfer::Translate(std::vector<float>& v, Coordinates& data) {
  float dx = data.move_value_x - data.last_move_x;
  float dy = data.move_value_y - data.last_move_y;
  float dz = data.move_value_z - data.last_move_z;
  float matrix[] = {1, 0, 0, dx, 0, 1, 0, dy, 0, 0, 1, dz, 0, 0, 0, 1};
  for (size_t i = 0; i < v.size(); i += 3) {
    v[i] = matrix[0] * v[i] + matrix[1] * v[i + 1] + matrix[2] * v[i + 2] +
           matrix[3] * 1;
    v[i + 1] = matrix[4] * v[i] + matrix[5] * v[i + 1] + matrix[6] * v[i + 2] +
               matrix[7] * 1;
    v[i + 2] = matrix[8] * v[i] + matrix[9] * v[i + 1] + matrix[10] * v[i + 2] +
               matrix[11] * 1;
  }
  data.last_move_x = data.move_value_x;
  data.last_move_y = data.move_value_y;
  data.last_move_z = data.move_value_z;
}

void ModelAffineTransfer::Scale(std::vector<float>& vertex, Coordinates& data) {
  float dscale = data.scale_value - data.last_scale;
  for (size_t i = 0; i < vertex.size(); i += 3) {
    vertex[i] *= dscale + 1;
    vertex[i + 1] *= dscale + 1;
    vertex[i + 2] *= dscale + 1;
  }
  data.last_scale = data.scale_value;
}

void ModelAffineTransfer::Center(std::vector<float>& vertex) {
  float center_x = 0.0;
  float center_y = 0.0;
  float center_z = 0.0;
  for (size_t i = 0; i < vertex.size(); i += 3) {
    center_x += vertex[i];
    center_y += vertex[i + 1];
    center_z += vertex[i + 2];
  }
  center_x /= vertex.size();
  center_y /= vertex.size();
  center_z /= vertex.size();
  for (size_t i = 0; i < vertex.size(); i += 3) {
    vertex[i] -= center_x;
    vertex[i + 1] -= center_y;
    vertex[i + 2] -= center_z;
  }
}

void ModelAffineTransfer::CalculateMaxOrMin(std::vector<float>& vertex,
                                            Coordinates& data) {
  data.max_x = data.max_y = data.max_z = 0;
  data.min_x = data.min_y = data.min_z = 0;
  for (size_t i = 0; i < vertex.size(); i += 3) {
    WritingMaxOrMin(vertex[i], data.max_x, data.min_x);
    WritingMaxOrMin(vertex[i + 1], data.max_y, data.min_y);
    WritingMaxOrMin(vertex[i + 2], data.max_z, data.min_z);
  }
}

template <typename T>
void ModelAffineTransfer::WritingMaxOrMin(T& coordinate, float& max,
                                          float& min) {
  if (coordinate > max) {
    max = coordinate;
  } else if (coordinate < min) {
    min = coordinate;
  }
}

void ModelAffineTransfer::ObjectReduct(std::vector<float>& vertex,
                                       Coordinates& data) {
  CalculateMaxOrMin(vertex, data);
  float max =
      std::fmax(std::fmax(data.max_x - data.min_x, data.max_y - data.min_y),
                data.max_y - data.min_y);
  float scale_obj = 1 / max;
  for (size_t i = 0; i < vertex.size(); i += 3) {
    vertex[i] *= scale_obj;
    vertex[i + 1] *= scale_obj;
    vertex[i + 2] *= scale_obj;
  }
}

}  // namespace s21
