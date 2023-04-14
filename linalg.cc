#include "linalg.h"
#include <format>

std::ostream &operator<<(std::ostream &out, Point &p)
{
  out << (p.vec ? "[" : "(");
  out << p.x << "," << p.y << "," << p.z;
  out << (p.vec ? "]" : ")");
  return out;
}

std::ostream &operator<<(std::ostream &out, Line &l)
{
  out << l.p << " " << l.dir;
  return out;
}

std::ostream &operator<<(std::ostream &out, Plane &pl)
{
  out << std::format("%fx + %fy + %fz = %f", pl.a, pl.b, pl.c, pl.d);
}

Vec cross(Vec v1, Vec v2)
{
  return makeVec(
      v1.y*v2.z - v1.z*v2.y,
      v1.z*v2.x - v1.x*v2.z,
      v1.x*v2.y - v1.y*v2.x,
      );
}

double dot(Vec v1, Vec v2)
{
  return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

Vec operator-(Point p1, Point p2)
{
  return makeVec(p1.x-p2.x, p1.y-p2.y, p1.z-p2.z);
}

Vec makeVec(double x, double y, double z)
{
  Point p {x, y, z};
  p.vec = true;
  return p;
}

Line::Line(Point p1, Point p2)
{
  p = p1;
  
  if(p2.vec)
  {
    dir = p2;
  }

  else
  {
    dir = p2 - p1;
  }
}

Plane::Plane(Point p1, Point p2, Point p3)
{
  Vec d1, d2;
  if(p2.vec && p3.vec)
  {
    d1 = p2;
    d2 = p3;
  }

  else if(!p2.vec && !p3.vec)
  {
    d1 = p2-p1;
    d2 = p3-p1;
  }
  
  else
  {
    std::cerr << "Plane(): invalid combination " << p1 << " " << p2 << " " << p3 << std::endl;
    return;
  }
  
  Vec N = cross(d1, d2);
  a = N.x;
  b = N.y;
  c = N.z;

  d = dot(p1, N);
}

Plane::normal()
{
  return makeVec(a, b, c);
}
