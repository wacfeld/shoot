#ifndef CAMERA_H
#define CAMERA_H
#include "linalg.h"

struct Camera
{
  Point p;
  // double alt, azi, roll; // radians
  Orient o;
  double width, height;
  double dist;
  Plane pl;
  
  Camera(Point p, Orient o, double width, double height, double dist);
};

#endif
