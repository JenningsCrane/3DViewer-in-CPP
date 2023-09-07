#ifndef ROTATION_STRATEGY_H
#define ROTATION_STRATEGY_H

#include "../../viewer_data.h"

class RotationStrategy {
 public:
  RotationStrategy(){};
  virtual void Rotate(coordinates &data){};
  void RotateArr(coordinates &data);
};
class RotateX : public RotationStrategy {
 public:
  void Rotate(coordinates &data) override{};
};

class RotateY : public RotationStrategy {
 public:
  void Rotate(coordinates &data) override{};
};

class RotateZ : public RotationStrategy {
 public:
  void Rotate(coordinates &data) override{};
};

#endif  // ROTATION_STRATEGY_H