#ifndef MODEL_H
#define MODEL_H

#include "model_affine_transfer.h"
#include "processing_file/processing_file.h"

class Model {
 public:
  Model() {}
  ~Model() { delete parser; }
  ProcessingFile* parser = new ProcessingFile();

  void OtherMethods(coordinates& data);
  void AffineRotate(coordinates& data);
};

#endif  // MODEL_H