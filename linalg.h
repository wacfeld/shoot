#ifndef LINALG_H
#define LINALG_H
#include <iostream>

struct Point;
struct Line;
struct Plane;

typedef Point Vec;

std::ostream &operator<<(std::ostream &out, Point &p);
std::ostream &operator<<(std::ostream &out, Line &l);
std::ostream &operator<<(std::ostream &out, Plane &pl);

Vec operator-(Point p1, Point p2);
Vec operator+(Vec v1, Vec v2);
Vec operator*(double c, Vec v);
Vec operator*(Vec v, double c);

Vec makeVec(double x, double y, double z);

Point intersect(Plane pl, Line l);
bool parallel(Plane pl, Line l);
bool zero(Point p);

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

struct Rectangle
{
  Point tl;
  Vec h;
  Vec w;

  Rectangle(Point tl, Vec h, Vec w);
  Plane plane();

  Point tr();
  Point bl();
  Point br();
};

#endif
