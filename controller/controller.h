#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include "../model/model.h"

class Controller {
 public:
  Controller(Model* m) : model(m) {}

 private:
  Model* model;
}

#endif  // CONSOLEVIEW_H