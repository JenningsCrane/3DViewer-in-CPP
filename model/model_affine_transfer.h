#ifndef MODEL_AFFINE_TRANSFER_H
#define MODEL_AFFINE_TRANSFER_H

#include "../viewer_data.h"
#include "rotation_strategy/rotation_strategy.h"

class ModelAffineTransfer {
 public:
  ModelAffineTransfer() {}
  ModelAffineTransfer(RotationStrategy *rot) : rotation(rot) {}
  ~ModelAffineTransfer() { delete rotation; }

  void Rotate(coordinates &data) { rotation->Rotate(data); }

  void Translate(coordinates &data);

  void Scale(coordinates &data);
  void Center(coordinates &data);
  void ObjectReduct(coordinates &data);
  void MaxMin(coordinates &data);

 private:
  RotationStrategy *rotation;
};

#endif  // MODEL_AFFINE_TRANSFER_H