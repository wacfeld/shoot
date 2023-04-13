#include "linalg.h"

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
