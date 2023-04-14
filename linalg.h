#ifndef LINALG_H
#define LINALG_H
#include <iostream>

struct Point;
struct Line;
struct Plane;
struct Rectangle;

typedef Point Vec;

std::ostream &operator<<(std::ostream &out, Point p);
std::ostream &operator<<(std::ostream &out, Line l);
std::ostream &operator<<(std::ostream &out, Plane pl);
std::ostream &operator<<(std::ostream &out, Rectangle rect);

Point operator-(Point p1, Point p2);
Point operator+(Point v1, Point v2);
Point operator*(double c, Point v);
Point operator*(Point v, double c);

Point intersect(Plane pl, Line l);
bool parallel(Plane pl, Line l);
bool zero(Point p);

Rectangle project(Rectangle src, Rectangle dest, Point p);
Rectangle project(Rectangle src, Plane dest, Point p);

double deg2rad(double deg);

Line points2line(Point p1, Point p2);
Line pdir2line(Point p, Point dir);
Plane points2plane(Point p1, Point p2, Point p3);
Plane pdir2plane(Point p, Point d1, Point d2);

struct Point
{
  double x, y, z;

  Point() {}
  Point(double ex, double why, double zee): x{ex}, y{why}, z{zee} {}
  
  Vec rotateX(double th);
  Vec rotateY(double th);
  Vec rotateZ(double th);
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
  Point bl_dat;
  Point w;
  Point h;

  // Rectangle(Point bl, Point h, Point w);
  Rectangle(Point bl, Point br, Point tl, Point tr);
  Plane plane();

  Point bl() {return bl_dat;}
  Point tr() {return bl_dat + h + w;}
  Point tl() {return bl_dat + h;}
  Point br() {return bl_dat + w;}
};

#endif
