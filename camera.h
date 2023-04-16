#ifndef CAMERA_H
#define CAMERA_H
#include "linalg.h"
#include "drawer.h"

struct Camera
{
  Point p;
  // double alt, azi, roll; // radians
  Orient o;
  double width, height;
  double dist;
  Plane plane;
  
  Camera(Point p, Orient o, double width, double height, double dist);

  Point2D cent2tl(Point2D P);
  Point2D scale(Point2D P);
  // void screenQuad(Rectangle proj);
  Point toscreen(Point p);
  std::vector<Point> wall2screen(Wall wall);
};

#endif
