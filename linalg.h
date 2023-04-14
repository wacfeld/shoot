#ifndef LINALG_H
#define LINALG_H
#include <iostream>

struct Point;
struct Line;
struct Plane;

typedef Point Vec;

std::ostream &operator<<(std::ostream &out, Point &p);
std::ostream &operator<<(std::ostream &out, Line &l);

Vec operator-(Point p1, Point p2);
Vec makeVec(double x, double y, double z);

struct Point
{
  bool vec;
  double x, y, z;

  Point() {}
  Point(double ex, double why, double zee): vec{false}, x{ex}, y{why}, z{zee} {}
};

struct Line
{
  Point p;
  Vec dir;
  Line(Point p1, Point p2);
};

struct Plane
{
  double a, b, c, d; // ax + by + cz = d

  Plane(Point p1, Point p2, Point p3);
  Vec normal();
};

#endif
