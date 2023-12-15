#ifndef CPP4_3DVIEWER_V2_0_1_MODEL_ROTATION_STRATEGY_ROTATION_STRATEGY_H_
#define CPP4_3DVIEWER_V2_0_1_MODEL_ROTATION_STRATEGY_ROTATION_STRATEGY_H_

#include "../../viewer_data.h"

namespace s21 {

class RotationStrategy {
 public:
  RotationStrategy() = default;
  virtual void Rotate(std::vector<float>&, Coordinates&) const {};
  void RotateArr(std::vector<float>& vertex, float* matrix) const;
};

class RotateX : public RotationStrategy {
 public:
  void Rotate(std::vector<float>& vertex, Coordinates& data) const override;
};

class RotateY : public RotationStrategy {
 public:
  void Rotate(std::vector<float>& vertex, Coordinates& data) const override;
};

class RotateZ : public RotationStrategy {
 public:
  void Rotate(std::vector<float>& vertex, Coordinates& data) const override;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_MODEL_ROTATION_STRATEGY_ROTATION_STRATEGY_H_
