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

Point operator-(Point p1, Point p2);
Point operator+(Point v1, Point v2);
Point operator*(double c, Point v);
Point operator*(Point v, double c);

Point intersect(Plane pl, Line l);
bool parallel(Plane pl, Line l);
bool zero(Point p);

Line points2line(Point p1, Point p2);
Line pdir2line(Point p, Point dir);
Plane points2plane(Point p1, Point p2, Point p3);
Plane pdir2plane(Point p, Point d1, Point d2);

struct Point
{
  double x, y, z;

  Point() {}
  Point(double ex, double why, double zee): x{ex}, y{why}, z{zee} {}
};

struct Line
{
  Point p;
  Point dir;
  Line() {}
};

struct Plane
{
  double a, b, c, d; // ax + by + cz = d

  Plane(double a, double b, double c, double d);
  Point normal();
};

struct Rectangle
{
  Point tl;
  Point w;
  Point h;

  Rectangle(Point tl, Point h, Point w);
  Plane plane();

  Point tr();
  Point bl();
  Point br();
};

#endif
