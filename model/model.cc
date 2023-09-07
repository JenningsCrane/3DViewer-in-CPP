#include "model.h"

void Model::OtherMethods(coordinates& data) {
  ModelAffineTransfer* affineOther = new ModelAffineTransfer();
  switch (data.state) {
    case (affine::kCenter):
      affineOther->Center(data);
      break;
    case (affine::kTranslate):
      affineOther->Translate(data);
      break;
    case (affine::kObjectReduct):
      affineOther->ObjectReduct(data);
      break;
    case (affine::kMaxMin):
      affineOther->MaxMin(data);
      break;
    case (affine::kScale):
      affineOther->Scale(data);
      break;
    default:
      break;
  }
  delete affineOther;
}

void Model::AffineRotate(coordinates& data) {
  ModelAffineTransfer* affineTransfer =
      nullptr;  // Объявляем переменную перед switch и инициализируем ее
                // значением nullptr
  switch (data.state) {
    case (affine::kRotateX):
      affineTransfer = new ModelAffineTransfer(new RotateX);
      affineTransfer->Rotate(data);
      break;
    case (affine::kRotateY):
      affineTransfer = new ModelAffineTransfer(new RotateY);
      affineTransfer->Rotate(data);
      break;
    case (affine::kRotateZ):
      affineTransfer = new ModelAffineTransfer(new RotateZ);
      affineTransfer->Rotate(data);
      break;
    default:
      break;
  }
  delete affineTransfer;  // Удаляем объект после использования, если он был
                          // создан
}