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
  out << l.p << " + t" << l.dir;
  return out;
}

std::ostream &operator<<(std::ostream &out, Plane &pl)
{
  // not supported by all the compilers i could install
  // out << std::format("%fx + %fy + %fz = %f", pl.a, pl.b, pl.c, pl.d);
  out << pl.a << "x + " << pl.b << "y + " << pl.c << "z = " << pl.d << std::endl;
  return out;
}

Vec cross(Vec v1, Vec v2)
{
  return makeVec(
      v1.y*v2.z - v1.z*v2.y,
      v1.z*v2.x - v1.x*v2.z,
      v1.x*v2.y - v1.y*v2.x
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

Vec operator+(Vec v1, Vec v2)
{
  return makeVec(v1.x+v2.x, v1.y+v2.y, v1.z+v2.z);
}

Vec operator*(double c, Vec v)
{
  return makeVec(c*v.x, c*v.y, c*v.z);
}

Vec operator*(Vec v, double c)
{
  return c * v;
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

  if(zero(dir))
  {
    std::cerr << "cannot make line from " << p1 << " and " << p2 << std::endl;
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

Vec Plane::normal()
{
  return makeVec(a, b, c);
}

Rectangle::Rectangle(Point _tl, Vec _h, Vec _w): tl{_tl}, h{_h}, w{_w}
{
  tl.vec = false;
  tl.vec = true;
  tl.vec = true;
}

Point Rectangle::tr()
{
  Point p = tl+w;
  p.vec = false;
  return p;
}

Point Rectangle::bl()
{
  Point p = tl+h;
  p.vec = false;
  return p;
}

Point Rectangle::br()
{
  Point p = tl+h+w;
  p.vec = false;
  return p;
}

Plane Rectangle::plane()
{
  Plane pl {
}

Point intersect(Plane pl, Line l)
{
  double numer = pl.d - (pl.a*l.p.x + pl.b*l.p.y + pl.c*l.p.z);
  double denom = pl.a*l.dir.x + pl.b*l.dir.y + pl.c*l.dir.z;
  double t = numer/denom;
  
  Point p = l.p + t*l.dir;
  p.vec = false;
  return p;
}

bool parallel(Plane pl, Line l)
{
  return dot(pl.normal(), l.dir) == 0;
}

bool zero(Point p)
{
  return p.x == 0 && p.y == 0 && p.z == 0;
}
