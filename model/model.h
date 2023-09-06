#ifndef MODEL_H
#define MODEL_H

#include "model_affine_transfer.h"
#include "model_parser.h"

class Model {
 public:
  Model(){};

 protected:
  ModelParser parser;
  ModelAffineTransfer affineTransfer;
}

#endif