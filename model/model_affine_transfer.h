#ifndef CPP4_3DVIEWER_V2_0_1_MODEL_MODEL_AFINE_TRANSFER_H_
#define CPP4_3DVIEWER_V2_0_1_MODEL_MODEL_AFINE_TRANSFER_H_

#include "../viewer_data.h"
#include "rotation_strategy/rotation_strategy.h"

namespace s21 {

class ModelAffineTransfer {
 public:
  void Rotate(const RotationStrategy& rotation, std::vector<float>& v,
              Coordinates& data);
  void Translate(std::vector<float>& v, Coordinates& data);
  void Scale(std::vector<float>& vertex, Coordinates& data);
  void Center(std::vector<float>& vertex);
  void CalculateMaxOrMin(std::vector<float>& vertex, Coordinates& data);
  template <typename T>
  void WritingMaxOrMin(T& coordinate, float& max, float& min);
  void ObjectReduct(std::vector<float>& vertex, Coordinates& data);
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_MODEL_MODEL_AFINE_TRANSFER_H_
