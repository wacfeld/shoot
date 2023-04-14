#include "linalg.h"

std::ostream &operator<<(std::ostream &out, Point &p)
{
  out << "(";
  out << p.x << "," << p.y << "," << p.z;
  out << ")";
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

Point cross(Point v1, Point v2)
{
  return {
    v1.y*v2.z - v1.z*v2.y,
    v1.z*v2.x - v1.x*v2.z,
    v1.x*v2.y - v1.y*v2.x
  };
}

double dot(Point v1, Point v2)
{
  return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

Point operator-(Point p1, Point p2)
{
  return {p1.x-p2.x, p1.y-p2.y, p1.z-p2.z};
}

Point operator+(Point v1, Point v2)
{
  return {v1.x+v2.x, v1.y+v2.y, v1.z+v2.z};
}

Point operator*(double c, Point v)
{
  return {c*v.x, c*v.y, c*v.z};
}

Point operator*(Point v, double c)
{
  return c * v;
}

Line points2line(Point p1, Point p2)
{
  Line l;
  l.p = p1;
  l.dir = p2-p1;
  return l;
}

Line pdir2line(Point p, Point dir)
{
  Line l;
  l.p = p;
  l.dir = dir;
  return l;
}

Plane points2plane(Point p1, Point p2, Point p3)
{
  Point d1 = p2-p1;
  Point d2 = p3-p1;
  return pdir2plane(p1, d1, d2);
}

Plane pdir2plane(Point p, Point d1, Point d2)
{
  Point N = cross(d1, d2);
  double d = dot(p, N);
  return Plane(N.x, N.y, N.z, d);
}

Plane::Plane(double _a, double _b, double _c, double _d): a{_a}, b{_b}, c{_c}, d{_d} {}

Point Plane::normal()
{
  return {a, b, c};
}

Rectangle::Rectangle(Point _tl, Point _h, Point _w): tl{_tl}, h{_h}, w{_w} {}

Point Rectangle::tr()
{
  Point p = tl+w;
  return p;
}

Point Rectangle::bl()
{
  Point p = tl+h;
  return p;
}

Point Rectangle::br()
{
  Point p = tl+h+w;
  return p;
}

Plane Rectangle::plane()
{
  return pdir2plane(tl, h, w);
}

Point intersect(Plane pl, Line l)
{
  double numer = pl.d - (pl.a*l.p.x + pl.b*l.p.y + pl.c*l.p.z);
  double denom = pl.a*l.dir.x + pl.b*l.dir.y + pl.c*l.dir.z;
  double t = numer/denom;
  
  Point p = l.p + t*l.dir;
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
