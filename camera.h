#ifndef CAMERA_H
#define CAMERA_H
#include "linalg.h"

struct Camera
{
  Point cent;
  double alt, azi, roll; // radians
  double width, height;
  double dist;
  Rectangle getRect();
};

#endif
