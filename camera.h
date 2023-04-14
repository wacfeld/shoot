#ifndef CAMERA_H
#define CAMERA_H
#include "linalg.h"

struct Camera
{
  double x, y, z;
  double pitch, yaw, roll;
  double width;
  Rectangle rect;
};

#endif
