#ifndef VIEWER_DATA_H
#define VIEWER_DATA_H

#include <stdio.h>

enum affine {
  kRotateX,
  kRotateY,
  kRotateZ,
  kTranslate,
  kCenter,
  kObjectReduct,
  kMaxMin,
  kScale
};

struct coordinates {
  float num_x;
  float num_y;
  float num_z;
  float num_last_x;
  float num_last_y;
  float num_last_z;
  int size_v;
  float v;
  float max_x;
  float min_x;
  float max_y;
  float min_y;
  float max_z;
  float min_z;

  affine state;
};

struct info {
  FILE file;
  float **v;
  unsigned int **f;
  int *size_v;
  int *size_f;
  char *name_file;
};

#endif  // VIEWER_DATA_H