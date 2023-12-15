#ifndef CPP4_3DVIEWER_V2_0_1_VIEWER_DATA_H_
#define CPP4_3DVIEWER_V2_0_1_VIEWER_DATA_H_

#include <stdio.h>

#include <vector>

namespace s21 {

enum Affine {
  kRotateX,
  kRotateY,
  kRotateZ,
  kTranslate,
  kCenter,
  kObjectReduct,
  kMaxMin,
  kScale
};

struct Coordinates {
  float move_value_x{90};
  float move_value_y;
  float move_value_z;
  float last_move_x;
  float last_move_y;
  float last_move_z;
  float rotate_value_x;
  float rotate_value_y;
  float rotate_value_z;
  float last_rotate_x;
  float last_rotate_y;
  float last_rotate_z;
  float last_scale;
  float scale_value;
  float max_x;
  float max_y;
  float max_z;
  float min_x;
  float min_y;
  float min_z;

  Affine state;
};

struct Autosave {
  bool radio;
  int stipple, square, size_line, size_point;
  float red_line, green_line, blue_line;
  float red_point, green_point, blue_point;
  float red_backg, green_backg, blue_backg;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_VIEWER_DATA_H_
